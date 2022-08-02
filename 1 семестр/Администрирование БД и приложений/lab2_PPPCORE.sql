create table PPPCORE_T1 (
  col1 number,
  col2 varchar (10)
)
tablespace PPPCORE_QDATA;

select * from user_tables;

insert into PPPCORE_T1 (col1, col2) values (1, 'str1');
insert into PPPCORE_T1 (col1, col2) values (2, 'str2');

select * from PPPCORE_T1;



