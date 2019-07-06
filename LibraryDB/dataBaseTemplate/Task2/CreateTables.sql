CREATE TABLE [Employees] (
	id_employee integer NOT NULL IDENTITY(1,1) PRIMARY KEY,
	firstName varchar(255) NOT NULL,
	yearBirth date NOT NULL,
	numberPassport integer NOT NULL,
	SNILS integer NOT NULL,
	INN integer NOT NULL,
	yearBeg date NOT NULL,
	yearEnd date NOT NULL,
	education varchar(255) NOT NULL,
	lastName varchar(255) NOT NULL,
	patronymic varchar(255) NOT NULL,
	experience integer NOT NULL,
)

CREATE TABLE [Departments] (
	id_department integer IDENTITY(1,1) PRIMARY KEY,
	name varchar(255) NOT NULL,
	description varchar(255),
	director integer FOREIGN KEY REFERENCES Employees(id_employee),
)

CREATE TABLE [Posts] (
	id_post integer IDENTITY(1,1) PRIMARY KEY,
	name varchar(255) NOT NULL,
	description varchar(255) NOT NULL,
	salary money NOT NULL,
)
CREATE TABLE [FreePosts] (
	id_fposts integer IDENTITY(1,1) PRIMARY KEY,
	post integer NOT NULL FOREIGN KEY REFERENCES Posts(id_post),
	department integer NOT NULL FOREIGN KEY REFERENCES Departments(id_department),
	quantity integer DEFAULT 0
)

CREATE TABLE [StuffDepartment] (
	id_stuffDepartment integer IDENTITY(1,1) PRIMARY KEY,
	department integer NOT NULL FOREIGN KEY REFERENCES Departments(id_department),
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	post integer NOT NULL FOREIGN KEY REFERENCES Posts(id_post),
	bonusPay money NOT NULL,
	begWork date NOT NULL,
	endWork date NOT NULL
)

CREATE TABLE [Holiday] (
	id_holiday integer IDENTITY(1,1) PRIMARY KEY,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	standartDay integer NOT NULL,
	remainDay integer NOT NULL
)

CREATE TABLE [PlanHoliday] (
	id_planholiday integer IDENTITY(1,1) PRIMARY KEY,
	begHoliday date NOT NULL,
	endHoliday date NOT NULL,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee)
)

CREATE TABLE [CovetiveEmployees] (
	id_covetive integer IDENTITY(1,1) PRIMARY KEY,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	desirePost integer NOT NULL FOREIGN KEY REFERENCES Posts(id_post)
)

CREATE TABLE [Salaries] (
	id_salaries integer IDENTITY(1,1) PRIMARY KEY,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	month integer NOT NULL,
	salary money NOT NULL,
	year integer NOT NULL,
	status bit default 0,
	post integer NOT NULL FOREIGN KEY REFERENCES Posts(id_post)
)

CREATE TABLE [Address] (
	id_address integer IDENTITY(1,1) PRIMARY KEY,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	street integer NOT NULL,
	numFlat integer NOT NULL,
	numPorch integer NOT NULL,
	separateHome bit NOT NULL,
	city varchar(255) NOT NULL
)

CREATE TABLE [FactHoliday] (
	id_factHoliday integer IDENTITY(1,1) PRIMARY KEY,
	begHoliday date NOT NULL,
	endHoliday date NOT NULL,
	employee integer NOT NULL FOREIGN KEY REFERENCES Employees(id_employee),
	year integer NOT NULL
)
