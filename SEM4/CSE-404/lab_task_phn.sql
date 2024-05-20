drop table phn_table;
drop table modified;

create table phn_table
(
phone varchar2(40)
);

create table modified
(
modified varchar2(40)
);

insert into phn_table values ('1235767834');
insert into phn_table values ('1267567867');
insert into phn_table values ('1234567894');
insert into phn_table values ('5234567892');

create or replace procedure format
(p_val in out varchar2) IS
BEGIN
p_val := '('||substr(p_val, 1,3)||')'||substr(p_val,4,2)||'-'||substr(p_val, 6,2)||'-'||substr(p_val, 8);
insert into modified values (p_val);
end format;
/

declare
cursor c_zip is
select * from phn_table;
v_zip c_zip%rowtype;
BEGIN
open c_zip;
fetch c_zip into v_zip;
while c_zip%found
loop
format(v_zip.phone);
fetch c_zip into v_zip;
end loop;
close c_zip;
end;
/
