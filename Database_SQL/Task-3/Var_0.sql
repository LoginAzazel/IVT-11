drop database orlov;
create database orlov;
use orlov;

drop trigger if exists `insertДети`;
drop trigger if exists `deleteДети`;
drop trigger if exists `updateДети`;
drop function if exists setCursor;
drop function if exists setCound;
drop function if exists getCound;
drop table if exists `Дети`;
drop table if exists `Группы`;
drop table if exists `Персонал`;

create table `Персонал`(
	`Табельный №` int primary key,
	`ФИО работника` varchar(40) not null,
	`Должность` varchar(50) not null,
	`Оклад, руб.` int not null
);

create table `Группы`(
	`№ группы` char(1) primary key,
	`Название группы` varchar(40) not null,
	`Табельный № воспитателя` int not null,
	`Количество детей в группе` int not null default 0,
	foreign key (`Табельный № воспитателя`) references `Персонал`(`Табельный №`) on delete no action on update cascade
);

create table `Дети`(
	`№ порядковый` int primary key auto_increment,
	`ФИО ребенка` varchar(40) not null,
	`Дата рождения` date not null,
	`№ группы` char(1) not null,
	foreign key (`№ группы`) references `Группы`(`№ группы`) on delete no action on update cascade
) auto_increment=1001;

insert into `Персонал`(`Табельный №`, `ФИО работника`, `Должность`, `Оклад, руб.`)
values (108, 'Самохина В.П.', 'Ст. воспитатель', 32000),
	   (110, 'Фирсова М.В.', 'Воспитатель', 27000),
	   (102, 'Фролова Н.Г.', 'Воспитатель', 27000),
	   (107, 'Самохвалова И.В.', 'Воспитатель', 27000),
	   (120, 'Фурманов Н.И.', 'Зав. детским садиком', 52000);

insert into `Группы`(`№ группы`, `Название группы`, `Табельный № воспитателя`)
values ('М', 'Младшая', 102),
	   ('С', 'Средняя', 107),
	   ('П', 'Подготовительная', 108),
	   ('Я', 'Ясельная', 110);

insert into `Дети`(`ФИО ребенка`, `Дата рождения`, `№ группы`)
values ('Иванов Алёша', '2014-10-30', 'С'),
	   ('Сидорова Наташа', '2014-02-27', 'С'),
	   ('Петрова Катя', '2014-09-17', 'С'),
	   ('Петров Артём', '2016-07-23', 'М'),
	   ('Фролов Антон', '2016-12-31', 'М'),
	   ('Федорова Ирина', '2013-09-12', 'П');

delimiter //
create function getCound(number char(1)) returns int
deterministic
begin
declare s int;
select count(`№ порядковый`) into s from `Дети` where `№ группы`=number;
return ifnull(s, 0);
end//
delimiter ;

select * from `Дети`;
select getCound('С');

delimiter //
create procedure setCound()
begin
update `Группы` set `Количество детей в группе`=getCound(`№ группы`);
end//
delimiter ;

call setCound();
select * from `Группы`;
 
delimiter // 
create procedure `setCursor`() 
BEGIN 
	DECLARE n char(1);
    DECLARE s, b INT default 0; 
	DECLARE cur1 CURSOR FOR SELECT `№ группы`, count(`№ группы`) FROM `Дети` group by `№ группы`;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET b = 1; 
    update `Дети` set `Количество детей в группе`=0;
	OPEN cur1; 
    WHILE b = 0 DO 
        FETCH cur1 INTO n, s; 
		update `Дети` set `Количество детей в группе`=s where `№ группы`=n;
    END WHILE; 
    CLOSE cur1; 
END // 
delimiter ;

call setCound();
select * from `Группы`;

insert into `Дети`(`ФИО ребенка`, `Дата рождения`, `№ группы`)
values ('Васильев Виталик', '2014-09-30', 'С');
select * from `Дети`;
select * from `Группы`;

delimiter //
create trigger `deleteДети` after delete on `Дети` for each row
begin
	update `Группы` set `Количество детей в группе` = `Количество детей в группе`-1 where `№ группы`=OLD.`№ группы`;
end//
delimiter ;

delete from `Дети` where `№ порядковый`=1004;
select * from `Дети`;
select * from `Группы`;

delimiter //
create trigger `updateДети` after update on `Дети` for each row
begin
	if OLD.`№ группы` != NEW.`№ группы` then 
		update `Группы` set `Количество детей в группе` = `Количество детей в группе`-1 where `№ группы`=OLD.`№ группы`;
		update `Группы` set `Количество детей в группе` = `Количество детей в группе`+1 where `№ группы`=NEW.`№ группы`;
	end if;
end//
delimiter ;

update `Дети` set `№ группы`='М' where `№ порядковый`=1006;
select * from `Дети`;
select * from `Группы`;

