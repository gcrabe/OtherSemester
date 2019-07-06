CREATE PROCEDURE CountEmpDepartment @department AS INT, @count AS int OUTPUT
AS
DECLARE @i as int
DECLARE @n as int
SET @count=0
SELECT @i=MIN(id_stuffDepartment) FROM StuffDepartment
SELECT @n=MAX(id_stuffDepartment) FROM StuffDepartment
WHILE(@i<=@n)
BEGIN
	IF(EXISTS(SELECT id_stuffDepartment FROM StuffDepartment WHERE @i=id_stuffDepartment AND department=@department))
	BEGIN
	SET @count=@count+1
END
SET @i=@i+1
END
GO

CREATE PROCEDURE CountFreeEmpDepartment @department AS INT, @count AS int OUTPUT
AS
DECLARE @i AS int
DECLARE @n AS int
SELECT @i=MIN(id_vacancy) FROM Vacancy
SELECT @n=MAX(id_vacancy) FROM Vacancy
SET @count=0
WHILE(@i<=@n)
BEGIN
	IF(EXISTS(SELECT id_vacancy FROM Vacancy WHERE @i=id_vacancy AND department=@department))
	BEGIN
	SET @count=@count+(SELECT quantity FROM Vacancy WHERE @i=id_vacancy AND department=@department)
	END
SET @i=@i+1
END
GO

CREATE PROCEDURE CanHoliday @employee AS INT, @beg AS date,@end AS date
AS
DECLARE @i AS int
DECLARE @n AS int
SELECT @i=MIN(id_factHoliday) FROM FactHoliday
SELECT @n=MAX(id_factHoliday) FROM FactHoliday
IF(@beg>@end)
BEGIN
	PRINT('Entry is no correct')
END
ELSE
	BEGIN
	WHILE(@i<=@n)
	BEGIN
		IF(EXISTS(SELECT id_factHoliday FROM FactHoliday WHERE @i=id_factHoliday AND (begHoliday<@beg AND @beg<endHoliday)OR(begHoliday<@end AND @end<endHoliday)))
		BEGIN
		PRINT('Period is busy');
		RETURN 0
		END
	SET @i=@i+1
	END
	PRINT('Period is free');
END
GO

CREATE PROCEDURE CountEmpPost @post AS INT, @count AS int OUTPUT
AS
DECLARE @i AS int
DECLARE @n AS int
SELECT @i=MIN(id_stuffDepartment) FROM StuffDepartment
SELECT @n=MAX(id_stuffDepartment) FROM StuffDepartment
SET @count=0
WHILE(@i<=@n)
BEGIN
	IF(EXISTS(SELECT id_stuffDepartment FROM StuffDepartment WHERE @i=id_stuffDepartment AND @post=post))
	BEGIN
	SET @count=@count+1
	END
SET @i=@i+1
END
GO

CREATE PROCEDURE CountFreePost @post AS INT, @count AS int OUTPUT
AS
DECLARE @i AS int
DECLARE @n AS int
SELECT @i=MIN(id_vacancy) FROM Vacancy
SELECT @n=MAX(id_vacancy) FROM Vacancy
SET @count=0
WHILE(@i<=@n)
BEGIN
	IF(EXISTS(SELECT id_vacancy FROM Vacancy WHERE @i=id_vacancy AND @post=post))
	BEGIN
	SET @count=@count+(SELECT quantity FROM Vacancy WHERE @i=id_vacancy AND @post=post)
	END
SET @i=@i+1
END
GO

CREATE PROCEDURE GetSalaryForPeriod @employee AS INT, @beg AS date, @end AS date,@salary AS money OUTPUT
AS
DECLARE @i AS int
DECLARE @n AS int
SELECT @i=MIN(id_salary) FROM Salaries
SELECT @n=MAX(id_salary) FROM Salaries
SET @salary=0
IF(@beg>@end)
BEGIN
	PRINT('Entry is no correct')
END
ELSE
BEGIN
	WHILE(@i<=@n)
	BEGIN
		IF(EXISTS(SELECT id_salary FROM Salaries WHERE @i=id_salary AND @employee=employee AND (DATEPART(YEAR,@beg)<=year AND year<=DATEPART(YEAR,@end) AND (DATEPART(MONTH,@beg)<=month AND month<=DATEPART(MONTH,@end)))))
		BEGIN
		SET @salary=@salary+(SELECT salary FROM Salaries WHERE @i=id_salary AND @employee=employee AND (DATEPART(YEAR,@beg)<=year AND year<=DATEPART(YEAR,@end) AND (DATEPART(MONTH,@beg)<=month AND month<=DATEPART(MONTH,@end))))
		END
	SET @i=@i+1
	END
END
GO