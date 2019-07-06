CREATE NONCLUSTERED INDEX One
ON Employees (firstName, lastName)
GO
CREATE UNIQUE NONCLUSTERED INDEX Two
ON Employees (numberPassport)
GO
CREATE UNIQUE NONCLUSTERED INDEX Three
ON Employees (SNILS, INN)
GO
CREATE NONCLUSTERED INDEX Four
ON Departments (name,director)
GO
CREATE NONCLUSTERED INDEX Five
ON Vacancy (post, department)
GO
CREATE NONCLUSTERED INDEX Six
ON Salaries (salary)
INCLUDE(month,year,status,post)
GO
CREATE NONCLUSTERED INDEX Seven
ON Posts (salary)
INCLUDE (name)
Go
CREATE NONCLUSTERED INDEX Eight
ON Employees (firstName, lastName, patronymic)
GO
CREATE CLUSTERED INDEX Nine
ON Address (id_address)