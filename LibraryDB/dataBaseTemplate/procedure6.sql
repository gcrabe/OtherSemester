CREATE PROCEDURE Payment_proc @i int
AS
IF (SELECT money_sum FROM Payment_ways) > @i
RETURN 1
ELSE
RETURN 0

EXEC Payment_proc 700;
GO