--1. DBLINK--
drop database link PDBLINK;
create database link PDBLINK
  connect to PPPCORE
  identified by pass
  using 'PPP_PDB';

--2. select, update, delete, insert--  
select * from PPPCORE_T11@PDBLINK;
insert into PPPCORE_T11@PDBLINK (col1, col2) values (4, 'str4');
update PPPCORE_T11@PDBLINK set col1 = 5 where col1 = 4;
delete PPPCORE_T11@PDBLINK where col1 = 5;

--3. global dblink--
create public database link PDBLINK_GLOBAL
  connect to PPPCORE
  identified by pass
  using 'PPP_PDB';
  
--4. select, update, delete, insert--
select * from PPPCORE_T11@PDBLINK_GLOBAL;
insert into PPPCORE_T11@PDBLINK_GLOBAL (col1, col2) values (4, 'str4');
update PPPCORE_T11@PDBLINK_GLOBAL set col1 = 5 where col1 = 4;
delete PPPCORE_T11@PDBLINK_GLOBAL where col1 = 5;