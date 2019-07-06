CREATE TRIGGER UpdPosts
ON Posts FOR UPDATE
AS
IF (UPDATE(salary) AND @@ROWCOUNT=1) 
BEGIN
	UPDATE Salaries SET salary = -(SELECT salary FROM deleted) + (SELECT bonusPay FROM StuffDepartment WHERE post = (
		SELECT id_post FROM inserted) ) + (SELECT salary FROM inserted)
	WHERE post = (SELECT post FROM inserted)
END;
GO

CREATE TRIGGER UpdStuffDepartment
ON StuffDepartment FOR UPDATE
AS
IF(UPDATE(bonusPay) AND @@ROWCOUNT=1)
BEGIN
	UPDATE Salaries SET salary = -(SELECT bonusPay FROM deleted) + (SELECT salary FROM Posts WHERE id_post = (
		SELECT post FROM inserted) ) + (SELECT bonusPay FROM inserted)
	WHERE employee = (SELECT employee FROM inserted)
END;
GO

CREATE TRIGGER UpdSalaries
ON Salaries INSTEAD OF UPDATE
AS
IF(UPDATE(status) AND @@ROWCOUNT=1)
BEGIN
	IF((SELECT status FROM deleted)=1)
	BEGIN
		PRINT 'Value of status is set'
	END;
END;
GO