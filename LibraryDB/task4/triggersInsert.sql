-- insert 1
use Library
go

create trigger InsertTrigger1 on authors for insert
as
	declare @mid_name nvarchar(255)
	declare @last_name nvarchar(255)
	declare @date_death date
	
	set @mid_name = (select mid_name from inserted)
	set @last_name = (select last_name from inserted)
	set @date_death = (select date_death from inserted)

if @mid_name = ''
begin
	update Authors set mid_name = null where id_author = (select id_author from inserted)
end;
if @last_name = ''
begin
	update Authors set last_name = null where id_author = (select id_author from inserted)
end;
if @date_death = ''
begin
	update Authors set date_death = null where id_author = (select id_author from inserted)
end;

insert into Authors(first_name, mid_name, last_name, date_birth, date_death)
	values(N'first1', N'', N'', '1900-5-5', '')

-- insert 2
use Library
go

create trigger InsertTrigger2 on users instead of insert
as
if @@rowcount = 1 and not exists(
	select * from departments where id_department = (
		select id_department from inserted)
	)
begin
	print 'incorrect department'
	rollback transaction
end;

insert into Users(priority, login, password, first_name, mid_name, last_name, document_number, date_birth, id_department, job_title, date_registration) 
	values(N'user', N'login1', N'password1', N'first1', N'mid1', N'last1', 6315, '1995-4-15', 2000, N'title', '2013-9-1')

-- insert 3
use Library
go

create trigger InsertTrigger3 on Actions for insert
as
	declare @id_book_exemplar integer
	set @id_book_exemplar = (select id_book_exemplar from inserted)

	declare @id_book_edition integer
	set @id_book_edition = (select id_book_edition from Book_exemplars where id_book_exemplar = @id_book_exemplar)

	update Book_exemplars set is_free = 0 where id_book_exemplar = @id_book_exemplar
	update Book_editions set count_available = count_available - 1 where id_book_edition = @id_book_edition
