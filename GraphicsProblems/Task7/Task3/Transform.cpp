#include "stdafx.h"
#include "Transform.h"
#include <cmath>

using namespace System::Collections::Generic;

mat T;
mat backupT;
std::vector<mat> matrices(0);


void times(mat a, mat b, mat &c)
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

void timesMatVec(mat a, vec b, vec &c)
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

void set(mat a, mat &b) 
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < M; j++)
		{
			b[i][j] = a[i][j];
		}
	}
}

void point2vec(point a, vec &b) 
{
	b[0] = a.x; 
	b[1] = a.y; 
	b[2] = 1;
}

void vec2point(vec a, point &b) 
{
	 b.x = ((float)a[0]) / a[2];
	 b.y = ((float)a[1]) / a[2];
}

void makeHomogenVec(float x, float y, vec &c) 
{
	 c[0] = x; 
	 c[1] = y; 
	 c[2] = 1;
}

void unit(mat &a)
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

void move(float Tx, float Ty, mat &c)
{
	 unit(c);
	 c[0][M - 1] = Tx;
	 c[1][M - 1] = Ty;
}

void rotate(float phi, mat &c, bool direction)
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

void scale(float S, mat &c)
{
	 unit(c);
	 c[0][0] = S; 
	 c[1][1] = S;
}

void originalState(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy,mat &a,mat &b,mat &c)
{
	unit(a);
	unit(b);
	unit(c);

	frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, b);
}

void reflectDefault(mat &a, bool axis)
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

void reflect(mat &a,int width,int height,bool axis)
{
	unit(a);

	if (!axis)
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

void rotateCenter(float phi, int width, int height, mat &R, mat &T, mat &T1,bool direction)
{
	unit(R);
	R[0][M - 1] = -((float)width)/2;
	R[1][M - 1] = -((float)height)/2;

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

	R[0][M - 1] = ((float)width) / 2;
	R[1][M - 1] = ((float)height) / 2;
}

void scaleCenter(float S, int width, int height, mat &R, mat &T, mat &T1)
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

void scaleAxes(float S, float minVal, float maxVal, int width, int height, mat &R, mat &T, mat &T1, bool direction)
{
	if (!direction)
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

		R[0][M - 1] = -((float)width) / 2;
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

void scaleAxes2(float S, mat &R, bool direction)
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

void scaleX(double S, mat &c)
{
	unit(c);
	c[0][0] = S;
}

void scaleY(double S, mat &c)
{
	unit(c);
	c[1][1] = S;
}

void scaleResize(float S, int Wcx, int Wcy, mat &R, mat &T, mat &T1, bool direction)
{
	if (!direction)
	{
		unit(R);
		move(-Wcx, -Wcy, R);
		times(R, T, T1);
		set(T1, T);

		reflect(R, 0, 0, false);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		scaleAxes2(S, R, false);
		times(R, T, T1);
		set(T1, T);

		reflect(R, 0, 0, false);
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

		reflect(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		scaleAxes2(S, R, true);
		times(R, T, T1);
		set(T1, T);

		reflect(R, 0, 0, true);
		times(R, T, T1);
		set(T1, T);

		move(Wcx, Wcy, R);
	}

	times(R, T, T1);
	set(T1, T);
}

void ShowNorm(float minYVal, float maxYVal, mat &R, mat &T, mat &T1)
{
	unit(R);
	move(0, -(minYVal + maxYVal), R);
	times(R, T, T1);
	set(T1, T);
	unit(R);
	reflect(R, 0, 0, true);
}

void frameIcon(float Vcx, float Vcy, float Vx, float Vy, float Wcx, float Wcy, float Wx, float Wy, mat &T)
{
	mat R;
	mat T1;
	unit(R);
	move(-Vcx, -Vcy, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	scaleX(Wx /Vx, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	scaleY(Wy / Vy, R);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	reflectDefault(R,true);
	times(R, T, T1);
	set(T1, T);

	unit(R);
	move(Wcx, Wcy, R);
	times(R, T, T1);
	set(T1, T);
}

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &T)
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
	reflect(R,0,0,true);
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
	float tMin = 0.0;
	float tMax = 1.0;
	float N[4][2] = { { 1,0 },{ 0,-1 },{ -1,0 },{ 0,1 } };
	float F[4][2] = { { Pmin.x, Pmin.y },{ Pmin.x, Pmax.y },{ Pmax.x, Pmax.y },{ Pmax.x, Pmin.y } };
	float p[2] = { B.x - A.x,B.y - A.y };
	float p1[2] = { A.x,A.y };
	for (int i = 1; i <= 4; i++)
	{
		float P = p[0] * N[i - 1][0] + p[1] * N[i - 1][1];
		float Q = (p1[0] - F[i - 1][0])*N[i - 1][0] + (p1[1] - F[i - 1][1])*N[i - 1][1];
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
		float x1 = A.x + (B.x - A.x)*tMin;
		float x2 = A.x + (B.x - A.x)*tMax;;
		float y1 = A.y + (B.y - A.y)*tMin;
		float y2 = A.y + (B.y - A.y)*tMax;;
		A.x = x1;
		B.x = x2;
		A.y = y1;
		B.y = y2;
		return true;
	}
	return false;
}

point ConvertPoint(mat &T, point a)
{
	vec A;
	point2vec(a, A);
	vec A1;
	timesMatVec(T, A, A1);
	vec2point(A1, a);
	return a;
}
polygon^ ConvertP(polygon^ P, mat T)
{
	polygon^ P1=gcnew polygon(0);
	point a;
	/*point2vec(p[p->Count - 1], A);
	timesMatVec(T, A, A1);
	vec2point(A1, a);*/
	for (int j = 0; j < P->Count; j++){
		/*point2vec(p[j], B);
		timesMatVec(T, B, B1);
		vec2point(B1, b);*/
		a=ConvertPoint(T,P[j]);
		P1->Add(a);
	}
	return P1;
}

polygon^ Pclip (polygon^ P, point Pmin, point Pmax)
{
	int k = 0;
	int n = P->Count;
	point pnt1 = P[n-1];
	int n1 = 0;
	polygon^ P1 = gcnew polygon(0);

	while(k < n)
	{
		point pnt2 = P[k];
		float dx = pnt2.x - pnt1.x;
		float dy = pnt2.y - pnt1.y;
		float outx = 0.0;
		float inx = 0.0;
		float outy = 0.0;
		float iny  =0.0;
		float inf = 1e9;
		if(dx > 0 || (dx == 0 && pnt1.x > Pmax.x))
		{
			inx = Pmin.x;
			outx = Pmax.x;
		}
		else
		{
			outx = Pmin.x;
			inx = Pmax.x;
		}
		if(dy > 0 || (dy == 0 && pnt1.y > Pmax.y))
		{
			iny = Pmin.y;
			outy = Pmax.y;
		}
		else
		{
			outy = Pmin.y;
			iny = Pmax.y;
		}
		float toutX = 0.0;
		float toutY = 0.0;
		if(dx != 0)
		{

			toutX = (outx - pnt1.x) / dx;
		}
		else
		{
			if(Pmin.x <= pnt1.x && pnt1.x <= Pmax.x)
			{
				toutX = inf;
			}
			else
			{
				toutX = -inf;
			}
		}
		if(dy != 0)
		{

			toutY = (outy - pnt1.y) / dy;
		}
		else
		{
			if(Pmin.y <= pnt1.y && pnt1.y <= Pmax.y)
			{
				toutY = inf;
			}
			else
			{
				toutY = -inf;
			}
		}
		float t1out = 0.0;
		float t2out = 0.0;
		if(toutX < toutY)
		{
			t1out = toutX;
			t2out = toutY;
		}
		else
		{
			t1out = toutY;
			t2out = toutX;
		}
		float tinX = 0.0;
		float tinY = 0.0;
		float t2in = 0.0;
		if(t2out > 0)
		{
			if(dx != 0)
			{
				tinX = (inx - pnt1.x) / dx;
			}
			else
			{
				tinX = inf;
			}
			if(dy!=0)
			{
				tinY = (iny - pnt1.y) / dy;
			}
			else
			{
				tinY = -inf;
			}
			if(tinX < tinY)
			{
				t2in = tinY;
			}
			else
			{
				t2in = tinX;
			}
			if(t1out < t2in)
			{
				if(0 < t1out && t1out <= 1)
				{
					n1 = n1 + 1;

					if(tinX < tinY)
					{
						point temp;
						temp.x = outx;
						temp.y = iny;
						P1->Add(temp);
					}
					else
					{
						point temp;
						temp.x = inx;
						temp.y = outy;
						P1->Add(temp);
					}
				}
			}
			else
			{
				if(t1out > 0 && t2in <= 1)
				{
					if(t2in >= 0)
					{
						n1 = n1 + 1;
						if(tinX > tinY)
						{
							point temp;
							temp.x = inx;
							temp.y = pnt1.y + tinX * dy;
							P1->Add(temp);
						}
						else
						{
							point temp;
							temp.x = pnt1.x + tinY * dx;
							temp.y = iny;
							P1->Add(temp);
						}
					}
					if(t1out <= 1)
					{
						n1 = n1 + 1;
						if(toutX < toutY)
						{
							point temp;
							temp.x = outx;
							temp.y = pnt1.y + toutX * dy;
							P1->Add(temp);
						}
						else
						{
							point temp;
							temp.x = pnt1.x + toutY * dx;
							temp.y = outy;
							P1->Add(temp);
						}
					}
					else
					{
						n1 = n1 + 1;
						P1->Add(pnt2);
					}
				}
			}
			if(0 < t2out && t2out <= 1)
			{
				n1 = n1 + 1;
				point temp;
				temp.x = outx;
				temp.y = outy;
				P1->Add(temp);
			}
		}

		k = k + 1;
		pnt1 = pnt2;
	}
	return P1;
}
