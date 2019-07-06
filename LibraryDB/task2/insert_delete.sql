USE Library
GO

INSERT INTO Cities(name) VALUES(N'Москва')
INSERT INTO Cities(name) VALUES(N'Санкт-Петербург')
INSERT INTO Cities(name) VALUES(N'Саратов')
INSERT INTO Cities(name) VALUES(N'Челябинск')

INSERT INTO Publishing_houses(name, id_city) VALUES(N'Современник', 1)
INSERT INTO Publishing_houses(name, id_city) VALUES(N'Наука', 1)
INSERT INTO Publishing_houses(name, id_city) VALUES(N'Лань', 2)
INSERT INTO Publishing_houses(name, id_city) VALUES(N'Издательство Саратовского Университета', 3)
INSERT INTO Publishing_houses(name, id_city) VALUES(N'Южно-Уральское книжное издательство', 4)

INSERT INTO Authors(first_name, mid_name, last_name, date_birth, date_death) 
	VALUES(N'Лев', N'Давидович', N'Ландау', '1908-01-22', '1968-04-01')
INSERT INTO Authors(first_name, mid_name, last_name, date_birth, date_death) 
	VALUES(N'Евгений', N'Михайлович', N'Лифшиц', '1915-02-21', '1985-10-29')
INSERT INTO Authors(first_name, mid_name, last_name, date_birth, date_death)
	VALUES(N'Илья', N'Михайлович', N'Лифшиц', '1917-01-13', '1982-10-23')

DELETE FROM Publishing_houses WHERE city = N'Санкт-Петербург'
DELETE FROM Authors WHERE last_name = N'Лифшиц'

DELETE FROM Book_editions_Translators
DELETE FROM Translators
DELETE FROM Actions
DELETE FROM Users
DELETE FROM Departments
DELETE FROM Book_exemplars
DELETE FROM Book_editions
DELETE FROM Publishing_houses
DELETE FROM Cities
DELETE FROM Book_general_Genres
DELETE FROM Genres
DELETE FROM Book_general_Authors
DELETE FROM Authors
DELETE FROM Book_general

USE Library
GO
DBCC CHECKIDENT('Translators', reseed, 0)
DBCC CHECKIDENT('Actions', reseed, 0)
DBCC CHECKIDENT('Users', reseed, 0)
DBCC CHECKIDENT('Departments', reseed, 0)
DBCC CHECKIDENT('Book_exemplars', reseed, 0)
DBCC CHECKIDENT('Book_editions', reseed, 0)
DBCC CHECKIDENT('Publishing_houses', reseed, 0)
DBCC CHECKIDENT('Cities', reseed, 0)
DBCC CHECKIDENT('Genres', reseed, 0)
DBCC CHECKIDENT('Authors', reseed, 0)
DBCC CHECKIDENT('Book_general', reseed, 0)
GO
