--1.permanent tablespace--
create tablespace TS_PPP
  datafile 'C:\app\Tablespaces\ts_PPP.dbf'
  size 7m
  autoextend on next 5m
  maxsize 20m;
  
drop tablespace TS_PPP;
  
--2.temporary tablespace--
create temporary tablespace TS_PPP_TEMP
  tempfile 'C:\app\Tablespaces\ts_PPP_TEMP.dbf'
  size 5m
  autoextend on next 3m
  maxsize 30m;

drop tablespace TS_PPP_TEMP;
  
--3.list of all tablespaces, files from dictionary--
select * from dba_tablespaces;
select * from dba_data_files;

--4.create a role--
alter session set "_ORACLE_SCRIPT" = true;
create role RL_PPPCORE;
grant create session,
      create table,
      drop any table,
      create view,
      drop any view,
      create procedure,
      drop any procedure to RL_PPPCORE;
      
drop role RL_PPPCORE;

--5.select role from a dictionary, all system privs, roles--
select * from dba_roles where role like 'RL%';
select * from dba_sys_privs where grantee like 'RL%';
select * from dba_roles;

--6.create profile--
create profile PF_PPPCORE limit
password_life_time 180
sessions_per_user 3
failed_login_attempts 7
password_lock_time 1
password_reuse_time 10
password_grace_time default
connect_time 180 
idle_time 30;

drop profile PF_PPPCORE;

--7.list of all profiles, list of all params of a profile,
--values of all params of default profile--
select * from dba_profiles;
select * from dba_profiles where profile like 'PF%';
select * from dba_profiles where profile like 'DEFAULT';

--8.create user--
create user PPPCORE identified by 12345
default tablespace TS_PPP quota unlimited on TS_PPP
temporary tablespace TS_PPP_TEMP
profile PF_PPPCORE
account unlock
password expire;
grant RL_PPPCORE to PPPCORE;

drop user PPPCORE;

--9.sqlplus new password for user--

--10.create for user a table and a view--

--11.create offline tablespace, --
create tablespace PPPCORE_QDATA 
  offline
  datafile 'C:\app\Tablespaces\PPPCORE_QDATA.dbf'
  size 10m
  autoextend on next 3m
  maxsize 30m

alter tablespace PPPCORE_QDATA online;
alter user PPPCORE quota 2m on PPPCORE_QDATA;
