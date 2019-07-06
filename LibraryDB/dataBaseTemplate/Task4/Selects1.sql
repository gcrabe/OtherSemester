SELECT firstName, lastName FROM Employees CROSS JOIN Departments;
SELECT firstName, lastName FROM Employees as e JOIN Departments as d ON e.id_employee=d.id_department;
SELECT name,salary FROM Posts WHERE salary BETWEEN 10000 and 20000;
SELECT SUBSTRING(firstName,1,2), SUBSTRING(patronymic,1,2), lastName FROM Employees;
SELECT firstName, lastName FROM Employees WHERE DATEPART(month,yearBeg)=8;
SELECT Sum(INN) FROM Employees GROUP BY SUBSTRING(firstName,1,3) HAVING Sum(INN)>14;
SELECT (SELECT name FROM Posts WHERE employee=Salaries.employee) FROM Salaries WHERE salary>10000;
(SELECT firstName FROM Employees) UNION (SELECT salary FROM Salaries);

--Point 1
--SELECT firstName,name FROM Employees e,Departments d WHERE e.id_employee=d.director;
--SELECT a.firstName, b.firstName FROM Employees a,Employees b WHERE a.id_employee=b.id_employee;
--SELECT firstName, lastName FROM Employees as e INNER JOIN Departments as d ON e.id_employee=d.id_department;
--SELECT firstName, lastName FROM Employees as e LEFT OUTER JOIN Departments as d on e.id_employee>3;
--SELECT firstName, lastName FROM Employees as e RIGHT OUTER JOIN Departments as d ON e.id_employee>3;
----Point 2
--SELECT name, director FROM Departments WHERE EXISTS (SELECT NULL);
--SELECT firstName, lastName FROM Employees WHERE Employees.id_employee IN (SELECT Departments.id_department FROM Departments WHERE Departments.id_department=2);
--SELECT firstName, lastName FROM Employees WHERE Employees.id_employee BETWEEN 3 and 5;
--SELECT firstName, lastName FROM Employees WHERE Employees.id_employee <> ANY(SELECT director FROM Departments);
--SELECT firstName, lastName FROM Employees WHERE Employees.firstName LIKE ('Èìÿ[1,2]');
----Point 3
--SELECT firstName=CASE firstName WHEN 'Èìÿ1' THEN '1' WHEN 'Èìÿ2' THEN '2' WHEN 'Èìÿ3' THEN '3' WHEN 'Èìÿ4' THEN '4' WHEN 'Èìÿ5' THEN '5' END,lastName FROM Employees;
----Point 4
--SELECT CAST(firstName as varchar(3)), CAST(lastName as varchar(1)) FROM Employees;
--SELECT CONVERT(datetime,(SELECT SNILS FROM Employees WHERE Employees.id_employee=1));
--SELECT firstName,lastName FROM Employees WHERE Employees.yearEnd IS NULL;
--SELECT firstName, COALESCE(firstName,lastName) FROM Employees;
----Point 5
--SELECT SUBSTRING(firstName,4,5) FROM Employees;
--SELECT UPPER(firstName),UPPER(LOWER(lastName)) FROM Employees;
----Point 6
--SELECT GetDate();
--SELECT DATEPART(month,yearBeg)FROM Employees;
--SELECT DATEADD(year,56,yearBeg) FROM Employees;
----Point 7
--SELECT Sum(INN) FROM Employees GROUP BY SUBSTRING(firstName,1,3) HAVING Sum(INN)>14;