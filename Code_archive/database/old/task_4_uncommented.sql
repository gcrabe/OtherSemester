use ScheduleVehicle
select * from Driver
select * from Vehicle
select * from Breaking
select * from Driver
select * from RepairsLog
select* from Route
select* from Stop
select* from Model
select* from Company
select* from Journal_Driver_Vehicle
select * from Journal_Company_Driver
select*from Journal_Vehicle_Route
select * from Journal_Route_Stop
insert into Journal_Route_Stop(IDRoute, IDStop) values (1, 1)
insert Journal_Company_Driver (IDCompany, IDDriver) values (1, 3)


--insert_1
CREATE TRIGGER i1_Driver ON Driver FOR INSERT AS
DECLARE @Name varchar(50)
SELECT @Name=FIO FROM inserted IF @Name='������'
BEGIN 
	PRINT '������'
	ROLLBACK TRANSACTION
END

insert into Driver (IDDriver, FIO, Passport, Experience, DateStart, Salary) values (5, '������', 564, 25, '2015-04-12', 8000)

	insert_2
CREATE TRIGGER i1_Repairs ON RepairsLog FOR INSERT AS
IF EXISTS (SELECT * FROM inserted WHERE DateEnd is NULL)
BEGIN 
	PRINT '������, �� ������ ��������� ���� DateEnd'
	ROLLBACK TRANSACTION
END

insert into RepairsLog(IDRepairs,DateStart, Comment) values (3, '2010-10-10', '������ �����������')

	insert_3
CREATE TRIGGER i_Model ON Model
AFTER INSERT AS
BEGIN
    SET NOCOUNT ON;
	if (select SeatPlace from inserted)<15
	rollback
	print'�� �� ������ ��������� ���������, � ������� ���������� ���� ������ 15'
END

insert into Model (IDModel, ModelOfVehicle, TypeOfVehicle, Firm, SeatPlace, Capacity) values(5, 'Param32', '���������', 'De Lijn', 12, 20)

	delete_1
ALTER TRIGGER d1_Model ON Model
FOR DELETE AS
IF EXISTS (SELECT * FROM delete WHERE Firm = 'Ford')
BEGIN 
	PRINT '������, ���������� ������� ��� ������'
  	ROLLBACK TRANSACTION
END

delete Model where IDModel = 3;

	delete_2
CREATE TRIGGER d_Company ON Company
FOR DELETE AS
IF EXISTS (SELECT * FROM deleted WHERE IDCompany=1)
BEGIN 
	PRINT '������, ������ ������� ��� ��������'
	ROLLBACK TRANSACTION
END

delete Company where IDCompany = 1;

	delete_3
CREATE TRIGGER d_Driver ON Driver
AFTER DELETE AS
BEGIN
	SET NOCOUNT ON;
	if (select Salary from deleted) >= 14000
		print '������ ������� ������ � �����������, ����� ������� ����� 14000'
	rollback
END

delete Driver where Salary >= 14000;

	update_1
CREATE TRIGGER u_Driver ON Driver
FOR UPDATE AS
IF UPDATE (FIO)
	PRINT '�� ���� ��� ��� ������� �����'

UPDATE Driver SET FIO = '�������' where IDDriver = 1;

	update_2
CREATE TRIGGER u_Breaking ON Breaking
FOR UPDATE AS
IF UPDATE (Date) 
BEGIN
    PRINT '������ �������� ���� ������� ���������'
    ROLLBACK TRANSACTION
END

UPDATE Breaking SET Date = '2003-02-14' where IDBreaking = 1;

	update_3
CREATE TRIGGER u1_Driver
   ON Driver
   AFTER update
AS
BEGIN
    SET NOCOUNT ON;
IF (SELECT Salary FROM INSERTED)< 0
PRINT'�������� �� ����� ���� �������������'
ROLLBACK
END
UPDATE Driver SET Salary='-120000' WHERE FIO='�������'

	InsteadOf
create trigger trigger_mrot on Driver
instead of insert
as
begin 
--print '��������� ������ � �����';
declare @S int;
select @S = Salary from inserted;
if (@S < 6140)
begin
print '��������� ������ � �����';
set @S = 6140;
end
declare @IDDriver int; 
select @IDDriver = IDDriver from inserted; 

declare @FIO char(70);
select @FIO = FIO from inserted;

declare @Passport int;
select @Passport = Passport from inserted;

declare @Experience int;
select @Experience = Experience from inserted;
declare @DateStart date;
select @DateStart = DateStart from inserted;

insert into Driver (IDDriver, FIO, Passport, Experience, DateStart, Salary) values (@IDDriver, @FIO, @Passport, @Experience, @DateStart, @S);
end

insert into Driver (IDDriver, FIO, Passport, Experience, DateStart, Salary) values (6, '������', 6563452, 10, '2000-09-19', 5000)


	cascade delete
create trigger cascade_delete_Model on Model
instead of delete 
as
begin
declare @ID int;
select @ID = IDModel from deleted;
delete from Vehicle 
where Model = @ID;
delete from Model
where IDModel = @ID;
end

insert into Model(IDModel, ModelOfVehicle, TypeOfVehicle, Firm, SeatPlace, Capacity) values (666, '�����', '������', '�����', 16, 16)

insert into Vehicle(IDVehicle, RegistrationNumber, YearOfRelease, Model) values (3, 'A21B', '1800-01-15', 666)
insert into Vehicle(IDVehicle, RegistrationNumber, YearOfRelease, Model) values(4, '��', '1600-05-12', 666)
delete from Model 
where IDModel = 666; 


drop trigger cascade_delete_Model