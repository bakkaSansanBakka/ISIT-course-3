--1. add birthday and salary column to teachers--
alter table teacher
  add (
        BIRTHDAY date,
        SALARY number(20, 2)
      );

select * from teacher;
  
insert into TEACHER (TEACHER, TEACHER_NAME, PULPIT, BIRTHDAY, SALARY)
  values  ('????', '?????? ???????? ?????????????', '????', TO_DATE('1967/05/04', 'yyyy/mm/dd'), 1000);
insert into TEACHER (TEACHER, TEACHER_NAME, PULPIT, BIRTHDAY, SALARY)
  values ('?????', '???????? ????????? ????????', '????', TO_DATE('1957/05/01', 'yyyy/mm/dd'), 1200);
insert into TEACHER (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?????',    '?????????? ?????? ??????????',  '????', TO_DATE('1978/02/01', 'yyyy/mm/dd'), 1100);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',    '?????? ???? ???????????',  '????', TO_DATE('1992/12/07', 'yyyy/mm/dd'), 900);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',    '??????? ???????? ????????',  '????', TO_DATE('1969/12/11', 'yyyy/mm/dd'), 1000);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?????',    '???????? ?????? ?????????',  '????', TO_DATE('1989/03/23', 'yyyy/mm/dd'), 960);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',     '????? ????????? ??????????',  '????', TO_DATE('1978/09/24', 'yyyy/mm/dd'), 1130);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',     '??????? ????????? ???????????',  '????', TO_DATE('1921/12/01', 'yyyy/mm/dd'), 1200);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',     '????????? ????? ????????',  '????', TO_DATE('1949/03/01', 'yyyy/mm/dd'), 1500);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',     '????????? ??????? ??????????',  '????', TO_DATE('1975/06/17', 'yyyy/mm/dd'), 1200);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',  '??????????? ??????? ??????????', '????', TO_DATE('1958/08/10', 'yyyy/mm/dd'), 1350 );
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?',     '???????????',  '????', TO_DATE('1970/01/01', 'yyyy/mm/dd'), 600);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                      values  ('???',     '????? ??????? ????????',  '????', TO_DATE('1955/02/23', 'yyyy/mm/dd'), 1400);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',     '????? ??????? ?????????????',  '????', TO_DATE('1979/04/16', 'yyyy/mm/dd'), 1200);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',   '?????????? ????????? ?????????????',  '??????', TO_DATE('1966/11/29', 'yyyy/mm/dd'), 1100);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?????',   '??????? ?????? ??????????',  '??????', TO_DATE('1973/05/09', 'yyyy/mm/dd'), 900);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',   '??????????? ????????? ????????',  '????', TO_DATE('1967/10/15', 'yyyy/mm/dd'), 1000);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',   '??????? ????????? ??????????',  '????', TO_DATE('1951/08/26', 'yyyy/mm/dd'), 1500);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',   '?????? ?????? ????????',  '??', TO_DATE('1991/07/24', 'yyyy/mm/dd'), 1200);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????', '??????? ?????? ??????????',  '??????', TO_DATE('1982/04/20', 'yyyy/mm/dd'), 1000);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',   '?????????? ???????? ????????',  '??', TO_DATE('1983/11/01', 'yyyy/mm/dd'), 950);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',   '?????? ?????????? ????????????',  '??', TO_DATE('1967/10/15', 'yyyy/mm/dd'), 1200);
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?????',   '????????? ???????? ?????????',  '?????', TO_DATE('1959/10/10', 'yyyy/mm/dd'), 1000); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',   '?????????? ???????? ??????????',  '??', TO_DATE('1993/03/27', 'yyyy/mm/dd'), 890); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('??????',   '????????? ??????? ?????????',  '????????', TO_DATE('1952/05/16', 'yyyy/mm/dd'), 1400); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('?????',   '???????? ?????? ??????????',  '??', TO_DATE('1969/12/25', 'yyyy/mm/dd'), 1090); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('???',   '????? ?????? ????????',  '?????', TO_DATE('1976/07/22', 'yyyy/mm/dd'), 1200); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',   '?????? ??????? ?????????',  '???????', TO_DATE('1984/11/10', 'yyyy/mm/dd'), 1100); 
insert into TEACHER    (TEACHER,  TEACHER_NAME, PULPIT, BIRTHDAY, SALARY )
                       values  ('????',   '??????? ???? ??????????',  '????????', TO_DATE('1956/09/19', 'yyyy/mm/dd'), 990); 

--2. list of teachers--
declare
  cursor teacher_cursor is select * from teacher;
begin
  for rec in teacher_cursor
    loop
      dbms_output.put_line(substr(rec.teacher_name, 1, instr(rec.teacher_name, ' '))
          || substr(rec.teacher_name, instr(rec.teacher_name, ' ', 1, 1) + 1, 1) || 
          '.' || substr(rec.teacher_name, instr(rec.teacher_name, ' ', 1, 2) + 1, 1) || '.');
    end loop;
end;

--3. teacher born on Monday--
select * from teacher 
  where (select to_char(birthday, 'DAY', 'NLS_DATE_LANGUAGE = ENGLISH') from dual)
    like '%MONDAY%';

--4. create view of teachers born in 1 month ago (no teachers born next month)--
create view teacherBirthday
  as select teacher, teacher_name, pulpit, birthday, 
            (extract(month from birthday)) as birthday_month, salary
  from teacher
  where (extract(month from birthday)) =  (extract(month from sysdate)) - 1;
  
drop view teacherBirthday;
select * from teacherBirthday;

--5. create view that contains teachers born in each month--
create view teacherBirth
  as select (extract(month from birthday)) as birthday_month, count(*) as count
  from teacher
  group by (extract(month from birthday))
  order by (extract(month from birthday));
  
drop view teacherBirth;
select * from teacherBirth;

--6. cursor for teachers which have anniversary next year--
declare
  cursor teacher_cursor is select * from teacher for update;
begin
  dbms_output.put_line('Teachers with anniversary next year: ');
  for rec in teacher_cursor
    loop
      if mod((extract(year from sysdate) + 1) - extract(year from rec.birthday), 5) = 0
        then dbms_output.put_line(rec.teacher_name || ' ' || rec.birthday);
      end if;
    end loop;
  
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--7. cursor for average salary of pulpit, for each faculty and for all faculties--
declare
  cursor faculty_cursor is select * from faculty;
  cursor pulpit_cursor(faculty_rec faculty_cursor%rowtype) 
    is select * from pulpit where faculty = faculty_rec.faculty;
  pulpitavg number(10, 2);
  salary_summary number(10, 2);
  counter int;
  faculty_average number(10, 2) := 0;
  faculty_counter int := 0;
begin
  for faculty_rec in faculty_cursor
    loop
      salary_summary := 0;
      counter := 0;
      dbms_output.put_line('faculty ' || rtrim(faculty_rec.faculty) || ': ');
      
      for pulpit_rec in pulpit_cursor(faculty_rec)
        loop
          select floor(avg(salary)) into pulpitavg from teacher
            where pulpit = pulpit_rec.pulpit;
          if pulpitavg > 0 then
            dbms_output.put_line('pulpit ' || rtrim(pulpit_rec.pulpit) || ': ' || pulpitavg);
            salary_summary := salary_summary + pulpitavg;
            counter := counter + 1;
          end if;
        end loop;
      
      if salary_summary > 0 and counter > 0 then
        dbms_output.put_line('AVERAGE FOR FACULTY = ' || floor(salary_summary/counter));
        faculty_average := faculty_average + salary_summary/counter;
        faculty_counter := faculty_counter + 1;
      end if;
    end loop;
    
  dbms_output.put_line('');
  dbms_output.put_line('AVERAGE SALARY FOR UNIVERSITY = ' || floor(faculty_average/faculty_counter));
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--8. create record type, nested records, assignment--
declare
  rec1 teacher%rowtype;
  type address is record
    (
      address1 varchar2(100),
      address2 varchar2(100)
    );
  type person is record
    (
      code teacher.teacher%type,
      name teacher.teacher_name%type,
      homeaddress address
    );
  rec2 person;
  rec3 person;
begin
  rec2.code := '????';
  rec2.name := '????????? ??????';
  rec2.homeaddress.address1 := '????????, ?????';
  rec2.homeaddress.address2 := '??. ????????, 78, ??. 53';
  rec3 := rec2;
  dbms_output.put_line(rtrim(rec3.code) || ' - ' || rec3.name || ' - ' || 
                        rec3.homeaddress.address1 || ' - ' || 
                        rec3.homeaddress.address2);
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;