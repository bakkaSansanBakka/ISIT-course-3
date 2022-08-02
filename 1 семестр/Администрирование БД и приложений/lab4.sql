--1. all pdbs--
select PDB_NAME, STATUS from dba_pdbs;

--2. all instances--
select * from v$instance;

--3. all installed components--
select COMP_ID, cOMP_NAME, VERSION, STATUS from dba_registry;

--4. create pdb in database configuration manager--

--5. all pdbs--
select PDB_NAME, STATUS from dba_pdbs;

--6. connect to PPP_PDB via SQL Developer--