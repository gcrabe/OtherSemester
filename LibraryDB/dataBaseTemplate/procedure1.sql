CREATE PROCEDURE Count_client AS
SELECT COUNT(id_client) FROM Clients
GO
exec Count_client

