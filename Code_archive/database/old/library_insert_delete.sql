INSERT INTO Publishing_houses(name, city) VALUES ("�����", "������")
INSERT INTO Publishing_houses(name, city) VALUES ("����", "�����-���������")
INSERT INTO Publishing_houses(name, city) VALUES ("�����", "�����-���������")
INSERT INTO Publishing_houses(name, city) VALUES ("������������ ������������ ������������", "�������")

INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("������", "���", "���������", "1908-01-22", "1968-04-01")
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("������", "�������", "����������", "1915-02-21", "1985-10-29")
INSERT INTO Authors(firstName, lastName, patronymicName, birthDate, deathDate) 	VALUES("������" , "����", "����������", "1917-01-13", "1982-10-23")

DELETE FROM Publishing_houses WHERE city = "�����-���������"
DELETE FROM Authors WHERE lastName = "������"

DELETE FROM Readership
DELETE FROM ActionList
DELETE FROM ExemplarList
DELETE FROM Book_Edition
DELETE FROM Book_General
DELETE FROM Authors
DELETE FROM Publishing_houses
                                                     
