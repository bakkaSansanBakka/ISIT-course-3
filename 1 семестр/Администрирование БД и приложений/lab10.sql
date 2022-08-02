--1. simple anonymous PL/SQL block--
begin
  null;
end;

--2. Hello World!--
begin
  dbms_output.put_line('Hello World!');
end;

--3. exceptions, sqlerm, sqlcode--
declare
  x number (3) := 3;
  y number (3) := 0;
  z number (10, 2);
begin
    dbms_output.put_line('x = ' ||x || ', y = ' ||y);
    z := x/y;
    dbms_output.put_line('z = ' ||z);
  exception
    when others
    then dbms_output.put_line('error = ' ||sqlerrm || '; code = ' ||sqlcode);
end;

--4. nested block--
declare
  x number (3) := 3;
  y number (3) := 0;
  z number (10, 2);
begin
    dbms_output.put_line('x = ' ||x || ', y = ' ||y);
    begin
      z := x/y;
      exception
        when others
        then dbms_output.put_line('error = ' ||sqlerrm || '; code = ' ||sqlcode);
    end;
  dbms_output.put_line('z = ' ||z);
end;

--5. compile warnings--
select * from v$parameter where name = 'plsql_warnings';

--6. special symbols in PL/SQL--
select * from v$reserved_words where reserved = 'Y' and length = 1;

--7. reserved words in PL/SQL--
select * from v$reserved_words where reserved = 'Y' and length != 1;

--8. parameters of PL/SQL--
select * from v$parameter where name like 'plsql%';

--in SQL plus--
show parameter plsql;

--9. anonymous block that shows:
declare
  num1 number(3) := 20;
  num2 number(3) := 5;
  fixedNum number(4,2) := 10.51;
  fixedNumWithRound number(10,-2) := 104353.51;
  binary_float_variable binary_float := 12455.5236;
  binary_double_variable binary_double := 12455.5236;
  e_number number(20,10) := 123456789E-5;
  bool boolean := false;
begin
  --10. declare integers
  dbms_output.put_line('num1 = ' || num1);
  dbms_output.put_line('num2 = ' || num2);  
  --11. ariphmetic operations
  dbms_output.put_line('num1 % num2 = ' || mod(num1, num2));
  --12. number with fixed point
  dbms_output.put_line('fixedNum = ' || fixedNum);
  --13. number with fixed point and negative scale
  dbms_output.put_line('fixedNumWithRound = ' || fixedNumWithRound);
  --14. binary_float variable
  dbms_output.put_line('binary_float_variable = ' || binary_float_variable);
  --15. binary_double variable
  dbms_output.put_line('binary_double_variable = ' || binary_double_variable);
  --16. number with E
  dbms_output.put_line('number with E = ' || e_number);
  --17. boolean variable
  if bool then dbms_output.put_line('boolean variable = true'); end if;
  if not bool then dbms_output.put_line('boolean variable = false'); end if;
  if bool is null then dbms_output.put_line('bool is null'); end if;
end;

--18. const declare--
declare
  n1 constant number(5) := 5;
  v1 constant varchar2(20) not null default 'Hello';
  c1 constant char := 'c';
begin
    n1 := 10;
  exception
   when others
    then dbms_output.put_line('error = ' ||n1);
end;

--19, 20. %TYPE, %ROWTYPE--
declare 
  faculty sys.faculty.faculty%type;
  faculty_rec sys.faculty%rowtype;
begin
  faculty := '???';
  faculty_rec.faculty := '????';
  faculty_rec.faculty_name := '??????????? ???? ? ??????????';
  
  dbms_output.put_line(faculty);
  dbms_output.put_line(faculty_rec.faculty || ': ' || faculty_rec.faculty_name);
exception
  when others
    then dbms_output.put_line('error = ' ||sqlerrm);
end;

--21, 22. if--
declare 
  num number(10) := 10;
begin
  if num > 20
    then dbms_output.put_line(num || ' > 20');
  elsif num = 15
    then dbms_output.put_line(num || ' = 15');
  else
    dbms_output.put_line(num || ' < 20');
  end if;
end;

--23. case--
declare 
  num number(10) := 10;
begin
  case
    when num > 20 then dbms_output.put_line('num > 20');
    when num = 15 then dbms_output.put_line('num = 15');
    else dbms_output.put_line('else block');
  end case;
  
  case num
    when 5 then dbms_output.put_line('no, 5');
    when 10 then dbms_output.put_line('yes, 10');
    else dbms_output.put_line('else block');
  end case;
end;

--24. loop--
declare
  x pls_integer := 0;
begin
  loop
    x := x + 1;
    dbms_output.put_line(x);
  exit when x > 5;
  end loop;
end;

--25. while--
declare
  x pls_integer := 5;
begin
  while (x > 0)
    loop
      x := x - 1;
      dbms_output.put_line(x);
    end loop;
end;

--26. for--
declare
  x pls_integer := 0;
begin
  for i in 1..5
    loop
      x := x + 1;
      dbms_output.put_line(x);
    end loop;
end;