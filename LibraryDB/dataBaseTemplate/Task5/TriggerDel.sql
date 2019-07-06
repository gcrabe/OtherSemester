CREATE TRIGGER DelPost
ON Posts
INSTEAD OF DELETE
AS 
BEGIN
DECLARE @id int
SET @id=(SELECT id_post FROM deleted)
DELETE FROM Posts WHERE Posts.id_post=@id;
DELETE FROM Vacancy WHERE Vacancy.id_vacancy=@id;
DELETE FROM StuffDepartment WHERE StuffDepartment.post=@id;
DELETE FROM PretendingEmployees WHERE PretendingEmployees.desirePost=@id;
DELETE FROM Salaries WHERE Salaries.post=@id;
DELETE FROM Salaries WHERE Salaries.post=@id;
END;
GO
CREATE TRIGGER DelEmployee
ON Employees
INSTEAD OF DELETE
AS 
BEGIN
DECLARE @id int
SELECT @id=(SELECT id_employee FROM deleted)
DELETE FROM Employees WHERE Employees.id_employee=@id;
DELETE FROM Departments WHERE Departments.director=@id;
DELETE FROM StuffDepartment WHERE StuffDepartment.employee=@id;
DELETE FROM Holiday WHERE Holiday.employee=@id;
DELETE FROM PlanHoliday WHERE PlanHoliday.employee=@id;
DELETE FROM PretendingEmployees WHERE PretendingEmployees.employee=@id;
DELETE FROM Salaries WHERE Salaries.employee=@id;
DELETE FROM Address WHERE Address.employee=@id;
DELETE FROM FactHoliday WHERE FactHoliday.employee=@id;
END;
GO
CREATE TRIGGER DelDepatment
ON Departments
INSTEAD OF DELETE
AS 
BEGIN
DECLARE @id int
SELECT @id=(SELECT id_department FROM deleted)
DELETE FROM Departments WHERE Departments.id_department=@id;
DELETE FROM Vacancy WHERE Vacancy.id_vacancy=@id;
DELETE FROM StuffDepartment WHERE StuffDepartment.department=@id;
END;
GO
CREATE TRIGGER DelStuffDepartment
ON StuffDepartment
INSTEAD OF DELETE
AS
BEGIN
DECLARE @id int
SELECT @id=(SELECT id_stuffDepartment FROM deleted)
DELETE FROM StuffDepartment WHERE StuffDepartment.id_stuffDepartment=@id;
UPDATE Employees SET Employees.yearEnd=GETDATE();
END;