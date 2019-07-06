-- delete 1
use Library
go

create trigger DeleteTrigger1 on Book_Editions instead of delete
as
	declare @id_book_edition integer
	set @id_book_edition = (select id_book_edition from deleted);

	declare @id_book_exemplar integer
	set @id_book_exemplar = (select id_book_exemplar from Book_exemplars where id_book_edition = @id_book_edition);

	delete from Actions where id_book_exemplar = @id_book_exemplar
	delete from Book_exemplars where id_book_edition = @id_book_edition
	delete from Book_editions where id_book_edition = @id_book_edition

--delete 2

use Library
go

create trigger DeleteTrigger2 on Book_general instead of delete
as
	declare @id_book_general integer
	set @id_book_general = (select id_book_general from deleted)

	declare @id_book_edition integer
	set @id_book_edition = (select id_book_edition from Book_editions where id_book_general = @id_book_general);

	declare @id_book_exemplar integer
	set @id_book_exemplar = (select id_book_exemplar from Book_exemplars where id_book_edition = @id_book_edition);

	delete from Actions where id_book_exemplar = @id_book_exemplar
	delete from Book_exemplars where id_book_edition = @id_book_edition
	delete from Book_editions where id_book_edition = @id_book_edition
	delete from Book_general where id_book_general = @id_book_general

-- delete 3
use Library
go

create trigger DeleteTrigger3 on Users instead of delete
as
	declare @id_user integer
	set @id_user = (select id_user from deleted)

	declare @date_actual date
	set @date_actual = (select date_actual from Actions where id_user = @id_user)

	if (@date_actual = null)
	begin
		print 'user has not free profile list'
	end