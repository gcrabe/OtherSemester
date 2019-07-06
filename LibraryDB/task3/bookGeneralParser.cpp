#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

const int MAXN = 27;

int main() {

	freopen("bookGeneral.in", "rt", stdin);
	freopen("bookGeneral.out", "wt", stdout);

	std::string title;

	for (int i = 0; i < MAXN; i++) {
		std::getline(std::cin, title);

		int udc[3] = {rand() % 1000, rand() % 1000, rand() % 1000};

		int year = 1900 + rand() % 100;
		int month = rand() % 12;
		int day = rand() % 29;

		std::cout << "INSERT INTO Book_general(title, udc, date_delivery) ";
		std::cout << "VALUES(N'" << title << "', ";
		std::cout << "N'" << udc[0] << ' ' << udc[1] << '.' << udc[2] << "', ";
		std::cout << '\'' << year << '-' << month << '-' << day << "')" << std::endl;
	}	

	return 0;
}