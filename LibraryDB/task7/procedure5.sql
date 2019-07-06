Use Library
go

create procedure UsersCursor @cursor cursor varying output
as
	set nocount on
	set @cursor = cursor

	forward_only static for

	select id_user, id_department from Users
	open @cursor
go

declare @current_cursor cursor
exec UsersCursor @cursor = @current_cursor OUTPUT;

while  (@@FETCH_STATUS = 0)
begin
     fetch next from @current_cursor
end

close @current_cursor

deallocate @current_cursor
go
