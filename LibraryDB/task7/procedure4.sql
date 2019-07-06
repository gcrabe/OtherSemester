create procedure CorrectUser
	@input_id_user as int
as
	if exists(select id_action from Actions where id_user = @input_id_user and date_actual = null)
	begin
		print 1
	end
	else begin
		print 0
  	end