create or replace procedure format_phone
(phone_number in out varchar2)
is
begin
phone_number := '(' || substr(phone_number, 1, 3)||
                ')' || substr(phone_number, 4, 3)||
                '-' || substr(phone_number, 7);
end;
/
declare 
p_number varchar2(15);
begin
select phone_number into p_number from phone_number where id = 1;
format_phone(p_number);
insert into modified_phone_number values (p_number);
dbms_output.put_line(p_number);
end;
/
