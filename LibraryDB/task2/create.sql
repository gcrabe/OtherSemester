USE Library
GO

CREATE TABLE [Cities] (
	id_city integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	name nvarchar(255) NOT NULL
)
GO

CREATE TABLE [Publishing_houses] (
	id_publishing_house integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	name nvarchar(255) NOT NULL UNIQUE,
	id_city integer NOT NULL FOREIGN KEY REFERENCES Cities(id_city)
)
GO

CREATE TABLE [Departments] (
	id_department integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	name nvarchar(255) NOT NULL
)
GO

CREATE TABLE [Users] (
	id_user integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	priority nvarchar(255) NOT NULL,
	login nvarchar(255) NOT NULL,
	password nvarchar(255) NOT NULL,
	first_name nvarchar(255) NOT NULL,
	mid_name nvarchar(255),
	last_name nvarchar(255) NOT NULL,
	document_number integer NOT NULL,
	date_birth date NOT NULL,
	id_department integer NOT NULL FOREIGN KEY REFERENCES Departments(id_department),
	job_title nvarchar(255) NOT NULL,
	date_registration date NOT NULL
)
GO

CREATE TABLE [Authors] (
	id_author integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	first_name nvarchar(255) NOT NULL,
	mid_name nvarchar(255),
	last_name nvarchar(255),
	date_birth nvarchar(255) NOT NULL,
	date_death nvarchar(255)
)
GO

CREATE TABLE [Book_general] (
	id_book_general integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	title nvarchar(255) NOT NULL,
	udc nvarchar(255) NOT NULL,
	date_delivery date NOT NULL
)
GO

CREATE TABLE [Book_general_Authors] (
	id_book_general integer NOT NULL FOREIGN KEY REFERENCES Book_general(id_book_general),
	id_author integer NOT NULL FOREIGN KEY REFERENCES Authors(id_author)
)
GO

CREATE TABLE [Translators] (
	id_translator integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	first_name nvarchar(255) NOT NULL,
	mid_name nvarchar(255),
	last_name nvarchar(255) NOT NULL
)
GO

CREATE TABLE [Genres] (
	id_genre integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	name nvarchar(255) NOT NULL
)
GO

CREATE TABLE [Book_general_Genres] (
	id_book_general integer NOT NULL FOREIGN KEY REFERENCES Book_general(id_book_general),
	id_genre integer NOT NULL FOREIGN KEY REFERENCES Genres(id_genre)
)
GO

CREATE TABLE [Book_editions] (
	id_book_edition integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	id_publishing_house integer NOT NULL FOREIGN KEY REFERENCES Publishing_houses(id_publishing_house),
	id_book_general integer NOT NULL FOREIGN KEY REFERENCES Book_general(id_book_general),
	edition_year integer NOT NULL,
	count_pages integer NOT NULL,
	is_illustrated bit NOT NULL,
	isbn nvarchar(255) NOT NULL UNIQUE,
	lbc nvarchar(255) NOT NULL,
	is_original bit NOT NULL,
	count_exemplars integer NOT NULL,
	count_available integer NOT NULL
)
GO

CREATE TABLE [Book_exemplars] (
	id_book_exemplar integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	id_book_edition integer NOT NULL FOREIGN KEY REFERENCES Book_editions(id_book_edition),
	is_free bit NOT NULL
)
GO

CREATE TABLE [Actions] (
	id_action integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	id_book_exemplar integer NOT NULL FOREIGN KEY REFERENCES Book_exemplars(id_book_exemplar),
	id_user integer NOT NULL FOREIGN KEY REFERENCES Users(id_user),
	date_borrowing date NOT NULL,
	date_required date NOT NULL,
	date_actual date
)
GO

CREATE TABLE [Book_editions_Translators] (
	id_book_edition integer NOT NULL FOREIGN KEY REFERENCES Book_editions(id_book_edition),
	id_translator integer NOT NULL FOREIGN KEY REFERENCES Translators(id_translator)
)
GO

ALTER TABLE Book_general_Authors ADD CONSTRAINT Book_general_Authors_pk PRIMARY KEY(id_book_general, id_author)

ALTER TABLE Book_editions_Translators ADD CONSTRAINT Book_editions_Translators_pk PRIMARY KEY(id_book_edition, id_translator)

ALTER TABLE Book_general_Genres ADD CONSTRAINT Book_general_Genres_pk PRIMARY KEY(id_book_general, id_genre)
