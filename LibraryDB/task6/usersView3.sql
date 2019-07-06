SET NUMERIC_ROUNDABORT OFF
SET ANSI_PADDING, ANSI_WARNINGS, CONCAT_NULL_YIELDS_NULL, ARITHABORT, QUOTED_IDENTIFIER, ANSI_NULLS ON;
GO

CREATE VIEW dbo.IndexedUsersView
WITH SCHEMABINDING
AS
SELECT dbo.Users.priority, dbo.Users.login, dbo.Users.password, dbo.Users.first_name, dbo.Users.mid_name, dbo.Users.last_name, dbo.Users.document_number, dbo.Users.date_birth,
	dbo.Users.id_department, dbo.Users.job_title, dbo.Users.date_registration
FROM dbo.Users
WHERE (dbo.Users.priority = N'user')
WITH CHECK OPTION 
GO

CREATE UNIQUE CLUSTERED INDEX ViewIndex
ON IndexedUsersView(document_number)
GO

