--6. Create structure objects--
create tablespace TS_PPP_PDB
  datafile 'C:\app\Tablespaces\ts_PPP_PDB1.dbf'
  size 7m
  autoextend on next 5m
  maxsize 20m;

create temporary tablespace TS_PPP_PDB_TEMP
  tempfile 'C:\app\Tablespaces\ts_PPP_PDB_TEMP.dbf'
  size 5m
  autoextend on next 3m
  maxsize 30m;
  
alter session set "_ORACLE_SCRIPT" = true;
create role RL_PPP_PDBCORE;
grant create session,
      create table,
      drop any table,
      create view,
      drop any view,
      create procedure,
      drop any procedure to RL_PPP_PDBCORE;
      
create profile PF_PPP_PDBCORE limit
password_life_time 180
sessions_per_user 3
failed_login_attempts 7
password_lock_time 1
password_reuse_time 10
password_grace_time default
connect_time 180 
idle_time 30;

select * from dba_profiles;
select * from dba_profiles where profile like 'PF%';

create user U1_PPP_PDB identified by 12345
default tablespace TS_PPP_PDB quota unlimited on TS_PPP_PDB
temporary tablespace TS_PPP_PDB_TEMP
profile PF_PPP_PDBCORE
account unlock;
grant RL_PPP_PDBCORE to U1_PPP_PDB;

drop user U1_PPP_PDB;

select * from dba_tablespaces;
select * from dba_data_files;
select * from dba_sys_privs;
select * from dba_sys_privs where grantee like 'RL%';
select * from dba_roles;
select * from dba_profiles;
select * from dba_role_privs;
select * from dba_role_privs where grantee like 'PPP%' or grantee like 'U1%';

select * from v$session;