-- create table sailor(
-- sid number,
-- sname varchar2(20),
-- rate number,
-- age number,
-- constraint sailor_pk primary key (sid)
-- );

-- create table boat(
-- bid number,
-- bname varchar2(20),
-- color varchar2(20),
-- constraint boat_pk primary key (bid)
-- );

-- create table reserves(
-- sid number,
-- bid number,
-- day date,
-- constraint reserves_pk primary key (sid,bid),
-- constraint reserves_fk1 foreign key (sid) references sailor(sid),
-- constraint reserves_fk2 foreign key (bid) references boat(bid)
-- );

-- insert into sailor values (22, 'Dustin', 65.6, 7);
-- and other sample tuples 

-- 1st question
select sname from sailor S, reserves R where S.sid = R.sid and bid = 103;

-- 2nd question
select sname from sailor S, reserves R, boat B where S.sid = R.sid and R.bid = B.bid and color = 'red';

-- 3rd question
select color from boat where bid in (select bid from reservers where sid =(select sid from sailor where sname = 'Lubber'));

-- 4th question
select sname from sailor where sid in (select sid from reserves);

-- 5th question
(select sname from sailor S, reserves R, boat B where S.sid = R.sid and R.bid = B.bid and color = 'red') intersect (select sname from sailor S, reserves R, boat B where S.sid = R.sid and R.bid = B.bid and color = 'green');
