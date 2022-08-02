grant create sequence to PPPCORE;
grant create table to PPPCORE;
grant create view to PPPCORE;
grant create cluster to PPPCORE;
grant create synonym to PPPCORE;
grant create public synonym, drop public synonym to PPPCORE;
grant create materialized view to PPPCORE;
--7--
select * from sys.dba_sequences where sequence_owner='PPPCORE';

--13. select created tables and cluster--
select * from dba_tables where owner='PPPCORE';
select * from dba_clusters;

select * from dba_sys_privs where grantee='PPP_PDB_ADMIN';
select * from dba_sys_privs where grantee='PPPCORE';