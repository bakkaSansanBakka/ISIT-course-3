--2. sequence 1--
create sequence S1
  increment by 10
  start with 1000
  nominvalue
  nomaxvalue
  nocycle
  nocache
  noorder;
  
select S1.nextval from dual;
select S1.nextval from dual;
select S1.nextval from dual;
select S1.nextval from dual;

select S1.currval from dual;

--3. create sequence 2--
create sequence S2
  increment by 10
  start with 10
  nominvalue
  maxvalue 100
  cycle
  nocache
  noorder;
  
drop sequence S2;

--4. get sequence 2 values--
select S2.nextval from dual;

--5. create sequence 3--
create sequence S3
  increment by -10
  start with 10
  minvalue -100
  maxvalue 10
  nocycle
  nocache
  order;

select S3.nextval from dual;
select S3.currval from dual;

drop sequence S3;

--6. create sequence 4--
create sequence S4
  increment by 1
  start with 1
  minvalue 1
  maxvalue 10
  cycle
  cache 5
  noorder;
  
select S4.nextval from dual;

drop sequence S4;

--7. all sequences in database--
select * from sys.dba_sequences where sequence_owner='PPPCORE';

--8. table--
create table T1
(
  N1 number(20),
  N2 number(20),
  N3 number(20),
  N4 number(20)
) cache storage (buffer_pool keep)

begin
  for i in 1..7
    loop
      insert into T1 (N1, N2, N3, N4)
        values (S1.nextval, S2.nextval, S3.nextval, S4.nextval);
    end loop;
end;

select * from T1;
drop table T1;

--9. create hash cluster--
create cluster ABC 
(
  X number(10),
  V varchar2(12)
) hashkeys 200;

--10. create table A from cluster--
create table A 
(
  XA number(10),
  Va varchar2(12),
  Ca number(10)
) cluster ABC (Xa, Va);

drop table A;

--11. create table B from cluster--
create table B 
(
  Xb number(10),
  Vb varchar2(12),
  Cb number(10)
) cluster ABC (Xb, Vb);

drop table B;

--12. create table C from cluster--
create table C 
(
  Xc number(10),
  Vc varchar2(12),
  Cc number(10)
) cluster ABC (Xc, Vc);

drop table C;

--13. select created tables and cluster--
select * from dba_tables where owner='PPPCORE';
select * from dba_clusters;

--14. create synonym--
create synonym C_TABLE for C;
select * from C_TABLE;

--15. create public synonym--
create public synonym B_TABLE for B;

--16. tables TABLE1 and TABLE2, view V1--
create table TABLE1
(
  COL1 int,
  COL2 int,
  foreign key (COL2) references TABLE2(COL1)
)

create table TABLE2
(
  COL1 int primary key,
  COL2 varchar(10)
)

insert into TABLE2(COL1, COL2) values (1, 'str1');
insert into TABLE2(COL1, COL2) values (2, 'str2');
insert into TABLE2(COL1, COL2) values (3, 'str3');

insert into TABLE1(COL1, COL2) values (10, 1);
insert into TABLE1(COL1, COL2) values (11, 2);
insert into TABLE1(COL1, COL2) values (12, 3);

select * from TABLE1;
select * from TABLE2;

drop table TABLE1;
drop table TABLE2;

create view V1 as select TABLE2.COL1 COL1, TABLE1.COL1 COL2 from TABLE1 inner join TABLE2 
  on TABLE1.COL2 = TABLE2.COL1;
  
select * from V1;

--17. materialized view--
drop materialized view MV;

create materialized view MV
build immediate
refresh complete start with (sysdate) next (sysdate + 2/1440)
as select TABLE2.COL1 COL1, TABLE1.COL1 COL2 from TABLE1 inner join TABLE2 
  on TABLE1.COL2 = TABLE2.COL1;
  
select * from MV;