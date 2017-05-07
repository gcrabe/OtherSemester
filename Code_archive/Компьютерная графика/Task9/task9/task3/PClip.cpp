#include "stdafx.h"
#include <algorithm>
#include "Transform.h"

using namespace std;

#define INF 2147483647.0

polygon^ Pclip(polygon^ P, point Pmin, point Pmax)
{
	int k = 0;
	int n = P->Count;
	point pnt1 = P[n - 1];
	int n1 = 0;
	polygon^ P1 = gcnew polygon(0);
	while (k<n)
	{
		point pnt2 = P[k];
		float dx = pnt2.x - pnt1.x;
		float dy = pnt2.y - pnt1.y;
		float outx = 0.0;
		float inx = 0.0;
		float outy = 0.0;
		float iny = 0.0;
		float inf = 1e9;
		if (dx>0 || (dx == 0 && pnt1.x>Pmax.x))
		{
			inx = Pmin.x;
			outx = Pmax.x;
		}
		else
		{
			outx = Pmin.x;
			inx = Pmax.x;
		}
		if (dy>0 || (dy == 0 && pnt1.y>Pmax.y))
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
		if (dx != 0)
		{

			toutX = (outx - pnt1.x) / dx;
		}
		else
		{
			if (Pmin.x <= pnt1.x && pnt1.x <= Pmax.x)
			{
				toutX = inf;
			}
			else
			{
				toutX = -inf;
			}
		}
		if (dy != 0)
		{

			toutY = (outy - pnt1.y) / dy;
		}
		else
		{
			if (Pmin.y <= pnt1.y && pnt1.y <= Pmax.y)
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
		if (toutX<toutY)
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
		if (t2out>0)
		{
			if (dx != 0)
			{
				tinX = (inx - pnt1.x) / dx;
			}
			else
			{
				tinX = inf;
			}
			if (dy != 0)
			{
				tinY = (iny - pnt1.y) / dy;
			}
			else
			{
				tinY = -inf;
			}
			if (tinX<tinY)
			{
				t2in = tinY;
			}
			else
			{
				t2in = tinX;
			}
			if (t1out<t2in)
			{
				if (0<t1out&& t1out <= 1)
				{
					n1 = n1 + 1;
					if (tinX<tinY)
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
				if (t1out>0 && t2in <= 1)
				{
					if (t2in >= 0)
					{
						n1 = n1 + 1;
						if (tinX>tinY)
						{
							point temp;
							temp.x = inx;
							temp.y = pnt1.y + tinX*dy;
							P1->Add(temp);
						}
						else
						{
							point temp;
							temp.x = pnt1.x + tinY*dx;
							temp.y = iny;
							P1->Add(temp);
						}
					}
					if (t1out <= 1)
					{
						n1 = n1 + 1;
						if (toutX<toutY)
						{
							point temp;
							temp.x = outx;
							temp.y = pnt1.y + toutX*dy;
							P1->Add(temp);
						}
						else
						{
							point temp;
							temp.x = pnt1.x + toutY*dx;
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
			if (0<t2out && t2out <= 1)
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