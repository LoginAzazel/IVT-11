CREATE DATABASE Task_3
USE Task_3

DROP TABLE IF EXISTS `Договора`;
DROP TABLE IF EXISTS `Работники предприятия`;
DROP TABLE IF EXISTS `Распределение работников`;
DROP TABLE IF EXISTS `Распределение работников1`;

CREATE TABLE `Договора`
(
	`№ договора` VARCHAR(10) NOT NULL,
	`Название организации` VARCHAR(50),
	`Адрес месторосположения` VARCHAR(50),
	`Сумма договора` INT,
	PRIMARY KEY(`№ договора`)
);

CREATE TABLE `Работники предприятия`
(
	`Табельный №` INT NOT NULL,
	`ФИО` VARCHAR(99) NOT NULL,
	`Профессия` VARCHAR(20),
	`Количество отработанных дней` INT,
	PRIMARY KEY(`Табельный №`)
);

CREATE TABLE `Распределение работников`
(
	`№ договора` VARCHAR(10) NOT NULL,
	`Дата` DATE,
	`Табельный №` INT NOT NULL,
	PRIMARY KEY(`Дата`),
	FOREIGN KEY(`№ договора`)
		REFERENCES `Договора`(`№ договора`)
		ON DELETE RESTRICT ON UPDATE CASCADE,
	FOREIGN KEY(`Табельный №`)
		REFERENCES `Работники предприятия`(`Табельный №`)
		ON DELETE RESTRICT ON UPDATE CASCADE
);

INSERT INTO `Договора`
	(`№ договора`, `Название организации`, `Адрес месторосположения`, `Сумма договора`)
	VALUES
	('2018-01', 'ООО "Топаз"', 'г.Котельники, 2-ой проезд, д.23', 200000),
	('2018-05','ООО "Вариант"','г.Держинский, Матросова - 14', 3000000),
	('2019-01','ООО "Вымпел"','г.Москва, Таганская - 23', 5000000);

INSERT INTO `Работники предприятия`
	(`Табельный №`, `ФИО`, `Профессия`)
	VALUES
	(2345, 'Иванов Сергей Степанович', 'Разнорабочий'),
	(2346, 'Краснов Сергей Георгиевич', 'Сантехник'),
	(2347, 'Бендер Остап Ибрагимович', 'Разнорабочий'),
	(2348, 'Абрамов Иван Петрович', 'Электрик');

INSERT INTO `Распределение работников`
	(`№ договора`, `Дата`, `Табельный №`)
	VALUES
	('2018-01', '20.09.2018', 2345),
	('2018-01', '20.09.2018', 2348),
	('2018-01', '21.09.2018', 2345),
	('2018-01', '21.09.2018', 2346),
	('2018-05', '21.09.2018', 2348),
	('2018-05', '20.09.2018', 2346),
	('2018-05', '22.09.2018', 2348);

-- Запроссы были выполнены на 
-- Microsoft SQL Server Management Studio
-- 2 --
IF OBJECT_ID (N'[dbo].[getCountDays]', N'FN') IS NOT NULL  
    DROP FUNCTION [dbo].[getCountDays];  
GO

CREATE FUNCTION [dbo].[getCountDays](@IDw int) RETURNS int
AS

BEGIN
DECLARE @sum int;
SELECT @sum = count([Дата])
FROM [Распределение работников]
WHERE [Табельный №] = @IDw;
IF (@sum IS NULL)   
SET @sum = 0;
RETURN @sum;
END;


DECLARE @sum int = 2345;
SELECT [dbo].[getCountDays](@sum) AS Days;

-- 3 --
CREATE PROCEDURE dbo.setCountDays
AS

BEGIN
UPDATE [Работники предприятия] set	[Количество отработанных дней] = dbo.getCountDays([Табельный №]);
END;

EXECUTE dbo.setCountDays;

-- 4 --
CREATE PROCEDURE [dbo].[setCountDaysCoursor4]
AS

BEGIN 
	DECLARE @IDw INT, @Days INT, @Enter INT;
	DECLARE cur4 CURSOR FOR 
		SELECT [Табельный №], count([Табельный №]) 
		FROM [Распределение работников]
		GROUP BY [Табельный №];

		
	OPEN cur4;
		FETCH NEXT FROM cur4 INTO @IDw, @Days;
		WHILE @@FETCH_STATUS = 0
		BEGIN 
				UPDATE [Работники предприятия] 
				SET [Количество отработанных дней] = @Days
				WHERE [Табельный №] = @IDw;
			FETCH NEXT FROM cur4 INTO @IDw, @Days;
		END;
	CLOSE cur4;
	DEALLOCATE cur4;

END;

-- 5 --

CREATE TRIGGER [deleteDays] 
ON [Распределение работников] 
AFTER DELETE 
AS
UPDATE [Работники предприятия]
SET [Количество отработанных дней] = [Количество отработанных дней] - 1
WHERE [Табельный №] = (SELECT [Табельный №] FROM deleted);


-- 6 -- 

CREATE TRIGGER [insertDays] 
ON [Распределение работников] 
AFTER INSERT 
AS
UPDATE [Работники предприятия]
SET [Количество отработанных дней] = [Количество отработанных дней] + 1
WHERE [Табельный №] = (SELECT [Табельный №] FROM inserted);

-- 7 -- 

CREATE TRIGGER [updateDays] 
ON [Распределение работников] 
AFTER UPDATE 
AS
	BEGIN
	UPDATE [Работники предприятия]
	SET [Количество отработанных дней] = [Количество отработанных дней] - 1
	WHERE [Табельный №] = (SELECT [Табельный №] FROM deleted)
	UPDATE [Работники предприятия]
	SET [Количество отработанных дней] = [Количество отработанных дней] + 1
	WHERE [Табельный №] = (SELECT [Табельный №] FROM inserted)
	END

