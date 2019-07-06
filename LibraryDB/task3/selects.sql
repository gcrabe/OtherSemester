USE Library
GO

SELECT id_book_general, id_author FROM Book_general bg, Authors a WHERE bg.date_delivery < {d'1950-12-31'}
SELECT a.first_name, b.first_name FROM Authors a, Authors b WHERE a.first_name = b.first_name
SELECT first_name, title FROM Authors CROSS JOIN Book_general
SELECT first_name, title FROM Authors as a INNER JOIN Book_general as bg ON bg.date_delivery < {d'1950-12-31'}
SELECT * FROM Authors as a LEFT OUTER JOIN Book_general as bg ON bg.date_delivery < {d'1950-12-31'}
SELECT * FROM Authors as a RIGHT OUTER JOIN Book_general as bg ON bg.date_delivery < {d'1950-12-31'}

SELECT first_name, last_name FROM Authors WHERE EXISTS(SELECT first_name FROM Authors WHERE first_name != 'Александр')
SELECT id_book_general FROM Book_general WHERE date_delivery BETWEEN {d'1950-01-01'} AND {d'1975-01-01'}
SELECT title FROM Book_general WHERE title IN (N'Замок', N'Золотая тетрадь')
SELECT id_book_general FROM Book_general WHERE id_book_general < SOME (SELECT id_book_general FROM Book_general)
SELECT id_book_general FROM Book_general WHERE date_delivery = ANY (SELECT date_delivery FROM Book_general)
SELECT title FROM Book_general WHERE date_delivery > ALL (SELECT date_delivery from Book_general WHERE title = N'Процесс')
SELECT first_name, last_name FROM Authors WHERE Authors.date_birth LIKE ('%')

SELECT first_name, last_name =
	CASE
		WHEN id_author > 5 THEN '1'
		WHEN id_author < 5 THEN '2'
		WHEN id_author = 5 THEN '3'
	END
from Authors

SELECT date_birth, date_death FROM Authors WHERE CAST(date_birth as date) LIKE ('%')
SELECT date_birth, date_death FROM Authors WHERE CONVERT(date, date_birth) LIKE ('%')
SELECT date_death FROM Authors WHERE date_death IS NOT NULL
SELECT first_name, last_name, NULLIF(first_name, last_name) as 'NULL IF EQ' FROM Authors WHERE id_author < 10

SELECT REPLACE(Authors.first_name, N'Иван', N'123') FROM Authors
SELECT SUBSTRING(Authors.first_name, 1, 1) FROM Authors
SELECT LOWER(first_name), UPPER(last_name) FROM Authors
SELECT STUFF(first_name, 1, 1, N'*') FROM Authors

SELECT DATEPART(year, GETDATE()), DATEPART(month, GETDATE()), DATEPART(day, GETDATE())
SELECT DATEADD(year, 1, GETDATE())
SELECT DATEDIFF(YEAR, date_delivery, GETDATE()) FROM Book_general
SELECT GETDATE()

SELECT SUM(id_author) FROM Authors GROUP BY SUBSTRING(first_name, 1, 1) HAVING SUM(id_author) > 5