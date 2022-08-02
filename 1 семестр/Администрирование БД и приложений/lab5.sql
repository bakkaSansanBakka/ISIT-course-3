--1. all tablespaces datafiles including temporary and permanent--
select * from dba_data_files;
select * from dba_temp_files;
alter session set "_ORACLE_SCRIPT" = true;

--2.create tablespace--
create tablespace PPP_QDATA 
  offline
  datafile 'C:\app\Tablespaces\PPP_QDATA.dbf'
  size 10m
  autoextend on next 3m
  maxsize 30m
  
alter tablespace PPP_QDATA online;
alter user PPPCORE quota 2m on PPP_QDATA;

--7. all extents in database--
select * from dba_extents;

--8. delete tablespace--
drop tablespace PPP_QDATA including contents and datafiles;

--9. groups of redo logs--
select GROUP#, MEMBERS, STATUS from v$log;
select * from v$log;

--10. all instance redo logs --
select * from v$logfile;

--11. switch redo logs--
alter system switch logfile;
select GROUP#, SEQUENCE#, bytes, MEMBERS, STATUS, first_change# from v$log;

alter system switch logfile;
select GROUP#, SEQUENCE#, bytes, MEMBERS, STATUS, first_change# from v$log;

alter system switch logfile;
select GROUP#, SEQUENCE#, bytes, MEMBERS, STATUS, first_change# from v$log;

--12.create redo logs group--
alter database add logfile group 4 'C:\app\oracleUser\oradata\orcl\REDO04.LOG'
size 50m blocksize 512;
alter database add logfile member 'C:\app\oracleUser\oradata\orcl\REDO041.LOG' to group 4;
alter database add logfile member 'C:\app\oracleUser\oradata\orcl\REDO042.LOG' to group 4;

select GROUP#, SEQUENCE#, bytes, MEMBERS, STATUS, first_change# from v$log;

alter system switch logfile;
select GROUP#, SEQUENCE#, bytes, MEMBERS, STATUS, first_change# from v$log;

--13. delete redo logs group--
alter database drop logfile member 'C:\app\oracleUser\oradata\orcl\REDO041.LOG';
alter database drop logfile member 'C:\app\oracleUser\oradata\orcl\REDO042.LOG';
alter database drop logfile member 'C:\app\oracleUser\oradata\orcl\REDO04.LOG';
alter database drop logfile group 4;

--14. is archive running--
select name, log_mode from v$database;
select instance_name, archiver, active_state from v$instance;

--15. number of the latest log--
select * from v$archived_log;

--16. turn on archivelog--
shutdown immediate;
startup mount;
alter database archievelog;
alter database open;

--17. create archieved log--
select * from v$log;
select recid, name, first_change# from v$archived_log;

--18. turn off archievelog--
shutdown immediate;
startup mount;
alter database noarchivelog;
select name, log_mode from v$database;

--19. list control files--
select * from v$controlfile;

--20. content of control file--
select * from v$controlfile_record_section;

--21. parameter file of instance--
select name, value, description from v$parameter;

--22. create PFILE--
create PFILE = 'PPP_PFILE.ORA' from SPFILE;

--23. password file--
--oracleUser/product/12.1.0/dbhome_1/database/PWDorcl.ora--

--24. list directories for diagnostic and message logs--
select * from v$diag_info;

--25. log.xml contents--