#pragma once
using namespace System::Collections::Generic;
value struct point
{
	float x, y;
};
value struct line
{
	point start, end;
	System::String^ name;
};
#define M 3
typedef float vec[M];
typedef float mat[M][M];

extern mat T;

void times(mat a, mat b, mat c);
void timesMatVec(mat a, vec b, vec c);
void set(mat a, mat b);
void point2vec(point a, vec b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec c);
void unit(mat a);
void move(float Tx, float Ty, mat c);
//If sense=false then along hour-hand
//If sense=true then against hour-hand
void Rotate(float phi, mat c, bool sense);
void Zoom(float S, mat c);
void OriginalState(mat a,mat b,mat c);
//If coordinateAxis=false, then relatively Ox
//If coordinateAxis=true, then relatively Oy
void Representation(mat a,int width, int height, bool coordinateAxis);
//If sense=false then along hour-hand
//If sense=true then against hour-hand
void RotateAboutCentre(float phi, int width, int height, mat R, mat T, mat T1, bool sense);
void ZoomAboutCentre(float S, int width, int height, mat R, mat T, mat T1);
//If sense=false then zoom to Ox
//If sense=true then zoom to Oy
void ZoomAboutAxes(float S,float minVal,float maxVal, int width, int height, mat R, mat T, mat T1, bool sense);
void ShowNorm(float minYVal,float maxYVal,mat R,mat T,mat T1);
