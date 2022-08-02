--1. range partition--
create table T_RANGE
(
  id number,
  str nvarchar2(20)
)
partition by range (id)
(
  partition two values less than (2),
  partition four values less than (4),
  partition six values less than (6),
  partition maxval values less than (maxvalue)
);

insert into T_RANGE(id, str) values(1, 'str1');
insert into T_RANGE(id, str) values(2, 'str2');
insert into T_RANGE(id, str) values(3, 'str3');
insert into T_RANGE(id, str) values(4, 'str4');
insert into T_RANGE(id, str) values(5, 'str5');
insert into T_RANGE(id, str) values(6, 'str6');

select * from T_RANGE;
select * from T_RANGE partition (maxval);

--2. interval partition--
create table T_INTERVAL
(
  id number,
  dat date
)
partition by range (dat)
interval (numtoyminterval(1,'year'))
(
  partition p0 values less than (to_date('1-1-2000', 'DD-MM-YYYY'))
);

insert into T_INTERVAL (id, dat) values (1, to_date('2-2-2001', 'DD-MM-YYYY'));
insert into T_INTERVAL (id, dat) values (1, to_date('12-5-1999', 'DD-MM-YYYY'));
insert into T_INTERVAL (id, dat) values (1, to_date('1-1-2000', 'DD-MM-YYYY'));
insert into T_INTERVAL (id, dat) values (1, to_date('22-3-1997', 'DD-MM-YYYY'));

select * from T_INTERVAL;
select * from T_INTERVAL partition (p0);

--3. hash partition--
create table T_HASH
(
  id number,
  str varchar2 (20)
)
partition by hash (str)
(
  partition p0,
  partition p1,
  partition p2,
  partition p3
);

insert into T_HASH (id, str) values (1, 'str1');
insert into T_HASH (id, str) values (2, 'str2');
insert into T_HASH (id, str) values (3, 'str3');
insert into T_HASH (id, str) values (4, 'str4');
insert into T_HASH (id, str) values (5, 'str5');
insert into T_HASH (id, str) values (6, 'str6');

select * from T_HASH;
select * from T_HASH partition (p0);
select * from T_HASH partition (p2);

--4. list partition--
create table T_LIST
(
  id number,
  num number
)
partition by list (num)
(
  partition p0 values (3,5),
  partition p1 values (1,4),
  partition pdefault values (default)
);

insert into T_LIST (id, num) values (1, 1);
insert into T_LIST (id, num) values (2, 2);
insert into T_LIST (id, num) values (3, 3);
insert into T_LIST (id, num) values (4, 4);
insert into T_LIST (id, num) values (5, 5);
insert into T_LIST (id, num) values (6, 6);

select * from T_LIST;
select * from T_LIST partition (p0);
select * from T_LIST partition (p1);

--6. update section key--
alter table T_RANGE enable row movement;
update T_RANGE set id = 7 where id = 3;
select * from T_RANGE partition (maxval);

alter table T_INTERVAL enable row movement;
update T_INTERVAL set dat = to_date('22-3-2002', 'DD-MM-YYYY') 
  where dat = to_date('22-3-1997', 'DD-MM-YYYY');
select * from T_INTERVAL partition (p0);

alter table T_HASH enable row movement;
update T_HASH set str = 'str10' where str = 'str1';
select * from T_HASH partition (p0);

alter table T_LIST enable row movement;
update T_LIST set num = 7 where num = 3;
select * from T_LIST;
select * from T_LIST partition (p0);

--7. alter table merge--
alter table T_RANGE merge partitions two, four into partition sixSec;
select * from T_RANGE partition(sixSec);

--8. alter table split--
alter table T_RANGE split partition sixSec into
(
  partition two values less than (2),
  partition four
);
select * from T_RANGE partition(two);
select * from T_RANGE partition(four);

--9. alter table exchange--
create table T_RANGE2
(
  id number,
  str nvarchar2(20)
);

alter table T_RANGE exchange partition six with table T_RANGE2 without validation;

select * from T_RANGE;
select * from T_RANGE2;