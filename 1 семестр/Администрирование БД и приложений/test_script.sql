--B2--

--1--
select * from orders;
select * from products;

declare 
  procedure get_products(customer orders.cust%type)
    is
      cursor orders_curs is select description, amount from orders join products
        on product_id = product where cust = customer
        order by amount desc;
      begin
        for order_ in orders_curs
          loop
            dbms_output.put_line('product: ' || order_.description || ', amount: ' 
              || order_.amount); 
          end loop;
      end;
begin
  get_products(2112);

exception
  when others
    then dbms_output.put_line('error: ' || sqlerrm);
end;

--2--
declare
  function orders_amount(starting_date orders.order_date%type, 
                          ending_date orders.order_date%type)
  return number is
    num number(10);
    begin
      select count(*) into num from orders where order_date > starting_date 
        and order_date < ending_date;
      return num;
    end;
begin
  dbms_output.put_line('count: ' || orders_amount('2007-12-17', '2008-01-17'));
end;

--B4--

--1--
select * from orders;
select * from customers;
select * from products;

declare
  procedure customers_date(starting_date orders.order_date%type, 
                            ending_date orders.order_date%type)
  is
    cursor orders_cursor is 
      select company from orders join customers on orders.cust = customers.cust_num
        where order_date > starting_date and order_date < ending_date;
  begin
    for rec in orders_cursor
      loop
        dbms_output.put_line('customer: ' || rec.company);
      end loop;
  
    exception
      when others
        then dbms_output.put_line('error: ' || sqlerrm);
    
  end;
begin
  customers_date('2007-12-17', '2007-12-31');
end;

--2--
select * from orders;
select * from customers;
select * from products;

declare
  function get_customers_amount(product_param products.product_id%type)
  return number is
    num number(10);
    begin
      select count(*) into num from orders where product = product_param;
      return num;
    end;
begin
  dbms_output.put_line('customers amount: ' || get_customers_amount('114'));
end;