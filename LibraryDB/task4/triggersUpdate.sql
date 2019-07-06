-- update 1

create trigger UpdateTrigger1 on Actions for update
as
	declare @id_book_exemplar integer
	set @id_book_exemplar = (select id_book_exemplar from inserted)

	declare @id_book_edition integer
	set @id_book_edition = (select id_book_edition from Book_exemplars where id_book_exemplar = @id_book_exemplar)

	update Book_exemplars set is_free = 1 where id_book_exemplar = @id_book_exemplar
	update Book_editions set count_available = count_available + 1 where id_book_edition = @id_book_edition

-- update 2

create trigger UpdateTrigger2 on Actions for update
as
	declare @date_borrowing date
	set @date_borrowing = (select date_borrowing from deleted)
	
	declare @date_required date
	set @date_required = (select date_required from deleted)

	declare @date_actual date
	set @date_actual = (select date_actual from inserted)

	declare @fine integer

	if (@date_actual not between @date_borrowing and @date_required)
	begin
		print 'Missed deadline!'
	end;

-- update 3

create trigger UpdateTrigger3 on Users instead of update
as
	if @@ROWCOUNT = 1 and not exists(
		select * from Departments where id_department = (
			select id_department from inserted
		)
	)
	begin
		print 'incorrect department'
		rollback transaction
	end;