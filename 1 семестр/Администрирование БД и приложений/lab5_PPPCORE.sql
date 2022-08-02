create table PPPCORE_T11 (
  col1 number primary key,
  col2 varchar (10)
)
tablespace PPP_QDATA;

--select * from user_tables;

insert into PPPCORE_T11 (col1, col2) values (1, 'str1');
insert into PPPCORE_T11 (col1, col2) values (2, 'str2');
insert into PPPCORE_T11 (col1, col2) values (3, 'str3');

select * from PPPCORE_T11;

drop table PPPCORE_T11;

--3.all segments of tablespace--
select * from dba_segments where tablespace_name='PPP_QDATA';

--4.drop table and list segments--
select * from dba_segments where tablespace_name='PPP_QDATA';
select * from user_recyclebin;

--5. restore dropped table--
flashback table PPPCORE_T11 to before drop;

--6. insert 10000 rows into table--
select * from PPPCORE_T11;
delete from pppcore_t11;

begin
  for i in 1..10000
  loop
    insert into PPPCORE_T11 (col1, col2) values (dbms_random.random, 'some str');
  end loop;
end;

--7. extents in table--
select * from user_extents where segment_name='PPPCORE_T11';