select distinct customer_name 
from depositor D, account A 
where D.account_number = A.account_number 
and (branch_name) in 
(select branch_name from branch where branch_city='BROOKLYN')
group by customer_name 
having count(*)= (select count(branch_name) from branch where branch_city='BROOKLYN');
