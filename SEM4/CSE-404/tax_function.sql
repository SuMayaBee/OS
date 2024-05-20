create or replace function tax(p_val in number)
return number
is
temp number;
begin
select commission_pct into temp from employees where salary = p_val;
return 0.08*(12*(NVL(temp, 0)*p_val + p_val));
end tax;
/
