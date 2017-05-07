INSERT INTO Publishing_houses(name, city) VALUES ("Наука", "Москва")
INSERT INTO Publishing_houses(name, city) VALUES ("Лань", "Санкт-Петербург")
INSERT INTO Publishing_houses(name, city) VALUES ("Питер", "Санкт-Петербург")
INSERT INTO Publishing_houses(name, city) VALUES ("Издательство Саратовского университета", "Саратов")

INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("Ландау", "Лев", "Давидович", "1908-01-22", "1968-04-01")
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("Лифшиц", "Евгений", "Михайлович", "1915-02-21", "1985-10-29")
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("Лифшиц" , "Илья", "Михайлович", "1917-01-13", "1982-10-23")

DELETE FROM Publishing_houses WHERE city = "Санкт-Петербург"
DELETE FROM Authors WHERE lastName = "Лифшиц"

DELETE FROM Readership
DELETE FROM ActionList
DELETE FROM ExemplarList
DELETE FROM Book_Edition
DELETE FROM Book_General
DELETE FROM Authors
DELETE FROM Publishing_houses
                                                     
