alter session set "_ORACLE_SCRIPT" = true;

select * from dba_sys_privs where grantee like 'PPP_PDB%';

grant connect to PPP_PDB_admin;