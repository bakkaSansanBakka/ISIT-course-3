--table to load data to--
create table LoadTable
(
  str nvarchar2(100),
  num number,
  datet date check (extract(month from datet) = 12)
);

drop table LoadTable;

select * from LoadTable;

sqlldr control='lab18Loader.ctl' userid=SYSTEM/system1