#include <cstdio>
#include <cstdlib>

#include <string>
#include <iostream>

const int MAXN = 24;

int main(int argc, char **argv) {
	freopen("authorsSample.in", "rt", stdin);
	freopen("authorsSample.out", "wt", stdout);

	std::string firstName, midName, lastName;
	
	for (int i = 0; i < MAXN; i++) {
		std::cin >> lastName >> firstName >> midName;
		
		int bYear = 1500 + rand() % 500;
		int bMonth = rand() % 12;
		int bDay = rand() % 29;

		int dYear = bYear + rand() % 100;
		int dMonth = rand() % 12;
		int dDay = rand() % 29;

		std::cout << "INSERT INTO Authors(first_name, mid_name, last_name, date_birth, date_death) ";
		std::cout << "VALUES(N'" << firstName << "', N'" << midName << "', N'" << lastName << "', '" << bYear << '-' << bMonth << '-' << bDay;
		std::cout << "', '" << dYear << '-' << dMonth << '-' << dDay << "')" << std::endl;
	}

	return 0;
}