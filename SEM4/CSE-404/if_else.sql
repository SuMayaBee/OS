declare 
character varchar2(1) := '&char';
begin
if (character >= 'A' and character <= 'Z')
then
dbms_output.put_line('Upper case');
elsif (character >= 'a' and character <= 'z')
then
 dbms_output.put_line('Lower case');
elsif (character >= '0' and character <= '9')
 then
 dbms_output.put_line('Digit');
else
 dbms_output.put_line('Special character');
end if;
end;
/
