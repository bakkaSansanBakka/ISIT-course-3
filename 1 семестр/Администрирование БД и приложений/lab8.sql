--1. sqlnet.ora and tnsnames.ora--
--C:\app\oracleUser\product\12.1.0\dbhome_1\NETWORK\ADMIN--

--2. connect to oracle as SYSTEM via sqlplus--
--connect /as sysdba--
--connect system as sysdba--
--show parameters--

--3. sqlplus pdb--
--connect /as sysdba--
--connect system/system1@//localhost:1521/PPP_PDB as sysdba;--

--select tablespace_name from dba_tablespaces;--
--select file_name from dba_data_files;
--select role from dba_roles;--
--select username from dba_users;

--4. params in HKEY_LOCAL_MACHINE/SOFTWARE/ORACLE--
--regedit--

--5. create local pdb name via creating connection string via Oracle Net Manager--

--6. SQLPLUS connect using created connection string--

--7. select from any owned table--
--select * from logstdby$parameters;

--8. amount of time to select from table--
set timing on;
select tablespace_name from dba_tables;
set timing off;

--9. describe command--
--describe logstdby$parameters;--

--10. all segments--
--select segment_name from user_segments;

--11. create view--
create view PPP_PDB_VIEW as
select segment_name, blocks, extents, bytes from dba_segments;

select * from segments;