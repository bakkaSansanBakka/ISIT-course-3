--B4--
--1--
select * from products;

declare
procedure proc(prod products.product_id%type)
  is
  begin
    update products set price = price + price * 0.1 where product_id = prod;
  end;
begin
  proc('2A45C');

exception
  when others
    then dbms_output.put_line('error: ' || sqlerrm);
end;

select * from products;

--2--
select * from orders;

declare
function func(customer orders.cust%type, order_year int) return number is
num number(10);
begin
  select count(*) into num from orders 
    where cust = customer and extract(year from order_date) - order_year = 0;
  return num;
end;
begin
  dbms_output.put_line('amount: ' || func('2112', 2008));
end;