#include "Function.h"
#include<cmath>

double F(double x)
{
	return tan(3.1415926535 /(double)180*x);
	//return 1.0/x;
}

bool FExist(double x)
{
	if (abs(cos(3.1415926535 / (double)180 * x)) < 0.001)
	{
		return false;
	}
	//if (abs(x)<0.0001)
	//{
	//	return false;
	//}
	return true;
}