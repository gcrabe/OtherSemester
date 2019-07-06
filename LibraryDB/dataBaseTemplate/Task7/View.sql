SET NUMERIC_ROUNDABORT OFF
SET ANSI_PADDING, ANSI_WARNINGS, CONCAT_NULL_YIELDS_NULL,
ARITHABORT, QUOTED_IDENTIFIER, ANSI_NULLS ON;
GO
CREATE VIEW dbo.Emp
WITH SCHEMABINDING
AS
SELECT dbo.Employees.firstName,dbo.Employees.lastName,dbo.Employees.patronymic,dbo.Employees.yearBirth,dbo.Employees.numberPassport,dbo.Employees.SNILS,dbo.Employees.INN,dbo.Employees.education,dbo.Employees.experience
FROM dbo.Employees
WHERE (dbo.Employees.experience >= 2)
WITH CHECK OPTION 
