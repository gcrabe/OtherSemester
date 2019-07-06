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

void OriginalState(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy,mat a,mat b,mat c)
{
	unit(a);
	unit(b);
	unit(c);
	frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, b);
}

void Representation(mat a, bool coordinateAxis)
{
	unit(a);
	if (!coordinateAxis)
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

void RepresentationCentre(mat a,int width,int height,bool coordinateAxis)
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
	R[0][M - 1] = -((float)width);
	R[1][M - 1] = -((float)height);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	R[0][0] = S;
	R[1][1] = S;
	times(R, T, T1);
	set(T1, T);

	unit(R);
	R[0][M - 1] = ((float)width);
	R[1][M - 1] = ((float)height);
	times(R, T, T1);
	set(T1, T);
}

void ZoomAboutAxes(float S, float minVal, float maxVal, int width, int height, mat R, mat T, mat T1, bool sense)
{
	if (!sense)
	{
		unit(R);
		//R[0][M - 1] = -((maxVal-minVal)/2+minVal);
		R[0][M - 1] = -((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = -((float)height) / 2;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][0] = S;
		//R[1][1] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((maxVal - minVal) / 2 + minVal);
		R[1][M - 1] = ((float)height) / 2;

	}
	else
	{
		unit(R);
		R[0][M - 1] = -((float)width) / 2;
		R[1][M - 1] = -((maxVal - minVal) / 2 + minVal);
		times(R, T, T1);
		set(T1, T);
		unit(R);
		//R[0][0] = S;
		R[1][1] = S;
		times(R, T, T1);
		set(T1, T);
		unit(R);
		R[0][M - 1] = ((float)width) / 2;
		R[1][M - 1] = ((maxVal - minVal) / 2 + minVal);
	}
}

void ZoomAboutAxes2(float S, mat R, bool sense)
{
	if (!sense)
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

void ZoomResize(float S, int Wcx, int Wcy, mat R, mat T, mat T1, bool sense)
{
	if (!sense)
	{
		unit(R);
		move(-Wcx,-Wcy,R);
		times(R, T, T1);
		set(T1, T);

		RepresentationCentre(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		ZoomAboutAxes2(S,R,false);
		times(R, T, T1);
		set(T1, T);

		RepresentationCentre(R, 0, 0, false);
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

		RepresentationCentre(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		ZoomAboutAxes2(S, R, true);
		times(R, T, T1);
		set(T1, T);

		RepresentationCentre(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		move(Wcx, Wcy, R);
	}
	times(R, T, T1);
	set(T1, T);
}

void ShowNorm(float minYVal, float maxYVal, mat R, mat T, mat T1)
{
	unit(R);
	move(0, -(minYVal + maxYVal), R);
	times(R, T, T1);
	set(T1, T);
	unit(R);
	RepresentationCentre(R, 0, 0, true);
}

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat T)
{
	mat R;
	mat T1;
	move(Vcx, Vcy, R);
	times(R, T, T1);
	set(T1, T);

	Zoom(Wx / Vx, R);
	times(R, T, T1);
	set(T1, T);

	Zoom(Wy / Vy, R);
	times(R, T, T1);
	set(T1, T);

	RepresentationCentre(R,0,0,true);
	times(R, T, T1);
	set(T1,T);

	move(Wcx, Wcy, R);
	times(R, T, T1);
	set(T1, T);
}

bool Clip(point &A, point &B, point Pmin, point Pmax)

	if (steep)
	{
		Swap(x1, y1);
		Swap(x2, y2);
	}

	if (x1 > x2)
	{
		Swap(x1,x2);
		Swap(y1,y2);
	}

	int dx = x2 - x1;
	int dy = System::Math::Abs(y2 - y1);
	int error = dx / 2;
	int ystep = (y1 < y2) ? 1 : -1;
	int y = y1;
	for (int x = x1; x <= x2; x++)
	{
		image->SetPixel(steep ? y : x, steep ? x : y,pen);
		error -= dy;
		if (error < 0)
		{
			y += ystep;
			error += dx;
		}
	}