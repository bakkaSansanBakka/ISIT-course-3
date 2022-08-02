--IMPLICIT CURSORS--

select * from faculty;

--1. precise sampling--
declare 
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec from faculty where faculty = '???';
  dbms_output.put_line(faculty_rec.faculty || ': ' || faculty_rec.faculty_name);
end;

--2. imprecise samling--
declare 
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec from faculty;
  dbms_output.put_line(faculty_rec.faculty || ': ' || faculty_rec.faculty_name);
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--3. when too_many_rows--
declare 
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec from faculty;
  dbms_output.put_line(faculty_rec.faculty || ': ' || faculty_rec.faculty_name);
  exception
    when too_many_rows
      then dbms_output.put_line('too many rows in sampling: ' || sqlcode);
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--4. when no_data_found--
declare 
  faculty_rec faculty%rowtype;
begin
  select * into faculty_rec from faculty where faculty = 'XXX';
  dbms_output.put_line(faculty_rec.faculty || ': ' || faculty_rec.faculty_name);
  exception
    when no_data_found
      then dbms_output.put_line('no suitable data found: ' || sqlcode);
    when too_many_rows
      then dbms_output.put_line('too many rows in sampling: ' || sqlcode);
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

select * from auditorium;
--5. update + commit/rollback--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
  auditorium_cur auditorium%rowtype;
begin
  update auditorium set auditorium = '316-4', 
                        auditorium_name = '316-4',
                        auditorium_capacity = 90,
                        auditorium_type = '??'
        where auditorium = '201-1';
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  dbms_output.put_line(auditorium_cur.auditorium_name || ' ' ||
                        auditorium_cur.auditorium_capacity || ' ' ||
                        auditorium_cur.auditorium_type);
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--6. UPDATE + commit/rollback + integrity violation--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
  auditorium_cur auditorium%rowtype;
begin
  update auditorium set auditorium = '314-4', 
                        auditorium_name = '314-4',
                        auditorium_capacity = 90,
                        auditorium_type = '??'
        where auditorium = '201-1';
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  dbms_output.put_line(auditorium_cur.auditorium_name || ' ' ||
                        auditorium_cur.auditorium_capacity || ' ' ||
                        auditorium_cur.auditorium_type);
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--7. INSERT + commit/rollback--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
  auditorium_cur auditorium%rowtype;
begin
  insert into auditorium (auditorium, auditorium_name, auditorium_type, auditorium_capacity)
    values ('202-1', '202-1', '??-?', 15);
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  dbms_output.put_line(auditorium_cur.auditorium_name || ' ' ||
                        auditorium_cur.auditorium_capacity || ' ' ||
                        auditorium_cur.auditorium_type);
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

select * from auditorium;

--8. INSERT + commit/rollback + integrity violation--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
  auditorium_cur auditorium%rowtype;
begin
  insert into auditorium (auditorium, auditorium_name, auditorium_type, auditorium_capacity)
    values ('201-1', '201-1', '??-?', 15);
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  dbms_output.put_line(auditorium_cur.auditorium_name || ' ' ||
                        auditorium_cur.auditorium_capacity || ' ' ||
                        auditorium_cur.auditorium_type);
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--9. DELETE + commit/rollback--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
begin
  delete auditorium where auditorium = '201-1';
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--10. DELETE + commit/rollback + integrity violation--
declare
  b1 boolean;
  b2 boolean;
  b3 boolean;
  n pls_integer;
begin
  delete auditorium where auditorium = '401-1';
  b1 := sql%found;
  b2 := sql%isopen;
  b3 := sql%notfound;
  n := sql%rowcount;
  if b1 then dbms_output.put_line('b1 = true');
    else dbms_output.put_line('b1 = false');
  end if;
  if b2 then dbms_output.put_line('b2 = true');
    else dbms_output.put_line('b2 = false');
  end if;
  if b3 then dbms_output.put_line('b3 = true');
    else dbms_output.put_line('b3 = false');
  end if;
  dbms_output.put_line('n = ' || n);
  --commit;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--EXPLICIT CURSORS--

select * from teacher;

--11. print TEACHERS with loop and cursor--
declare 
  cursor teacher_cursor is select teacher, teacher_name, pulpit from teacher;
  cteacher        sys.teacher.teacher%type;
  cteacher_name   sys.teacher.teacher_name%type;
  cpulpit         sys.teacher.pulpit%type;
begin
  open teacher_cursor;
  dbms_output.put_line('rowcount = ' || teacher_cursor%rowcount);
  loop
    fetch teacher_cursor into cteacher, cteacher_name, cpulpit;
    exit when teacher_cursor%notfound;
    dbms_output.put_line(teacher_cursor%rowcount || ' ' ||
                          cteacher || ' ' ||
                          cteacher_name || ' ' ||
                          cpulpit);
  end loop;
  dbms_output.put_line('rowcount = ' || teacher_cursor%rowcount);
  close teacher_cursor;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--12. print SUBJECT with while loop and cursor using %ROWTYPE--
select * from subject;

declare 
  cursor subject_cursor is select subject, subject_name, pulpit from subject;
  rec_subject sys.subject%rowtype;
begin
  open subject_cursor;
  dbms_output.put_line('rowcount = ' || subject_cursor%rowcount);
  fetch subject_cursor into rec_subject;
  while subject_cursor%found
  loop
    dbms_output.put_line(subject_cursor%rowcount || ' ' ||
                          rec_subject.subject || ' ' ||
                          rec_subject.subject_name || ' ' ||
                          rec_subject.pulpit);
    fetch subject_cursor into rec_subject;
  end loop;
  dbms_output.put_line('rowcount = ' || subject_cursor%rowcount);
  close subject_cursor;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--13. print PULPIT join TEACHER using for loop--
declare 
  cursor teapit_cursor is select t.teacher, t.teacher_name, 
                                t.pulpit, p.pulpit_name, p.faculty 
                          from teacher t inner join pulpit p on t.pulpit = p.pulpit;
  rec             teapit_cursor%rowtype;
begin
  for rec in teapit_cursor
  loop
    dbms_output.put_line(teapit_cursor%rowcount || ' ' ||
                          rec.teacher || ' ' ||
                          rec.teacher_name || ' ' ||
                          rec.pulpit || ' ' ||
                          rec.pulpit_name || ' ' ||
                          rec.faculty);
  end loop;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--14. cursor with params--
--loop, exit when-
declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max;
  cauditorium             sys.auditorium.auditorium%type;
  cauditorium_capacity    sys.auditorium.auditorium_capacity%type;
begin
  open auditorium_cursor(0, 20);
  loop
    fetch auditorium_cursor into cauditorium, cauditorium_capacity;
    exit when auditorium_cursor%notfound;
    dbms_output.put_line(auditorium_cursor%rowcount || ' ' ||
                          cauditorium || ' ' ||
                          cauditorium_capacity);
  end loop;
  dbms_output.put_line('rowcount = ' || auditorium_cursor%rowcount);
  close auditorium_cursor;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--while loop--
declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max;
  cauditorium             sys.auditorium.auditorium%type;
  cauditorium_capacity    sys.auditorium.auditorium_capacity%type;
begin
  open auditorium_cursor(0, 20);
  fetch auditorium_cursor into cauditorium, cauditorium_capacity;
  while (auditorium_cursor%found)
  loop
    dbms_output.put_line(auditorium_cursor%rowcount || ' ' ||
                          cauditorium || ' ' ||
                          cauditorium_capacity);
    fetch auditorium_cursor into cauditorium, cauditorium_capacity;
  end loop;
  dbms_output.put_line('rowcount = ' || auditorium_cursor%rowcount);
  close auditorium_cursor;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--for loop--
declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max;
  --rec auditorium_cursor%rowtype;
begin
  for rec in auditorium_cursor(0, 20)
  loop
    dbms_output.put_line(auditorium_cursor%rowcount || ' ' ||
                          rec.auditorium || ' ' ||
                          rec.auditorium_capacity);
  end loop;
  dbms_output.put_line('rowcount = ' || auditorium_cursor%rowcount);
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--15. refcursor--
declare
  xcurs sys_refcursor;
  rec auditorium_type%rowtype;
begin
  open xcurs for select * from auditorium_type;
  fetch xcurs into rec;
  while (xcurs%found)
    loop
      dbms_output.put_line(rtrim(rec.auditorium_type) || ' ' || 
                            rtrim(rec.auditorium_typename));
      fetch xcurs into rec;
    end loop;
  close xcurs;
  exception
    when others
      then dbms_output.put_line('error: ' || sqlerrm);
end;

--16. cursor subquery--
declare
  cursor curs_aut is
    select auditorium_type,
            cursor (
                    select auditorium from auditorium aum
                      where aut.auditorium_type = aum.auditorium_type
                    )
      from auditorium_type aut;
  curs_aum sys_refcursor;
  aut auditorium_type.auditorium_type%type;
  aum auditorium.auditorium%type;
  txt varchar2(1000);
begin
  open curs_aut;
  fetch curs_aut into aut, curs_aum;
  while (curs_aut%found)
    loop
      txt := rtrim(aut) || ': ';
      loop
        fetch curs_aum into aum;
        exit when curs_aum%notfound;
        txt := txt || ', ' || rtrim(aum);
      end loop;
      dbms_output.put_line(txt);
      fetch curs_aut into aut, curs_aum;
    end loop;
  close curs_aut;
exception
  when others
    then dbms_output.put_line('error: ' || sqlerrm);
end;

--17. decrease auditorium capacity, UPDATE CURRENT OF--
declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max
      for update;
begin
  for rec in auditorium_cursor(40, 80)
  loop
    update auditorium set auditorium_capacity = auditorium_capacity * 0.9
      where current of auditorium_cursor;
    dbms_output.put_line(rec.auditorium || ' ' ||
                          rec.auditorium_capacity);
  end loop;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--18. while, delete current of--
select * from auditorium;

declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max
      for update;
  aum auditorium.auditorium%type;
  cty auditorium.auditorium_capacity%type;
begin
  open auditorium_cursor(0, 20);
  fetch auditorium_cursor into aum, cty;
  while (auditorium_cursor%found)
    loop
      delete auditorium where current of auditorium_cursor;
      fetch auditorium_cursor into aum, cty;
    end loop;
  close auditorium_cursor;
  
  for rec in auditorium_cursor(0, 100)
    loop
      dbms_output.put_line(rec.auditorium || ' ' ||
                            rec.auditorium_capacity);
    end loop;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--19. rowid with update and delete--
declare 
  cursor auditorium_cursor (capacity_min sys.auditorium.auditorium%type, 
                            capacity_max sys.auditorium.auditorium%type) 
    is select auditorium, auditorium_capacity, rowid from auditorium 
      where auditorium_capacity >= capacity_min and auditorium_capacity <= capacity_max
      for update;
  aum auditorium.auditorium%type;
  cty auditorium.auditorium_capacity%type;
begin
  for xxx in auditorium_cursor(20,40)
    loop
      case
        when xxx.auditorium_capacity >= 35
          then delete auditorium where rowid = xxx.rowid;
        when xxx.auditorium_capacity < 35
          then update auditorium set auditorium_capacity = auditorium_capacity + 3
              where rowid = xxx.rowid;
      end case;
    end loop;
  for rec in auditorium_cursor(0, 100)
    loop
      dbms_output.put_line(rec.auditorium || ' ' ||
                            rec.auditorium_capacity);
    end loop;
  rollback;
  exception
    when others
      then dbms_output.put_line('error = ' || sqlerrm);
end;

--20. print all teachers--
declare
  cursor teacher_cursor is select * from teacher;
  counter int := 0;
begin
  for rec in teacher_cursor
    loop
      if counter = 3 
        then dbms_output.put_line('-------------------------');
        counter := 0;
      end if;
      counter := counter + 1;
      dbms_output.put_line(rec.teacher_name || ' ' || rec.pulpit);
    end loop;
end;