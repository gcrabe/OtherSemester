#pragma once
#include "stdafx.h"
#include "Transform.h"
#include <math.h>

mat3D T;

void times(mat a, mat b, mat &R) {
	for(int i = 0; i < M; i++) {
		for(int j = 0; j < M; j++) {
			float skalaar = 0;
			for(int k = 0; k < M; k++)
				skalaar += a[i][k] * b[k][j];
			R[i][j] = skalaar;
		}
	}
}

void timesMatVec(mat a, vec b, vec &R) {
	for(int i = 0; i < M; i++) {
		float skalaar = 0;
		for(int j = 0; j < M; j++)
			skalaar += a[i][j] * b[j];
		R[i] = skalaar;
	}
}

void set(mat a, mat &b) {
	for(int i = 0; i < M; i++)
		for (int j = 0; j < M; j++)
			b[i][j] = a[i][j];
}

void point2vec(point a, vec &b) {
	b[0] = a.x; b[1] = a.y; b[2] = 1;
}

void vec2point(vec a, point &b) {
	b.x = ((float)a[0])/a[2];
	b.y = ((float)a[1])/a[2];
}

void makeHomogenVec(float x, float y, vec &R){
	R[0] = x; 
	R[1] = y; 
	R[2] = 1;
}

void unit(mat &a) {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move(float Tx, float Ty, mat &R) {
	unit (R);
	R[0][M-1] = Tx;
	R[1][M-1] = Ty;
}

void rotate(float phi, mat &R) {
	unit(R);
	R[0][0] = cos(phi); R[0][1] = sin(phi);
	R[1][0] = -sin(phi); R[1][1] =  cos(phi);
}

void scale(float x, float y, mat &R) { 
	unit(R);
	R[0][0] = x;
	R[1][1] = y;
}
void reflectHoriz(mat &R) {
	unit(R);
	R[1][1] = -1;
}

void reflectVert(mat &R) { 
	unit(R);
	R[0][0] = -1;
}

void start(float Tx, mat &R) {
	unit(R);
	R[1][1] =  -1;
	R[1][2] = Tx;
}

void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &R) {
	mat R1, c1;
	unit(R1);
	unit(R);
	move(-Vcx, -Vcy, R1);
	set(R1, c1);
	scale(Wx / Vx, Wy / Vy, R1);
	times(R1, c1, c1);
	reflectHoriz(R1);
	times(R1, c1, c1);
	move(Wcx, Wcy, R1);
	times(R1, c1, R);
}

//3D

void times3D (mat3D a, mat3D b, mat3D &R) {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			float skalaar = 0;
			for(int k = 0; k < N; k++)
				skalaar += a[i][k] * b[k][j];
			R[i][j] = skalaar;
		}
	}
}
void timesMatVec3D (mat3D a, vec3D b, vec3D &R) {
	float skalaar;
	for(int i = 0; i < N; i++) {
		skalaar = 0;
		R[i] = 0;
		for(int j = 0; j < N; j++) {
			skalaar = a[i][j] * b[j];
			R[i] += skalaar;
		}
	}
}

void set3D (mat3D a, mat3D &b) {
	for(int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			b[i][j] = a[i][j];
}

void point2vec3D (point3D a, vec3D &b) {
	b[0] = a.x; b[1] = a.y; b[2] = a.z; b[3] = 1;
}

void vec2point3D (vec3D a, point3D &b) {
	b.x = ((float)a[0])/a[3];
	b.y = ((float)a[1])/a[3];
	b.z = ((float)a[2])/a[3];
}

void makeHomogenVec3D (float x, float y, float z, vec3D &R) {
	R[0] = x; R[1] = y; R[2] = z; R[3] = 1;
}

void unit3D (mat3D &a) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (i == j) a[i][j] = 1;
			else a[i][j] = 0;
		}
	}
}

void move3D (float Tx, float Ty, float Tz, mat3D &R) {
	unit3D (R);
	R[0][N-1] = Tx;
	R[1][N-1] = Ty;
	R[2][N-1] = Tz;
}

void rotate3D (point3D n, float phi, mat3D &R) {
	unit3D (R);
	R[0][0] = cos(phi) + ( pow( (n.x), 2 ) * (1 - cos(phi)) );
	R[0][1] = n.x * n.y * ( 1 - cos(phi) ) - n.z * sin(phi);
	R[0][2] = n.x * n.z * ( 1 - cos(phi) ) + n.y * sin(phi);

	R[1][0] = n.x * n.y * (1 - cos(phi) ) + n.z * sin(phi);  
	R[1][1] = cos(phi) + n.y * n.y * ( 1 - cos(phi) ); 
	R[1][2] = n.y * n.z * ( 1 - cos(phi) ) - n.x * sin(phi);

	R[2][0] = n.x * n.z * ( 1 - cos(phi) ) - n.y * sin(phi);
	R[2][1] = n.y * n.z * ( 1 - cos(phi) ) + n.x * sin(phi); 
	R[2][2] = cos(phi) + n.z * n.z * ( 1 - cos(phi) );
}
void scale3D (float Sx, float Sy, float Sz, mat3D &R) {
	unit3D (R);
	R[0][0] = Sx; 
	R[1][1] = Sy;
	R[2][2] = Sz;
}

void LookAt (point3D eye, point3D center, point3D up, mat3D &R) {
	unit3D(R);
	mat3D R1;
	unit3D(R1);

	move3D (-eye.x, -eye.y, -eye.z, R1);

	point3D e1, e2, e3;
	float s_p = sqrt( pow(eye.x - center.x, 2) + 
		pow(eye.y - center.y, 2) + 
		pow(eye.z - center.z, 2));

	e3.x = (eye.x - center.x) / s_p;
	e3.y = (eye.y - center.y) / s_p;
	e3.z = (eye.z - center.z) / s_p;

	float u = sqrt(pow(up.x, 2) + pow(up.y, 2) + pow(up.z, 2) );

	e1.x = (up.y * e3.z - e3.y * up.z) / u;
	e1.y = - (up.x * e3.z - e3.x * up.z) / u;
	e1.z = (up.x * e3.y - e3.x * up.y) / u;

	e2.x = (e3.y * e1.z - e1.y * e3.z);
	e2.y = -(e3.x * e1.z - e1.x * e3.z);
	e2.z = e3.x * e1.y - e1.x * e3.y;

	mat3D R2;
	R2[0][0] = e1.x;
	R2[0][1] = e1.y; 
	R2[0][2] = e1.z;
	R2[0][3] = 0;

	R2[1][0] = e2.x; 
	R2[1][1] = e2.y; 
	R2[1][2] = e2.z; 
	R2[1][3] = 0;

	R2[2][0] = e3.x; 
	R2[2][1] = e3.y; 
	R2[2][2] = e3.z;
	R2[2][3] = 0;

	R2[3][0] = 0; 
	R2[3][1] = 0;  
	R2[3][2] = 0;  
	R2[3][3] = 1;

	times3D (R2,  R1, R);
}

void Ortho (float Vx, float Vy, float near, float far, mat3D &R) {
	unit3D(R);
	R[0][0] = 2.0 / Vx;
	R[1][1] = 2.0 / Vy;
	R[2][2] = 2.0 / (far - near);
	R[2][3] = (far + near) / (far - near);	
}
void Frustrum (float Vx, float Vy, float near, float far, mat3D &R) {
	unit3D(R);
	R[0][0] = near * 2.0 / Vx;
	R[1][1] = near * 2.0 / Vy;
	R[2][2] = (far + near) / (far - near);
	R[2][3] = (2 * far * near) / (far - near);
	R[3][2] = -1;
	R[3][3] = 0;
}
void Perspective (float fovy, float aspect, float near, float far, mat3D &R) {
	unit3D(R);
	R[0][0] = 1.0 / ( aspect * tan(fovy / 2.0) );
	R[1][1] = 1 / tan( fovy / 2.0 );
	R[2][2] = (far + near) / (far - near);
	R[2][3] = 2 * far * near / (far - near);
	R[3][2] = -1;
	R[3][3] = 0;

}
void setTo2D (point3D a, point &b) {
	b.x = a.x;
	b.y = a.y;
}

