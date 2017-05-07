#pragma once

#include "stdafx.h"
#include "Transform.h"

#include <math.h>

t_matrix ETransform;

void t_times_matrix_to_matrix(t_matrix a, t_matrix b, t_matrix c)
{
	for (int i = 0; i < MDIM; i++)
	{
		for (int j = 0; j < MDIM; j++)
		{
			float tempVal = 0;

			for (int k = 0; k < MDIM; k++)
				tempVal += a[i][k] * b[k][j];

			c[i][j] = tempVal;
		}
	}
}

void t_times_matrix_to_vector(t_matrix a, t_vector b, t_vector c)
{
	for (int i = 0; i < MDIM; i++)
	{
		float tempVal = 0;

		for (int j = 0; j < MDIM; j++)
			tempVal += a[i][j] * b[j];

		c[i] = tempVal;
	}
}

void t_set(t_matrix a, t_matrix b)
{
	for (int i = 0; i < MDIM; i++)
		for (int j = 0;  j < MDIM; j++)
			b[i][j] = a[i][j];
}

void t_point_to_vector(t_point a, t_vector b)
{
	b[0] = a.x;
	b[1] = a.y;
	b[2] = 1.0;
}

void t_vector_to_point(t_vector a, t_point &b)
{
	b.x = ((float) a[0]) / a[2];
	b.y = ((float) a[1]) / a[2];
}

void t_make_uniform_vector(float x, float y, t_vector c)
{
	c[0] = x;
	c[1] = y;
	c[2] = 1.0;
}

void t_unit(t_matrix a)
{
	for (int i = 0; i < MDIM; i++)
		for (int j = 0; j < MDIM; j++)
			a[i][j] = (i == j) ? 1 : 0;
}

void t_move(float Tx, float Ty, t_matrix c)
{
	t_unit(c);

	c[0][MDIM - 1] = Tx;
	c[1][MDIM - 1] = Ty;
}

void t_rotate(float phi, t_matrix c)
{
	t_unit(c);

	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);
}

void t_scale(float Sz, t_matrix c)
{
	t_unit(c);

	c[0][0] = Sz;
	c[1][1] = Sz;
}

void t_reflection_vertical(t_matrix c)
{
	t_unit(c);

	c[0][0] = -1;
	c[1][1] = 1;
}

void t_reflection_horizontal(t_matrix c)
{
	t_unit(c);
	
	c[0][0] = 1;
	c[1][1] = -1;
}
