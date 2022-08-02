--Procedures

--1. AddProduct
create or replace procedure AddProduct
(p_name products.name%type, 
p_price products.price%type, 
p_manufacturer_id products.manufacturer_id%type, 
p_supplier_id products.supplier_id%type, 
p_amount products.amount%type, 
p_product_type products.product_type%type)
is
begin
    insert into PRODUCTS(name, price, manufacturer_id, supplier_id, amount, product_type) 
    VALUES(p_name, p_price, p_manufacturer_id, p_supplier_id, p_amount, p_product_type);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--2. DeleteProduct
create or replace procedure DeleteProduct(p_id products.id%type)
is
begin
    delete from products where products.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--3. UpdateProduct
create or replace procedure UpdateProduct
(p_id products.id%type, 
p_name products.name%type, 
p_price products.price%type, 
p_manufacturer_id products.manufacturer_id%type, 
p_supplier_id products.supplier_id%type, 
p_amount products.amount%type, 
p_product_type products.product_type%type)
is
begin
    update products set id = p_id, 
		name = p_name, 
		price = p_price, 
		manufacturer_id = p_manufacturer_id, 
		supplier_id = p_supplier_id, 
		amount = p_amount, 
		product_type = p_product_type
	where products.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--4. AddProductType
create or replace procedure AddProductType(p_type product_types.type%type)
is
begin
    insert into PRODUCT_TYPES(type) 
    VALUES(p_type);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--5. DeleteProductType
create or replace procedure DeleteProductType(p_id product_types.id%type)
is
begin
    delete from product_types where product_types.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--6. UpdateProductType
create or replace procedure UpdateProductType
(p_id product_types.id%type, 
p_type product_types.type%type)
is
begin
    update product_types set id = p_id, 
		type = p_type
	where product_types.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--7. AddSupplier
create or replace procedure AddSupplier
(p_company_name suppliers.сompany_name%type,
p_adress suppliers.adress%type,
p_phone_number suppliers.phone_number%type)
is
begin
    insert into SUPPLIERS(сompany_name, adress, phone_number) 
    VALUES(p_company_name, p_adress, p_phone_number);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--8. DeleteSupplier
create or replace procedure DeleteSupplier(p_id suppliers.id%type)
is
begin
    delete from suppliers where suppliers.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--9. UpdateSupplier
create or replace procedure UpdateSupplier
(p_id suppliers.id%type, 
p_company_name suppliers.сompany_name%type,
p_adress suppliers.adress%type,
p_phone_number suppliers.phone_number%type)
is
begin
    update suppliers set id = p_id, 
		сompany_name = p_company_name,
		adress = p_adress,
		phone_number = p_phone_number
	where suppliers.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--10. AddManufacturer
create or replace procedure AddManufacturer
(p_company_name manufacturers.сompany_name%type,
p_adress manufacturers.adress%type,
p_phone_number manufacturers.phone_number%type)
is
begin
    insert into MANUFACTURERS(сompany_name, adress, phone_number) 
    VALUES(p_company_name, p_adress, p_phone_number);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--11. DeleteManufacturer
create or replace procedure DeleteManufacturer(p_id manufacturers.id%type)
is
begin
    delete from manufacturers where manufacturers.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--12. UpdateManufacturer
create or replace procedure UpdateManufacturer
(p_id manufacturers.id%type, 
p_company_name manufacturers.сompany_name%type,
p_adress manufacturers.adress%type,
p_phone_number manufacturers.phone_number%type)
is
begin
    update manufacturers set id = p_id, 
		сompany_name = p_company_name,
		adress = p_adress,
		phone_number = p_phone_number
	where manufacturers.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--13. AddStore
create or replace procedure AddStore(p_address stores.address%type)
is
begin
    insert into STORES(address) 
    VALUES(p_address);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--14. DeleteStore
create or replace procedure DeleteStore(p_id stores.id%type)
is
begin
    delete from stores where stores.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--15. UpdateStore
create or replace procedure UpdateStore
(p_id stores.id%type, 
p_address stores.address%type)
is
begin
    update stores set id = p_id, 
		address = p_address
	where stores.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--16. AddSalesman
create or replace procedure AddSalesman
(p_name salesmen.name%type,
p_surname salesmen.surname%type,
p_patronymic salesmen.patronymic%type,
p_adress salesmen.adress%type,
p_phone_number salesmen.phone_number%type)
is
begin
    insert into SALESMEN(name,
		surname,
		patronymic,
		adress,
		phone_number) 
    VALUES(p_name, p_surname, p_patronymic, p_adress, p_phone_number);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--17. DeleteSalesman
create or replace procedure DeleteSalesman(p_id salesmen.id%type)
is
begin
    delete from salesmen where salesmen.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--18. UpdateSalesman
create or replace procedure UpdateSalesman
(p_id salesmen.id%type, 
p_name salesmen.name%type,
p_surname salesmen.surname%type,
p_patronymic salesmen.patronymic%type,
p_adress salesmen.adress%type,
p_phone_number salesmen.phone_number%type)
is
begin
    update salesmen set id = p_id, 
		name = p_name,
		surname = p_surname,
		patronymic = p_patronymic,
		adress = p_adress,
		phone_number = p_phone_number
	where salesmen.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--19. AddClient
create or replace procedure AddClient
(p_nickname clients.nickname%type,
p_name clients.name%type,
p_surname clients.surname%type,
p_patronymic clients.patronymic%type,
p_email clients.email%type,
p_adress clients.adress%type,
p_phone_number clients.phone_number%type)
is
begin
    insert into CLIENTS(nickname,
		name,
		surname,
		patronymic,
		email,
		adress,
		phone_number) 
    VALUES(p_nickname, p_name, p_surname, p_patronymic, p_email, p_adress, p_phone_number);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--20. DeleteClient
create or replace procedure DeleteClient(p_id clients.id%type)
is
begin
    delete from clients where clients.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--21. UpdateClient
create or replace procedure UpdateClient
(p_id clients.id%type, 
p_nickname clients.nickname%type,
p_name clients.name%type,
p_surname clients.surname%type,
p_patronymic clients.patronymic%type,
p_email clients.email%type,
p_adress clients.adress%type,
p_phone_number clients.phone_number%type)
is
begin
    update clients set id = p_id, 
		nickname = p_nickname,
		name = p_name,
		surname = p_surname,
		patronymic = p_patronymic,
		email = p_email,
		adress = p_adress,
		phone_number = p_phone_number
	where clients.id = p_id;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--22. AddOrder
create or replace procedure AddOrder
(p_salesman_id orders.salesman_id%type,
p_client_id orders.client_id%type,
p_product_id orders.product_id%type,
p_amount orders.amount%type,
p_store_id orders.store_id%type,
p_order_date orders.order_date%type)
is
begin
    insert into ORDERS(salesman_id,
		client_id,
		product_id,
		amount,
		store_id,
		order_date) 
    VALUES(p_salesman_id,
	p_client_id,
	p_product_id,
	p_amount,
	p_store_id,
	p_order_date);
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--23. DeleteOrder
create or replace procedure DeleteOrder(p_order_number orders.order_number%type)
is
begin
    delete from orders where orders.order_number = p_order_number;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--24. UpdateOrder
create or replace procedure UpdateOrder
(p_order_number orders.order_number%type, 
p_salesman_id orders.salesman_id%type,
p_client_id orders.client_id%type,
p_product_id orders.product_id%type,
p_amount orders.amount%type,
p_store_id orders.store_id%type,
p_order_date orders.order_date%type)
is
begin
    update orders set order_number = p_order_number, 
		salesman_id = p_salesman_id,
		client_id = p_client_id,
		product_id = p_product_id,
		amount = p_amount,
		store_id = p_store_id,
		order_date = p_order_date
	where orders.order_number = p_order_number;
    exception
    when others 
    then DBMS_OUTPUT.put_line(sqlerrm);
end;

--25. Export Suppliers to Xml
create or replace directory XMLDATAREPOSITORY AS 'C:/app';

create or replace procedure ExportSupplierstoXml
is
DOC DBMS_XMLDOM.DOMDocument;
XDATA XMLTYPE;
CURSOR XMLCUR IS
SELECT XMLELEMENT("SUPPLIERS",
XMLAttributes('http://www.w3.org/2001/XMLSchema' AS "xmlns:xsi",
'http://www.oracle.com/Users.xsd' AS "xsi:nonamespaceSchemaLocation"),
XMLAGG(XMLELEMENT("SUPPLIERS",
xmlelement("id", SUPPLIERS.id),
xmlelement("сompany_name", SUPPLIERS.сompany_name),
xmlelement("adress", SUPPLIERS.adress),
xmlelement("phone_number", SUPPLIERS.phone_number)
))) from SUPPLIERS;
begin
open xmlcur;
loop
fetch xmlcur into xdata;
exit when xmlcur%notfound;
end loop;
close xmlcur;
DOC := DBMS_XMLDOM.NewDOMDocument(XDATA);
DBMS_XMLDOM.WRITETOFILE(DOC, 'XMLDATAREPOSITORY/Suppliers.xml');
END;

--26. Import Xml data to Suppliers
create or replace procedure ImportSuppliersDataFromXml
IS
L_CLOB CLOB;
L_BFILE BFILE := BFILENAME('XMLDATAREPOSITORY', 'Suppliers.xml');

L_DEST_OFFSET INTEGER := 1;
L_SRC_OFFSET INTEGER := 1;
L_BFILE_CSID NUMBER := 0;
L_LANG_CONTEXT INTEGER := 0;
L_WARNING INTEGER := 0;

P DBMS_XMLPARSER.PARSER;
v_doc dbms_xmldom.domdocument;
v_root_element dbms_xmldom.domelement;
V_CHILD_NODES DBMS_XMLDOM.DOMNODELIST;
V_CURRENT_NODE DBMS_XMLDOM.DOMNODE;

et SUPPLIERS%rowtype;
begin
DBMS_LOB.CREATETEMPORARY (L_CLOB, TRUE);
DBMS_LOB.FILEOPEN(L_BFILE, DBMS_LOB.FILE_READONLY);

DBMS_LOB.LOADCLOBFROMFILE (DEST_LOB => L_CLOB, SRC_BFILE => L_BFILE, AMOUNT => DBMS_LOB.LOBMAXSIZE,
DEST_OFFSET => L_DEST_OFFSET, SRC_OFFSET => L_SRC_OFFSET, BFILE_CSID => L_BFILE_CSID,
LANG_CONTEXT => L_LANG_CONTEXT, WARNING => L_WARNING);
DBMS_LOB.FILECLOSE(L_BFILE);
COMMIT;
P := Dbms_Xmlparser.Newparser;
DBMS_XMLPARSER.PARSECLOB(P,L_CLOB);
V_DOC := DBMS_XMLPARSER.GETDOCUMENT(P);
V_ROOT_ELEMENT := DBMS_XMLDOM.Getdocumentelement(v_Doc);
V_CHILD_NODES := DBMS_XMLDOM.GETCHILDRENBYTAGNAME(V_ROOT_ELEMENT,'*');

FOR i IN 0 .. DBMS_XMLDOM.GETLENGTH(V_CHILD_NODES) - 1
LOOP
V_CURRENT_NODE := DBMS_XMLDOM.ITEM(V_CHILD_NODES,i);

DBMS_XSLPROCESSOR.VALUEOF(V_CURRENT_NODE,'id/text()',et.id);
Dbms_Xslprocessor.Valueof(V_Current_Node,'сompany_name/text()',et.сompany_name);
Dbms_Xslprocessor.Valueof(V_Current_Node,'adress/text()',et.adress);
dbms_xslprocessor.valueof(v_current_node,'phone_number/text()',et.phone_number);

insert into SUPPLIERS(сompany_name, adress, phone_number)
values(et.сompany_name, et.adress, et.phone_number);
end loop;

DBMS_LOB.FREETEMPORARY(L_CLOB);
DBMS_XMLPARSER.FREEPARSER(P);
DBMS_XMLDOM.FREEDOCUMENT(V_DOC);
commit;
END;