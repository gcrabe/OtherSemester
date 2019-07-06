GO
CREATE PROCEDURE Trainer_Search  @F AS nvarchar(255), @L AS nvarchar(255) output
AS
SELECT id_trainer
FROM Trainers
WHERE first_name = @F and last_name = @L
GO

EXEC Trainer_Search N'Иван', N'Церулик';
GO