begin
  for r in 1..100000
    loop
      AddSupplier('test_company_name', 'test_address', 'test_phone_number');
    end loop;
end;

select * from suppliers;

declare
  time1 number := dbms_utility.get_time();
begin
  for r in (select * from suppliers where id > 35000 and id < 55000)
    loop 
      null;
    end loop;
    dbms_output.put_line('elapsed time: ' || (dbms_utility.get_time() - time1)/100);
end;

create index supplier_id_index on suppliers(id);

begin
  AddSupplier('company 1', 'address 1', 'phone number 1');
  AddSupplier('company 2', 'address 2', 'phone number 2');
end;
commit;

delete from suppliers;
select * from suppliers;

begin
  ExportSupplierstoXml();
end;

begin
  importsuppliersdatafromxml();
end;