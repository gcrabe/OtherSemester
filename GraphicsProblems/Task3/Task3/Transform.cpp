#pragma once

#include "stdafx.h"
#include "Transform.h"

#include <math.h>

mat T;

void times(mat a, mat b, mat c) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			float skalaar = 0;

			for (int k = 0; k < M; k++) {
				skalaar += a[i][k] * b[k][j];
			}

			c[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec c) {
	for (int i = 0; i < M; i++) {
		float skalaar = 0;

		for (int j = 0; j < M; j++) {
			skalaar += a[i][j] * b[j];

			c[i] = skalaar;
		}
	}
}

void set(mat a, mat b) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			b[i][j] = a[i][j];
		}
	}
}

void point2vec(point a, vec b) {
	b[0] = a.x;
	b[1] = a.y;
	b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = (float)a[0] / a[2];
	b.y = (float)a[1] / a[2];
}

void makeHomogenVec(float x, float y, vec c) {
	c[0] = x;
	c[1] = y;
	c[2] = 1;
}

void unit(mat a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j)
				a[i][j] = 1;
			else
				a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat c) {
	unit(c);
	
	c[0][M - 1] = Tx;
	c[1][M - 1] = Ty;
}

void rotate(float phi, mat c, bool direction) {
	unit(c);

	c[0][0] = cos(phi); c[0][1] = -sin(phi);
	c[1][0] = sin(phi); c[1][1] = cos(phi);

	if (!direction) {
		c[0][1] *= -1;
		c[1][0] *= -1;
	}
}

void scale(float S, mat c) {
	unit(c);

	c[0][0] = S;
	c[1][1] = S;
}

void reflect(mat a, int width, int height, bool axis) {
	unit(a);

	if (!axis) {
		a[0][0] = -1;
		a[1][1] = 1;
		a[0][M - 1] = (float)width;
	} else {
		a[0][0] = 1;
		a[1][1] = -1;
		a[1][M - 1] = (float)height;
	}
}

void rotateCenter(float phi, int width, int height, mat R, mat T, mat T1, bool direction) {
	move(float(-width) / 2, float(-height) / 2, R);
	times(R, T, T1);
	set(T1, T);
	
	rotate(phi, R, direction);
	times(R, T, T1);
	set(T1, T);
	
	move(float(width) / 2, float(height) / 2, R);
}

void scaleCenter(float S, int width, int height, mat R, mat T, mat T1) {
	move(float(-width) / 2, float(-height) / 2, R);
	times(R, T, T1);
	set(T1, T);

	scale(S, R);
	times(R, T, T1);
	set(T1, T);

	move(float(width) / 2, float(height) / 2, R);
}

void scaleAxes(float S, float minVal, float maxVal, int width, int height, mat R, mat T, mat T1, bool direction) {
	if (!direction) {
		move(-((maxVal - minVal) / 2 + minVal), -(float)height / 2, R);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		R[0][0] = S;
		times(R, T, T1);
		set(T1, T);

		unit(R);
		move((maxVal - minVal) / 2 + minVal, (float)height / 2, R);
	} else {
		move(-(float)width / 2, -((maxVal - minVal) / 2 + minVal), R);
		times(R, T, T1);
		set(T1, T);

		unit(R);
		R[1][1] = S;
		times(R, T, T1);
		set(T1, T);
		
		move((float)width / 2, (maxVal - minVal) / 2 + minVal, R);
	}
}

void showNorm(float minYVal, float maxYVal, mat R, mat T, mat T1) {
	///unit(R);
	move(0, -(minYVal + maxYVal), R);
	times(R, T, T1);
	set(T1, T);
	
	unit(R);
	reflect(R, 0, 0, true);
}
