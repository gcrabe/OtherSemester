#include "stdafx.h"
#include "Transform.h"
#include "Clip.h"

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
		float x1 = A.x + (B.x - A.x) * tMin;
		float x2 = A.x + (B.x - A.x) * tMax;;
		float y1 = A.y + (B.y - A.y) * tMin;
		float y2 = A.y + (B.y - A.y) * tMax;;

		A.x = x1;
		B.x = x2;
		A.y = y1;
		B.y = y2;

		return true;
	}

	return false;
}
