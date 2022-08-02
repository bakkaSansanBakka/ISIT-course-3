--1. procedure: print teachers which work at pulpit in parameter--
declare
  procedure get_teachers(pcode teacher.pulpit%type)
    is
      cursor teachers_cursor
        is select * from teacher where pulpit = pcode;
      begin
        for rec in teachers_cursor
          loop
            dbms_output.put_line(rec.teacher);
          end loop;
      end;
begin
  get_teachers('????');
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--2. function: return amount of teachers which work at pulpit in parameter--
declare
  function get_num_teachers(pcode teacher.pulpit%type) return number is
    num number(10);
    begin
      select count(*) into num from teacher where pulpit = pcode;
      return num;
    end;
begin
  dbms_output.put_line('amount of techers in ????: ' || get_num_teachers('????'));
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--3. procedure: print teachers which work at faculty in parameter--
declare
  procedure get_teachers(fcode faculty.faculty%type)
    is
      cursor teachers_cursor
        is select * from teacher join pulpit on teacher.pulpit = pulpit.pulpit
          where pulpit.faculty = fcode;
      begin
        for rec in teachers_cursor
          loop
            dbms_output.put_line(rec.teacher);
          end loop;
      end;
begin
  get_teachers('???');
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--procedure: print subjects belong to pulpit in parameter--

declare
  procedure get_subjects(pcode subject.pulpit%type)
  is
    cursor subject_cursor
      is select * from subject where pulpit = pcode;
    begin
      for rec in subject_cursor
        loop
          dbms_output.put_line(rec.subject);
        end loop;
    end;
begin
  get_subjects('??????');
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--4. function: return amount of teachers work in faculty in parameter--
declare
  function get_num_teachers(fcode faculty.faculty%type) return number is
    num number(10);
    begin
      select count(*) into num from teacher join pulpit 
        on teacher.pulpit = pulpit.pulpit 
          where pulpit.faculty = fcode;
      return num;
    end;
begin
  dbms_output.put_line('amount of techers in ????: ' || get_num_teachers('????'));
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--function: get amount of subjects belong to pulpit in parameter--
declare
  function get_num_subjects(pcode subject.pulpit%type) return number is
    num number(10);
    begin
      select count(*) into num from subject where pulpit = pcode;
      return num;
    end;
begin
  dbms_output.put_line('amount of subjects belong to ????: ' || get_num_subjects('????'));
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--5. create package with procedures and functions--
create or replace package teachers as
  procedure get_teachers(fcode faculty.faculty%type);
  procedure get_subjects(pcode subject.pulpit%type);
  function get_num_teachers(fcode faculty.faculty%type) return number;
  function get_num_subjects(pcode subject.pulpit%type) return number;
end;

create or replace package body teachers is
  
  procedure get_teachers(fcode faculty.faculty%type)
    is
      cursor teachers_cursor
        is select * from teacher join pulpit on teacher.pulpit = pulpit.pulpit
          where pulpit.faculty = fcode;
      begin
        for rec in teachers_cursor
          loop
            dbms_output.put_line(rec.teacher);
          end loop;
      end;
    
  procedure get_subjects(pcode subject.pulpit%type)
  is
    cursor subject_cursor
      is select * from subject where pulpit = pcode;
    begin
      for rec in subject_cursor
        loop
          dbms_output.put_line(rec.subject);
        end loop;
    end;
  
  function get_num_teachers(fcode faculty.faculty%type) return number is
    num number(10);
    begin
      select count(*) into num from teacher join pulpit 
        on teacher.pulpit = pulpit.pulpit 
          where pulpit.faculty = fcode;
      return num;
    end;
  
  function get_num_subjects(pcode subject.pulpit%type) return number is
    num number(10);
    begin
      select count(*) into num from subject where pulpit = pcode;
      return num;
    end;
end;

--6. package use--
begin
  teachers.get_teachers('???');
  dbms_output.put_line('');
  teachers.get_subjects('??????');
  dbms_output.put_line('');
  dbms_output.put_line('amount of techers in ????: ' || teachers.get_num_teachers('????'));
  dbms_output.put_line('amount of subjects belong to ????: ' || teachers.get_num_subjects('????'));
end;