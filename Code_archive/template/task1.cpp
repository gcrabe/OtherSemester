#include <stdio.h>
#include <iostream>
#include <string>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

using namespace std;

class TimeReport // создаем класс, в котором будет подсчитываться время
{
	const std::string m_title;
	const double m_startTime;

public:
	TimeReport(const std::string& title)
		: m_title(title)
		, m_startTime(omp_get_wtime())
	{
	}

	~TimeReport()
	{
		const double endTime = omp_get_wtime();
		std::cout << m_title << " : " << endTime - m_startTime << std::endl;
	}

private:
	TimeReport(const TimeReport&);
	TimeReport& operator = (const TimeReport&);
};


void  Function() 
{
	const int iterations = 1000;
	for (int i = 0; i < iterations; ++i) // цикл в цикле
	{
		for (int j = 0; j < iterations / 10; ++j)
		{
			const double x = 1. / (i + 1);
			const double y = 1. / (j + i);
			const double z = (sin(x) * sin(y));
			if (z > 1000)
			{
				break;
			}
		}
	}
}

int main()
{
	const int iterations = 1000;

	{
		TimeReport timeReport(" Parallel static"); // параллельная версия
#pragma omp parallel for private(i) static(iterations / 4)
		for (int i = 0; i < iterations; ++i)
		{
			Function();
		}
	}

	{
		TimeReport timeReport(" Parallel dynamic"); // параллельная версия
#pragma omp parallel for private(i) dynamic
		for (int i = 0; i < iterations; ++i)
		{
			Function();
		}
	}	

	system("pause");
	return 0;
}
