--1. overall SGA size--
select * from v$sga; -- partly
select sum(value) from v$sga;

--2. current sizes of SGA main pools--
--3. granule size for every pool--
select component, current_size, granule_size from v$sga_dynamic_components;

--4. SGA free space size--
select * from v$sga_dynamic_free_memory;

--5. sizes of KEEP, DEFAULT, RECYCLE pools of buffer cache--
select component, current_size, granule_size from v$sga_dynamic_components 
  where component like 'KEEP%';
select component, current_size, granule_size from v$sga_dynamic_components
  where component like 'DEFAULT buffer%';
select component, current_size, granule_size from v$sga_dynamic_components
  where component like 'RECYCLE%';
  
--6. create table and put it into KEEP pool, show table segment--
create table PPP (k int) storage(buffer_pool keep) tablespace users;
insert into PPP values (1);
select segment_name, segment_type, tablespace_name, buffer_pool 
  from user_segments where segment_name='PPP';
  
--7. create table that will be cached in default pool, show table segment--
create table CCC (k int) cache storage(buffer_pool default) tablespace users;
insert into CCC values(1);
select segment_name, segment_type, tablespace_name, buffer_pool 
  from user_segments where segment_name='CCC';
  
--8. log buffer size--
select name, value, description from v$parameter where name='log_buffer';

--9. 10 biggest objects in shared pool--
select * from (select pool, name, bytes from v$sgastat where pool='shared pool' 
  order by bytes desc) where rownum <= 10;
  
--or

select pool, name, bytes from v$sgastat where pool='shared pool' 
  order by bytes desc fetch next 10 rows only;
  
--10. large pool free space--
select * from v$sgastat where pool='large pool' and name='free memory';

--11. all connections to instance--
select saddr, audsid, username, status, osuser, program, type from v$session;

--12. connection mode--
select username, service_name, server from v$session;

--13*. most used db objects--
select name, type, executions from v$db_object_cache order by executions desc;