--1
select * from v$sga;
select * from v$sga_dynamic_components;

--2
select * from v$parameter;

--3
select * from v$controlfile;

--4
--show parameter spfile;
--create pfile = 'test_pfile_exam.ora' from spfile = 'SPFILEORCL.ORA';

--5
select * from T1;
select * from dba_segments where segment_name = 'T1';

--MIDDLE LEVEL--

--1
select * from orders;
select * from customers;
select * from products;

select cust customer from orders;

create or replace procedure 
  listOfOrders(customer_name customers.company%type)
is
  qty number := 0;
  amnt number := 0;
  
  cursor curs is select description, orders.qty quantity, orders.amount amount
    from orders join customers on orders.cust = customers.cust_num 
      join products on orders.product = products.product_id where customers.company = customer_name;
  begin
    for rec in curs
      loop
        dbms_output.put_line(rec.description);
        qty := qty + rec.quantity;
        amnt := amnt + rec.amount;
      end loop;
    dbms_output.put_line('final average price: ' || to_char(amnt/qty));
  exception
    when others then
      dbms_output.put_line('error: ' || sqlerrm);
  end;
  
begin
  listOfOrders('Ace International');
end;

--2
select * from orders;
select * from customers;
select * from products;

alter session set NLS_DATE_FORMAT='YYYY-MM-DD';

create or replace function 
  ordersAmountForDateInterval (customer_name customers.company%type,
                                start_date orders.order_date%type,
                                end_date orders.order_date%type)
return number is
  amount number;
  begin
    select count(*) into amount from orders join customers on orders.cust = customers.cust_num
              where customers.company = customer_name 
              and orders.order_date between start_date and end_date;
    return amount;
  end;
  
select ordersAmountForDateInterval('Ace International', '2008-01-28', '2008-02-26') from dual;

--3
select * from orders;
select * from customers;
select * from products;

create or replace procedure listOfProductsAndSum (customer_name customers.company%type)
is
cursor curs is select description, orders.amount amount 
  from orders join customers on orders.cust = customers.cust_num 
              join products on orders.product = products.product_id
  where customers.company = customer_name
  order by orders.amount desc;
begin
  for rec in curs
    loop
      dbms_output.put_line('product: ' || rec.description || ', amount: ' || rec.amount);
    end loop;
end;

begin
  listOfProductsAndSum('Ace International');
end;

--4
select * from orders;
select * from customers;
select * from products;

create or replace function orderAmountForDatePeriod (start_date orders.order_date%type,
                                                      end_date orders.order_date%type)
return number is
  amount number;
  begin
    select count(*) into amount from orders 
      where order_date between start_date and end_date;
    return amount;
  end;
  
begin
  dbms_output.put_line('orders amount: ' || to_char(orderAmountForDatePeriod('2007-12-27', '2008-01-24')));
end;

--5
select * from orders;
select * from customers;
select * from products;

create or replace procedure listOfCustomersDesc (start_date orders.order_date%type,
                                                  end_date orders.order_date%type)
is
cursor curs is select company, sum(orders.amount) amountSum
  from orders join customers on orders.cust = customers.cust_num
  where orders.order_date between start_date and end_date
  group by company
  order by sum(orders.amount) desc;
begin
  for rec in curs
    loop
      dbms_output.put_line('customer: ' || rec.company || ', sum amount: ' || rec.amountSum);
    end loop;
end;

begin
  listOfCustomersDesc('2007-10-12', '2007-12-27');
end;

--6
create or replace function amountOfOrdersPeriod (start_date orders.order_date%type,
                                                  end_date orders.order_date%type)
return number is
amount number;
begin
  select count(*) into amount from orders where order_date between start_date and end_date;
  return amount;
end;

begin
  dbms_output.put_line('amount of goods: ' || amountOfOrdersPeriod('2007-12-12', '2008-02-12'));
end;

--7
create or replace procedure listOfCustomersPeriod(start_date orders.order_date%type,
                                                  end_date orders.order_date%type)
is
cursor curs is select distinct company 
  from orders join customers on orders.cust = customers.cust_num
    where orders.order_date between start_date and end_date;
begin
  for rec in curs
    loop
      dbms_output.put_line(rec.company);
    end loop;
  exception
    when others then
      dbms_output.put_line('error: ' || sqlerrm);
end;

begin
  listOfCustomersPeriod('2007-12-12', '2008-01-01');
end;

--8
select * from orders;
select * from customers;
select * from products;

create or replace function amountOfCustomersProd (product_name products.description%type)
return number is
amount number;
begin
  select count(*) into amount 
    from orders join products on orders.product = products.product_id
    where products.description = product_name;
  return amount;
end;

begin
  dbms_output.put_line('amount of customers: ' || to_char(amountOfCustomersProd('Ratchet Link')));
end;

--9
select * from products;

create or replace procedure increaseProdPrice (product_name products.description%type)
is
begin
  update products set price = price + price * 0.1 where description = product_name;
  
  exception
    when others then
      dbms_output.put_line('error: ' || sqlerrm);
end;

begin
  increaseProdPrice ('Ratchet Link');
end;

--10
select * from customers;
select * from orders;

create or replace function amountOrdersForYearCustomer 
  (customer_name customers.company%type, orderYear int)
return number is
amount number;
begin
  select count(*) into amount from orders join customers on orders.cust = customers.cust_num
    where customers.company = customer_name and extract(year from order_date) = orderYear;
  return amount;
end;

begin
  dbms_output.put_line('amount of orders: ' || amountOrdersForYearCustomer('JCP Inc.', 2007));
end;