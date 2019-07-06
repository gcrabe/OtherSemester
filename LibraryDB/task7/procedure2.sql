create procedure GetFree
	@input_book_title as nvarchar(255)
as
	select * from Book_exemplars where is_free = 1 and id_book_edition = (
		select id_book_edition from Book_editions where id_book_general = (
			select id_book_general from Book_general where title = @input_book_title
		)
	)

exec GetFree N'Title'
