create procedure GetNews
as
	select title, date_delivery from Book_general where date_delivery > getdate() - 30

exec GetNews