#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

void func(int n)
{
	int d = 1;

	for (int i = 2; i <= n; i++)
	{
		if (n % i == 0)
		{
			bool prime = 1;

			for (int k = 2; k * k <= i; k++)
				if (i % k == 0)
				{
					prime = 0;
					break;
				}

			if (prime)
				d = i;
		}
	}

	cout << n << " -> " << d << endl;
}

int main(int argc, char **argv)
{
	for (int i = 0; i < 10; i++)
		func(i);

	system("pause");

	return 0;
}