#pragma once

#include "stdafx.h"
#include "Function.h"
#include<cmath>

const double PI = 3.14159265358979;
const double EPS = 0.001;

double F(double x) {
	return tan(PI / 180.0 * x);
}

bool FExist(double x) {
	return abs(cos(PI / 180.0 * x)) < EPS ? false : true;
}
