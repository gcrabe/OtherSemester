CREATE VIEW dbo.UsersView WITH ENCRYPTION
AS
SELECT dbo.Users.id_user, dbo.Users.first_name, dbo.Users.mid_name, dbo.Users.last_name, dbo.Users.date_registration, dbo.Departments.name
FROM dbo.Users INNER JOIN
	 dbo.Departments ON dbo.Users.id_department = dbo.Departments.id_department
WHERE (dbo.Users.priority = N'user')



use Library
go
select * from UsersView
