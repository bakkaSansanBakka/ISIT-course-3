--DBMS_JOB--
alter system set JOB_QUEUE_PROCESSES = 9;

create table T1
(
  id number,
  num number
);

insert into T1 (id, num) values (1, 1);
insert into T1 (id, num) values (2, 2);
insert into T1 (id, num) values (3, 3);
insert into T1 (id, num) values (4, 4);
commit;

select * from T1;

create table T2
(
  id number,
  num number
);

--2. create job copy data from table 1 to table 2 and delete data drom table 1 once a week--
create or replace procedure copy_data_from_T1_to_T2 as
  err_msg nvarchar2(200);
  begin
    insert into T2 select * from T1 where num > 2;
    delete from T1 where num > 2;
    
    insert into job_log (finished_at, success) values (CURRENT_TIMESTAMP, 1);
    
    exception
      when others then
        err_msg := sqlerrm;
        insert into job_log (finished_at, success, err_msg) 
          values (CURRENT_TIMESTAMP, 0, err_msg);
  end;

--3. table for logging--
create table job_log
(
  pk number generated always as identity,
  finished_at timestamp,
  success char(1) check (success in ('0', '1')),
  err_msg nvarchar2(200),
  primary key (pk)
);

--run--
select * from T1;
select * from T2;
delete from T1;
delete from T2;

declare
  job_num user_jobs.job%type;
begin
  dbms_job.submit(job_num, 'begin copy_data_from_T1_to_T2; end;', sysdate, 'SYSDATE + 7');
  dbms_output.put_line(job_num);
end;

select * from dba_jobs where job = 1;
select * from job_log;

--5. next_date, broken--
begin
  dbms_job.broken(1, true);
end;

begin
  dbms_job.broken(1, false);
end;

begin
  dbms_job.next_date(1, sysdate + 2/24);
end;

select * from dba_jobs where job = 1;

--6. dbms_sheduler--
begin
  dbms_scheduler.create_schedule
  (
    schedule_name => 'Weeks', 
    start_date => to_date('1-1-2020', 'DD-MM-YYYY'), 
    repeat_interval => 'FREQ=Weekly'
  );
  dbms_scheduler.create_program
  (
    program_name => 'copy_data_from_T1_to_T2_progg', 
    program_type => 'STORED_PROCEDURE', 
    program_action => 'copy_data_from_T1_to_T2',
    number_of_arguments => 0,
    enabled => true
  );
  dbms_scheduler.create_job
  (
    job_name => 'job1',
    program_name => 'copy_data_from_T1_to_T2_progg',
    schedule_name => 'Weeks',
    enabled => true
  );
end;

begin
  dbms_scheduler.stop_job('job1');
end;

begin
  dbms_scheduler.set_attribute(name => 'job1', attribute => 'start_date', value => to_date('2-2-2020', 'DD-MM-YYYY'));
end;

select * from  user_scheduler_running_jobs;
select * from dba_jobs;