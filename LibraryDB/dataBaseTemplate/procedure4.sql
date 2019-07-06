GO
CREATE PROCEDURE Workouts_current_time @tb AS time, @te AS time 
AS
SELECT id_workout From Workouts WHERE time_begin = @tb AND time_end = @te
GO

exec Workouts_current_time '13:00:00', '14:00:00'