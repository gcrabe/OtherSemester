#include "Transform.h"
#include <cmath>

using namespace System::Collections::Generic;

mat T;

void times(mat a, mat b, mat c)
{
	for (int i = 0; i < M; i++) 
	{
		for (int j = 0; j < M; j++) 
		{
			float skalaar = 0;
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
		float skalaar = 0;
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
	 b.x = ((float)a[0]) / a[2];
	 b.y = ((float)a[1]) / a[2];
}


void makeHomogenVec(float x, float y, vec c) 
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

void move(float Tx, float Ty, mat c)
{
	 unit(c);
	 c[0][M - 1] = Tx;
	 c[1][M - 1] = Ty;
}

void Rotate(float phi, mat c, bool sense)
{
	 unit(c);
	 if (!sense)
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

void Zoom(float S, mat c)
{
	 unit(c);
	 c[0][0] = S; 
	 c[1][1] = S;
}

void OriginalState(mat a,mat b,mat c)
{
	unit(a);
	unit(b);
	unit(c);
}

void Representation(mat a,int width,int height,bool coordinateAxis)
{
	unit(a);
	if (!coordinateAxis)
	{
		a[0][0] = -1;
		a[1][1] = 1;
		a[0][M - 1] = ((float)width);
	}
	else
	{
		a[0][0] = 1;
		a[1][1] = -1;
		a[1][M - 1] = ((float)height);
	}
}

void RotateAboutCentre(float phi, int width, int height, mat R, mat T, mat T1,bool sense)
{
	unit(R);
	R[0][M - 1] = -((float)width)/2;
	R[1][M - 1] = -((float)height)/2;
	times(R, T, T1);
	set(T1, T);
	unit(R);
	if (!sense)
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
	R[0][M - 1] = ((float)width) / 2;
	R[1][M - 1] = ((float)height) / 2;
}

void ZoomAboutCentre(float S, int width, int height, mat R, mat T, mat T1)
{
	unit(R);
	R[0][M - 1] = -((float)width) / 2;
	R[1][M - 1] = -((float)height) / 2;
	times(R, T, T1);
	set(T1, T);
	unit(R);
	R[0][0] = S;
	R[1][1] = S;
	times(R, T, T1);
	set(T1, T);
	unit(R);
	R[0][M - 1] = ((float)width) / 2;
	R[1][M - 1] = ((float)height) / 2;
}

void ZoomAboutAxes(float S,float minVal,float maxVal, int width,int height,mat R, mat T, mat T1, bool sense)
{
	if (!sense)
	{
		unit(R);
		R[0][M - 1] = -((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = -((float)height) / 2;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][0] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = ((float)height) / 2;
	}
	else
	{
		unit(R);
		R[0][M - 1] = -((float)width)/2;
		R[1][M - 1] = -((maxVal - minVal) / 2 + minVal);
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[1][1] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((float)width) / 2;
		R[1][M - 1] = ((maxVal - minVal) / 2 + minVal);
	}
}

void ShowNorm(float minYVal, float maxYVal, mat R, mat T, mat T1)
{
	unit(R);
	move(0, -(minYVal + maxYVal), R);
	times(R, T, T1);
	set(T1, T);
	unit(R);
	Representation(R, 0, 0, true);
}