INSERT INTO Publishing_houses(name, city) VALUES (N'�����', N'������')
INSERT INTO Publishing_houses(name, city) VALUES (N'����', N'�����-���������')
INSERT INTO Publishing_houses(name, city) VALUES (N'�����', N'�����-���������')
INSERT INTO Publishing_houses(name, city) VALUES (N'������������ ������������ ������������', N'�������')

INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'���', N'������', N'���������', '1908-01-22', '1968-04-01')
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'�������', N'������', N'����������', '1915-02-21', '1985-10-29')
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'����', N'������', N'����������', '1917-01-13', '1982-10-23')

DELETE FROM Publishing_houses WHERE city = N'�����-���������'
DELETE FROM Authors WHERE lastName = N'������'

DELETE FROM ActionList
DELETE FROM Readership
DELETE FROM ExemplarList
DELETE FROM Book_Edition
DELETE FROM Book_General
DELETE FROM Authors
DELETE FROM Publishing_houses
