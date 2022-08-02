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