INSERT INTO Departments(name,description)
VALUES ('�����1', '��������1');
INSERT INTO Departments(name,description)
VALUES ('�����2', '��������2');
INSERT INTO Departments(name,description)
VALUES ('�����3', '��������3');
INSERT INTO Departments(name,description)
VALUES ('�����4', '��������4');
INSERT INTO Departments(name,description)
VALUES ('�����5', '��������5');
INSERT INTO Posts(name,description,salary)
VALUES ('����1', '��������1', '1000');
INSERT INTO Posts(name,description,salary)
VALUES ('����2', '��������2', '2000');
INSERT INTO Posts(name,description,salary)
VALUES ('����3', '��������3', '3000');
INSERT INTO Posts(name,description,salary)
VALUES ('����4', '��������4', '4000');
INSERT INTO Posts(name,description,salary)
VALUES ('����5', '��������5', '5000');

DELETE FROM Posts 
WHERE id_posts=1;
DELETE FROM Posts 
WHERE id_posts=2;
DELETE FROM Posts 
WHERE id_posts=3;

DELETE FROM FactHoliday
DELETE FROM Address
DELETE FROM Salaries
DELETE FROM CovetiveEmployees
DELETE FROM PlanHoliday
DELETE FROM Holiday
DELETE FROM StuffDepartment
DELETE FROM FreePosts
DELETE FROM Posts
DELETE FROM Departments
DELETE FROM Employees