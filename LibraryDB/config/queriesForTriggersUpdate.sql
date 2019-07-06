use Library
go

insert into Cities(name) values(N'Nsk')

insert into Publishing_houses(name, id_city) values(N'Science', 1)

insert into Book_General(title, udc, date_delivery) values(N'Title', N'Udc', '2000-5-5')

insert into Book_editions(id_publishing_house, id_book_general, edition_year, count_pages, is_illustrated, isbn, lbc,
							is_original, count_exemplars, count_available) 
	values (1, 1, 2001, 495, 1, N'123123', N'123123', 1, 100, 10)

insert into Book_exemplars(id_book_edition, is_free) values(1, 1)

insert into Actions(id_book_exemplar, id_user, date_borrowing, date_required, date_actual) values(1, 1, '2005-5-5', '2005-5-10', '')

----------------------

update Actions set date_actual = '2006-5-5' where id_action = 4