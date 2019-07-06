CREATE VIEW dbo.DynamicUsersView
AS
SELECT dbo.Users.priority, dbo.Users.login, dbo.Users.password, dbo.Users.first_name, dbo.Users.mid_name, dbo.Users.last_name, dbo.Users.document_number, dbo.Users.date_birth,
	dbo.Users.id_department, dbo.Users.job_title, dbo.Users.date_registration
FROM dbo.Users
WHERE (dbo.Users.priority = N'user')
WITH CHECK OPTION 


use Library
go

insert into DynamicUsersView(priority, login, password, first_name, mid_name, last_name, document_number, date_birth,
	id_department, job_title, date_registration)
values (N'worker', N'login0', N'password0', N'first0', N'mid0', N'last0', 12345, '1995-5-5', 1, N'title0', '2015-5-5')