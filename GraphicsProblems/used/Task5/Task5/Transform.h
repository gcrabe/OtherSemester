#pragma once

value struct point
{
	double x, y;
};

value struct line
{
	point start, end;
	System::String^ name;
};

#define M 3

typedef double vec[M];

typedef double mat[M][M];

extern mat T;
extern mat T2;
extern mat TCoo;
extern mat TPoint;

void times(mat a, mat b, mat c);

void timesMatVec(mat a, vec b, vec c);

void set(mat a, mat b);

void point2vec(point a, vec b);

void vec2point(vec a, point &b);

void makeHomogenVec(double x, double y, vec c);

void unit(mat a);

void move(double Tx, double Ty, mat c);

//If sense=false then along hour-hand
//If sense=true then against hour-hand
void Rotate(double phi, mat c, bool sense);

void Zoom(double S, mat c);

void OriginalState(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy,mat a,mat b,mat c);

//If coordinateAxis=false, then relatively Oy
//If coordinateAxis=true, then relatively Ox
void Representation(mat a, bool coordinateAxis);

//If coordinateAxis=false, then relatively Oy
//If coordinateAxis=true, then relatively Ox
void RepresentationCentre(mat a,int width, int height, bool coordinateAxis);

//If sense=false then along hour-hand
//If sense=true then against hour-hand
void RotateAboutCentre(double phi, int width, int height, mat R, mat T, mat T1, bool sense);

void ZoomAboutCentre(double S, double width, double height, mat R, mat T, mat T1);

//If sense=false then zoom to Ox
//If sense=true then zoom to Oy
void ZoomAboutAxes(double S, double width, double height, mat R, mat T, mat T1, bool sense);
void ZoomAboutAxesDr(float S, float minVal, float maxVal, int width, int height, mat R, mat T, mat T1, bool sense);

void ShowNorm(double minYVal,double maxYVal,mat R,mat T,mat T1);

void frame(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy, mat T);
bool Clip(point &A, point &B, point Pmin, point Pmax);

//If sense=false then resize to Ox
//If sense=true then resize to Oy
//Wcx, Wcy are coordinates up-left cover
void ZoomResize(double S, int Wcx, int Wcy, mat R, mat T, mat T1, bool sense);
point ConvertPoint(mat T, point a);