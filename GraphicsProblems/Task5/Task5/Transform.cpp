#pragma once

#include "stdafx.h"
#include "Transform.h"
#include <cmath>

using namespace System::Collections::Generic;

mat T;
mat T2;
mat TCoo;
mat TPoint;

void times(mat a, mat b, mat c)
{
	for (int i = 0; i < M; i++) 
	{
		for (int j = 0; j < M; j++) 
		{
			double skalaar = 0;
			for (int k = 0; k < M; k++)
			{
				skalaar += a[i][k] * b[k][j];
			}
			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec c)
{
	for (int i = 0; i < M; i++)
	{
		double skalaar = 0;
		for (int j = 0; j < M; j++)
		{
			skalaar += a[i][j] * b[j];
		}
		c[i] = skalaar;

	}
}

void set(mat a, mat b) 
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}

void point2vec(point a, vec b) 
{
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point& b) 
{
	 b.x = ((double)a[0]) / a[2];
	 b.y = ((double)a[1]) / a[2];
}

void makeHomogenVec(double x, double y, vec c) 
{
	 c[0] = x; 
	 c[1] = y; 
	 c[2] = 1;
}

void unit(mat a)
{
	 for (int i = 0; i < M; i++)
	 {
		 for (int j = 0; j < M; j++)
		 {
			 if (i == j)
			 {
				 a[i][j] = 1;
			 }
			 else
			 {
				 a[i][j] = 0;
			 }

		 }
	 }
}

void move(double Tx, double Ty, mat c)
{
	 unit(c);
	 c[0][M - 1] = Tx;
	 c[1][M - 1] = Ty;
}

void rotate(double phi, mat c, bool direction)
{
	 unit(c);
	 if (!direction)
	 {
		 c[0][0] = cos(phi);
		 c[0][1] = -sin(phi);
		 c[1][0] = sin(phi);
		 c[1][1] = cos(phi);
	 }
	 else
	 {
		 c[0][0] = cos(phi);
		 c[0][1] = sin(phi);
		 c[1][0] = -sin(phi);
		 c[1][1] = cos(phi);
	 }
}

void scale(double S, mat c)
{
	 unit(c);
	 c[0][0] = S; 
	 c[1][1] = S;
}

void originalState(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy,mat a,mat b,mat c)
{
	unit(a);
	unit(b);
	unit(c);
	frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, b);
}

void reflectDefalut(mat a, bool axis)
{
	unit(a);
	if (!axis)
	{
		a[0][0]= -1;
		a[1][1]= 1;
	}
	else
	{
		a[0][0]= 1;
		a[1][1]= -1;
	}
}

void reflectCenter(mat a,int width,int height,bool axis)
{
	unit(a);
	if (!axis)
	{
		a[0][0] = -1;
		a[1][1] = 1;
		a[0][M - 1] = ((double)width);
	}
	else
	{
		a[0][0] = 1;
		a[1][1] = -1;
		a[1][M - 1] = ((double)height);
	}
}

void rotateCenter(double phi, int width, int height, mat R, mat T, mat T1,bool direction)
{
	unit(R);
	R[0][M - 1] = -((double)width)/2;
	R[1][M - 1] = -((double)height)/2;
	times(R, T, T1);
	set(T1, T);
	unit(R);
	if (!direction)
	{
		R[0][0] = cos(phi);
		R[0][1] = -sin(phi);
		R[1][0] = sin(phi);
		R[1][1] = cos(phi);
	}
	else
	{
		R[0][0] = cos(phi);
		R[0][1] = sin(phi);
		R[1][0] = -sin(phi);
		R[1][1] = cos(phi);
	}
	times(R, T, T1);
	set(T1, T);
	unit(R);
	R[0][M - 1] = ((double)width) / 2;
	R[1][M - 1] = ((double)height) / 2;
}

void scaleCenter(double S, double width, double height, mat R, mat T, mat T1)
{
	unit(R);
	R[0][M - 1] = -((double)width);
	R[1][M - 1] = -((double)height);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	R[0][0] = S;
	R[1][1] = S;
	times(R, T, T1);
	set(T1, T);

	unit(R);
	R[0][M - 1] = ((double)width);
	R[1][M - 1] = ((double)height);
	times(R, T, T1);
	set(T1, T);
}

void scaleAxes2(double S, mat R, bool direction)
{
	if (!direction)
	{
		unit(R);
		R[0][0] = S;

	}
	else
	{
		unit(R);
		R[1][1] = S;
	}
}

void scaleAxes(double S, double Wcx, double Wcy, mat R, mat T, mat T1, bool direction)
{
	if (!direction)
	{
		unit(R);
		unit(T1);
		move(-Wcx, -Wcy, R);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		unit(T1);
		scaleAxes2(S, R, false);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		unit(T1);
		move(Wcx, Wcy, R);
	}
	else
	{
		unit(R);
		unit(T1);
		move(-Wcx, -Wcy, R);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		unit(T1);
		scaleAxes2(S, R, true);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		unit(R);

		move(Wcx, Wcy, R);
	}
}

void scaleAxesDr(double S, double minVal, double maxVal, int width, int height, mat R, mat T, mat T1, bool direction)
{
	if (!direction)
	{
		unit(R);
		R[0][M - 1] = -((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = -((double)height) / 2;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][0] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = ((double)height) / 2;

	}
	else
	{
		unit(R);
		R[0][M - 1] = -((double)width) / 2;
		R[1][M - 1] = -((maxVal - minVal) / 2 + minVal);
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[1][1] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((double)width) / 2;
		R[1][M - 1] = ((maxVal - minVal) / 2 + minVal);
	}
}

void scaleResize(double S, int Wcx, int Wcy, mat R, mat T, mat T1, bool direction)
{
	if (!direction)
	{
		unit(R);
		move(-Wcx, -Wcy, R);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		scaleAxes2(S, R, false);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		move(Wcx, Wcy, R);
	}
	else
	{
		unit(R);
		move(-Wcx, -Wcy, R);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		scaleAxes2(S, R, true);
		times(R, T, T1);
		set(T1, T);

		reflectCenter(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		move(Wcx, Wcy, R);
	}
	times(R, T, T1);
	set(T1, T);
}

void scaleX(double S, mat c)
{
	unit(c);
	c[0][0] = S;
}

void scaleY(double S, mat c)
{
	unit(c);
	c[1][1] = S;
}

void showNorm(double minYVal, double maxYVal, mat R, mat T, mat T1)
{
	unit(R);
	move(0, -(minYVal + maxYVal), R);
	times(R, T, T1);
	set(T1, T);
	unit(R);
	reflectCenter(R, 0, 0, true);
}

void frame(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy, mat T)
{
	mat R;
	mat T1;
	unit(R);
	move(Vcx, Vcy, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	scaleX(Wx / Vx, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	scaleY(Wy / Vy, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	reflectCenter(R,0,0,true);
	times(R, T, T1);
	set(T1,T);

	unit(R);
	move(Wcx, Wcy, R);
	times(R, T, T1);
	set(T1, T);
}

bool Clip(point &A, point &B, point Pmin, point Pmax)
{
	bool visiable = true;
	double tMin = 0.0;
	double tMax = 1.0;
	double N[4][2] = { { 1,0 },{ 0,-1 },{ -1,0 },{ 0,1 } };
	double F[4][2] = { { Pmin.x, Pmin.y },{ Pmin.x, Pmax.y },{ Pmax.x, Pmax.y },{ Pmax.x, Pmin.y } };
	double p[2] = { B.x - A.x,B.y - A.y };
	double p1[2] = { A.x,A.y };
	for (int i = 1; i <= 4; i++)
	{
		double P = p[0] * N[i - 1][0] + p[1] * N[i - 1][1];
		double Q = (p1[0] - F[i - 1][0])*N[i - 1][0] + (p1[1] - F[i - 1][1])*N[i - 1][1];
		if (P == 0)
		{
			if (Q < 0)
			{
				visiable = false;
				break;
			}
		}
		else
		{
			if (P > 0)
			{
				tMin = System::Math::Max(tMin, -Q / P);
			}
			if (P < 0)
			{
				tMax = System::Math::Min(tMax, -Q / P);
			}
		}
		if (tMin > tMax)
		{
			visiable = false;
			break;
		}
	}
	if (visiable)
	{
		double x1 = A.x + (B.x - A.x)*tMin;
		double x2 = A.x + (B.x - A.x)*tMax;;
		double y1 = A.y + (B.y - A.y)*tMin;
		double y2 = A.y + (B.y - A.y)*tMax;;
		A.x = x1;
		B.x = x2;
		A.y = y1;
		B.y = y2;
		return true;
	}
	return false;
}

point ConvertPoint(mat T,point a)
{
	vec A;
	point2vec(a, A);
	vec A1;
	timesMatVec(T, A, A1);
	vec2point(A1, a);
	return a;
}
