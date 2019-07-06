create procedure CountUsersFromDepartment
	@input_id_department as int
as
	declare @i as int
	declare @n as int

	declare @count as int
	set @count = 0

	select @i = min(id_user) from Users
	select @n = max(id_user) from Users

	while (@i <= @n)
	begin
		if (exists(select id_user from Users where @i = id_user and id_department = @input_id_department))
		begin
			set @count = @count + 1
		end

		set @i = @i + 1
	end

    print @count
go


use Library
go

Exec CountUsersFromDepartment 1