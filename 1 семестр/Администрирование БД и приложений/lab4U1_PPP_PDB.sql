create table PPP_table
(
  C1 int,
  C2 varchar(10)
);

insert into PPP_table(C1, C2) values (1, 'str1');
insert into PPP_table(C1, C2) values(2, 'str2');

select * from PPP_table;
select * from user_role_privs;