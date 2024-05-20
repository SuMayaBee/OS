declare
cursor c_zip is
select * from employee;
v_zip c_zip%rowtype;
begin
open c_zip;
fetch c_zip into v_zip;
while c_zip%found
loop
if v_zip.salary*12>10000
then
insert into new1 values (v_zip.id, v_zip.salary);
end if;
fetch c_zip into v_zip;
end loop;
close c_zip;
end;
/
