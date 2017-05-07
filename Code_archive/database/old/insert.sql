INSERT INTO Publishing_houses(name, city) VALUES (N'Наука', N'Москва')
INSERT INTO Publishing_houses(name, city) VALUES (N'Лань', N'Санкт-Петербург')
INSERT INTO Publishing_houses(name, city) VALUES (N'Питер', N'Санкт-Петербург')
INSERT INTO Publishing_houses(name, city) VALUES (N'Издательство Саратовского университета', N'Саратов')

INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'Лев', N'Ландау', N'Давидович', '1908-01-22', '1968-04-01')
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'Евгений', N'Лифшиц', N'Михайлович', '1915-02-21', '1985-10-29')
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 
	VALUES(N'Илья', N'Лифшиц', N'Михайлович', '1917-01-13', '1982-10-23')

DELETE FROM Publishing_houses WHERE city = N'Санкт-Петербург'
DELETE FROM Authors WHERE lastName = N'Лифшиц'

DELETE FROM ActionList
DELETE FROM Readership
DELETE FROM ExemplarList
DELETE FROM Book_Edition
DELETE FROM Book_General
DELETE FROM Authors
DELETE FROM Publishing_houses
