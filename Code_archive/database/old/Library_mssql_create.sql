CREATE TABLE [Authors] (
	idAuthor integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	firstName nvarchar(256) NOT NULL,
	lastName nvarchar(256) NOT NULL,
	patronymicName nvarchar(256) NOT NULL,
	birthDate date NOT NULL,
	deathDate date NOT NULL
)
GO
CREATE TABLE [Publishing_houses] (
	idPublishingHouse integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	name nvarchar(256) NOT NULL,
	city nvarchar(256) NOT NULL
)
GO
CREATE TABLE [Readership] (
	idReader integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	firstName nvarchar(256) NOT NULL,
	lastName nvarchar(256) NOT NULL,
	patronymicName nvarchar(256) NOT NULL,
	birthDate date NOT NULL,
	institution nvarchar(256) NOT NULL,
	subdivision nvarchar(256) NOT NULL,
	position nvarchar(256) NOT NULL,
	receiptDate date NOT NULL
)
GO
CREATE TABLE [Book_general] (
	idBook integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	title nvarchar(256) NOT NULL,
	author integer NOT NULL FOREIGN KEY REFERENCES Authors(idAuthor),
	genre nvarchar(256) NOT NULL,
	udc nvarchar(256) NOT NULL,
	dateReceipt date NOT NULL
)
GO
CREATE TABLE [Book_edition] (
	idEdition integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	publishingHouse integer NOT NULL FOREIGN KEY REFERENCES Publishing_houses(idPublishingHouse),
	book integer NOT NULL FOREIGN KEY REFERENCES Book_general(idBook),
	editionDate date NOT NULL,
	pageCount integer NOT NULL,
	containsIllustrations bit NOT NULL,
	isbn nvarchar(256) NOT NULL,
	lbc nvarchar(256) NOT NULL,
	inTranslation bit NOT NULL,
	translators nvarchar(256) NOT NULL,
	cntSpecimen integer NOT NULL,
	cntFree integer NOT NULL
)
GO
CREATE TABLE [ExemplarList] (
	inventoryNumber integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	bookEdition integer NOT NULL FOREIGN KEY REFERENCES Book_edition(idEdition),
	free bit NOT NULL
	
)
GO
CREATE TABLE [ActionList] (
	idAction integer NOT NULL PRIMARY KEY IDENTITY(1, 1),
	exemplar integer NOT NULL FOREIGN KEY REFERENCES ExemplarList(inventoryNumber),
	reader integer NOT NULL FOREIGN KEY REFERENCES Readership(idReader),
	dateStart date NOT NULL,
	dateEnd date NOT NULL
)
