--1. background processes--
select paddr, name, description from v$bgprocess;

--2. running background processes--
select paddr, name, description from v$bgprocess 
  where paddr != hextoraw('00');
  
--3. running DBWn processes number--
select paddr, name, description from v$bgprocess 
  where paddr != hextoraw('00') and (name like 'DBW%' or name like 'BW%');
  
--4. current connections to instance--
select saddr, audsid, username, status, osuser, program, type from v$session;

--5. connection mode--
select username, service_name, server from v$session;

--6. services--
select name, network_name, pdb from v$services;

--7. dispatcher parameters--
show parameter dispatcher;

--8. Windows service that implements LISTENER process--
--task manager -> services -> OracleOraDB12Home1TNSListener--

--9. current connections to instance--
select saddr, audsid, username, server, status, osuser, program, type from v$session;

--10. LISTENER.ORA file contents--
--app\oracleUser\product\12.1.0\dbhome_1\NETWORK\ADMIN\listener.ora--

--11. lsnrctl utility--
--app\oracleUser\product\12.1.0\dbhome_1\BIN\LSNRCTL.exe--

--12. list of instance services served by LISTENER process--
--command 'services' in LSNRCTL.exe--