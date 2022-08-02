--Tables and sequences creation

-- 1. PRODUCT_ID sequence and PRODUCTS table
CREATE sequence PRODUCT_ID_SEQ;
CREATE TABLE PRODUCTS (
	Id INT DEFAULT PRODUCT_ID_SEQ.NEXTVAL NOT NULL,
  name NVARCHAR2(200) NOT NULL,
	price DECIMAL(10) NOT NULL,
  manufacturer_id INT NOT NULL,
  supplier_id INT NOT NULL,
  amount int NOT NULL,
  product_type int NOT NULL,
	constraint PRODUCT_PK PRIMARY KEY (Id));
     
-- 2. MANUFACTURER_ID sequence and MANUFACTURERS table
CREATE sequence MANUFACTURER_ID_SEQ;
CREATE TABLE MANUFACTURERS (
	Id INT DEFAULT MANUFACTURER_ID_SEQ.NEXTVAL NOT NULL,
	сompany_name NVARCHAR2(200) NOT NULL,
	adress NVARCHAR2(200) NOT NULL,
	phone_number NVARCHAR2(50) NOT NULL,
	constraint MANUFACTURER_PK PRIMARY KEY (Id));
    
-- 3. SUPPLIER_ID sequence and SUPPLIERS table
CREATE sequence SUPPLIER_ID_SEQ;
CREATE TABLE SUPPLIERS (
	Id INT DEFAULT SUPPLIER_ID_SEQ.NEXTVAL NOT NULL,
	сompany_name NVARCHAR2(200) NOT NULL,
	adress NVARCHAR2(200) NOT NULL,
	phone_number NVARCHAR2(50) NOT NULL,
	constraint SUPPLIER_PK PRIMARY KEY (Id));

-- 4. CLIENT_ID sequence and CLIENTS table
CREATE sequence CLIENT_ID_SEQ;
CREATE TABLE CLIENTS (
	Id INT DEFAULT CLIENT_ID_SEQ.NEXTVAL NOT NULL,
	nickname NVARCHAR2(200) NOT NULL,
	name NVARCHAR2(50) NOT NULL,
	surname NVARCHAR2(50) NOT NULL,
	patronymic NVARCHAR2(50) NOT NULL,
  email NVARCHAR2(200),
	adress NVARCHAR2(100) NOT NULL,
	phone_number NVARCHAR2(100) UNIQUE NOT NULL,
	constraint CLIENT_PK PRIMARY KEY (id));
  
-- 5. SALESMAN_ID sequence and SALESMEN table
CREATE sequence SALESMAN_ID_SEQ;
CREATE TABLE SALESMEN (
	Id INT DEFAULT SALESMAN_ID_SEQ.NEXTVAL NOT NULL,
	name NVARCHAR2(50) NOT NULL,
	surname NVARCHAR2(50) NOT NULL,
	patronymic NVARCHAR2(50) NOT NULL,
	adress NVARCHAR2(100) NOT NULL,
	phone_number NVARCHAR2(50) UNIQUE NOT NULL,
	constraint SALESMEN_PK PRIMARY KEY (id));
  
-- 6. PRODUCT_TYPE_ID sequence and PRODUCT_TYPES table
CREATE sequence PRODUCT_TYPE_ID_SEQ;
CREATE TABLE PRODUCT_TYPES (
	Id INT DEFAULT PRODUCT_TYPE_ID_SEQ.NEXTVAL NOT NULL,
	type NVARCHAR2(200) NOT NULL,
	constraint PRODUCT_TYPES_PK PRIMARY KEY (id));
  
-- 7. STORE_ID sequence and STORES table
CREATE sequence STORE_ID_SEQ;
CREATE TABLE STORES (
	Id INT DEFAULT STORE_ID_SEQ.NEXTVAL NOT NULL,
	address NVARCHAR2(200) NOT NULL,
	constraint STORES_PK PRIMARY KEY (id));
  
-- 8. ORDER_NUMBER sequence and ORDERS table
CREATE sequence ORDER_NUMBER_SEQ;
CREATE TABLE ORDERS (
	order_number INT DEFAULT ORDER_NUMBER_SEQ.NEXTVAL NOT NULL,
	salesman_id int NOT NULL,
  client_id int NOT NULL,
  product_id int NOT NULL,
  amount int NOT NULL,
  store_id int NOT NULL,
  order_date date NOT NULL,  
	constraint ORDERS_PK PRIMARY KEY (order_number));

ALTER TABLE PRODUCTS ADD CONSTRAINT PRODUCTS_FK1 FOREIGN KEY (manufacturer_id) 
  REFERENCES MANUFACTURERS(Id);
ALTER TABLE PRODUCTS ADD CONSTRAINT PRODUCTS_FK2 FOREIGN KEY (supplier_id) 
  REFERENCES SUPPLIERS(Id);
ALTER TABLE PRODUCTS ADD CONSTRAINT PRODUCTS_FK3 FOREIGN KEY (product_type) 
  REFERENCES PRODUCT_TYPES(Id);
  
ALTER TABLE ORDERS ADD CONSTRAINT ORDERS_FK1 FOREIGN KEY (salesman_id) 
  REFERENCES SALESMEN(Id);
ALTER TABLE ORDERS ADD CONSTRAINT ORDERS_FK2 FOREIGN KEY (client_id) 
  REFERENCES CLIENTS(Id);
ALTER TABLE ORDERS ADD CONSTRAINT ORDERS_FK3 FOREIGN KEY (store_id) 
  REFERENCES STORES(Id);
ALTER TABLE ORDERS ADD CONSTRAINT ORDERS_FK4 FOREIGN KEY (product_id) 
  REFERENCES PRODUCTS(Id);
  
--Triggers creation

--1. Manufacturer id before insert trigger
create or replace trigger MANUFACTURER_ID_BI
    before insert on MANUFACTURERS for each row
begin
    if :new.ID is null then
        :new.ID := MANUFACTURER_ID_SEQ.nextval;
    end if;
end;

--2. Product type id before insert trigger
create or replace trigger PRODUCT_TYPE_ID_BI
    before insert on PRODUCT_TYPES for each row
begin
    if :new.ID is null then
        :new.ID := PRODUCT_TYPE_ID_SEQ.nextval;
    end if;
end;

--3. Salesman id before insert trigger
create or replace trigger SALESMAN_ID_BI
    before insert on SALESMEN for each row
begin
    if :new.ID is null then
        :new.ID := SALESMAN_ID_SEQ.nextval;
    end if;
end;

--4. Client id before insert trigger
create or replace trigger CLIENT_ID_BI
    before insert on CLIENTS for each row
begin
    if :new.ID is null then
        :new.ID := CLIENT_ID_SEQ.nextval;
    end if;
end;

--5. Supplier id before insert trigger
create or replace trigger SUPPLIER_ID_BI
    before insert on SUPPLIERS for each row
begin
    if :new.ID is null then
        :new.ID := SUPPLIER_ID_SEQ.nextval;
    end if;
end;

--6. Store id before insert trigger
create or replace trigger STORE_ID_BI
    before insert on STORES for each row
begin
    if :new.ID is null then
        :new.ID := STORE_ID_SEQ.nextval;
    end if;
end;

--7. Product id before insert trigger
create or replace trigger PRODUCT_ID_BI
    before insert on PRODUCTS for each row
begin
    if :new.ID is null then
        :new.ID := PRODUCT_ID_SEQ.nextval;
    end if;
end;

--8. Order number before insert trigger
create or replace trigger ORDER_NUMBER_BI
    before insert on ORDERS for each row
begin
    if :new.order_number is null then
        :new.order_number := ORDER_NUMBER_SEQ.nextval;
    end if;
end;