INSERT INTO Departments(name,description)
VALUES ('Отдел1', 'Описание1');
INSERT INTO Departments(name,description)
VALUES ('Отдел2', 'Описание2');
INSERT INTO Departments(name,description)
VALUES ('Отдел3', 'Описание3');
INSERT INTO Departments(name,description)
VALUES ('Отдел4', 'Описание4');
INSERT INTO Departments(name,description)
VALUES ('Отдел5', 'Описание5');
INSERT INTO Posts(name,description,salary)
VALUES ('Пост1', 'Описание1', '1000');
INSERT INTO Posts(name,description,salary)
VALUES ('Пост2', 'Описание2', '2000');
INSERT INTO Posts(name,description,salary)
VALUES ('Пост3', 'Описание3', '3000');
INSERT INTO Posts(name,description,salary)
VALUES ('Пост4', 'Описание4', '4000');
INSERT INTO Posts(name,description,salary)
VALUES ('Пост5', 'Описание5', '5000');

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