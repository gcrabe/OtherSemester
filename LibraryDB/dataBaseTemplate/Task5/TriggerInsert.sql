CREATE TRIGGER InsertStuffDepartment
ON StuffDepartment FOR INSERT
AS
IF(@@ROWCOUNT=1 AND EXISTS(SELECT * FROM Vacancy WHERE department=(SELECT department FROM inserted) AND post=(SELECT post FROM inserted)))
BEGIN
DELETE FROM Vacancy WHERE department=(SELECT department FROM inserted) AND post=(SELECT post FROM inserted)
END;
IF(@@ROWCOUNT=1 AND EXISTS(SELECT * FROM PretendingEmployees WHERE employee=(SELECT employee FROM inserted) AND desirePost=(SELECT post FROM inserted)))
BEGIN
DELETE FROM PretendingEmployees WHERE employee=(SELECT employee FROM inserted) AND desirePost=(SELECT post FROM inserted)
END;
UPDATE Employees SET yearBeg=GETDATE() WHERE id_employee=(SELECT employee FROM inserted)
GO

CREATE TRIGGER InsertPlanHoliday
ON PlanHoliday INSTEAD OF INSERT
AS
DECLARE @beg DATE;
DECLARE @end DATE;
DECLARE @id_employee int;
SET @beg=(SELECT begHoliday FROM inserted);
SET @end=(SELECT endHoliday FROM inserted);
SET @id_employee=(SELECT employee FROM inserted);
IF(@beg>@end)
BEGIN
PRINT 'No correct enter data'
END;
ELSE
BEGIN
IF(EXISTS(SELECT * FROM PlanHoliday WHERE (begHoliday<@beg AND @beg<endHoliday)OR(begHoliday<@end AND @end<endHoliday)))
BEGIN
PRINT 'Exists cross period'
END;
ELSE
BEGIN
IF((SELECT remainday FROM Holiday WHERE employee=@id_employee)<DATEDIFF(day,@beg,@end))
BEGIN
PRINT 'Period is bigger then remain days'
END;
END;
END;
GO

CREATE TRIGGER InsertFactHoliday
ON FactHoliday INSTEAD OF INSERT
AS
DECLARE @beg DATE;
DECLARE @end DATE;
DECLARE @id_employee int;
SET @beg=(SELECT begHoliday FROM inserted);
SET @end=(SELECT endHoliday FROM inserted);
SET @id_employee=(SELECT employee FROM inserted);
IF(@beg>@end)
BEGIN
PRINT 'No correct enter data'
END;
ELSE
BEGIN
IF(EXISTS(SELECT * FROM FactHoliday WHERE (begHoliday<@beg AND @beg<endHoliday)OR(begHoliday<@end AND @end<endHoliday)))
BEGIN
PRINT 'Exists cross period'
END;
ELSE
BEGIN
IF((SELECT remainday FROM Holiday WHERE employee=@id_employee)<DATEDIFF(day,@beg,@end))
BEGIN
PRINT 'Period is bigger then remain days'
END;
END;
END;
GO
