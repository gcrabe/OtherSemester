CREATE PROCEDURE Cash_payment1 @q As nvarchar(255)
AS
SELECT (id_payment_way) FROM Payment_ways  WHERE name!=@q
GO

exec Cash_payment1 N'Дебетовая карта'