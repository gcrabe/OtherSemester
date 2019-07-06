#pragma once
//#include <array>
//#include <iterator>
#include<vector>

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

//typedef float vec[M];
//typedef float mat[M][M];
//typedef std::tr1::array<float, M> vec;
//typedef std::tr1::array<vec, M> mat;
typedef std::vector<std::vector<float>> mat;
typedef std::vector<float> vec;
extern mat T;
//#define mat std::vector<std::vector<float>>
//#define vec std::vector<float>
//extern std::vector<std::vector<float>> T(M,std::vector<float>(M));


void times(mat a, mat b, mat& c);

void timesMatVec(mat a, vec b, vec& c);

void set(mat a, mat& b);

void point2vec(point a, vec& b);

void vec2point(vec a, point &b);

void makeHomogenVec(float x, float y, vec& c);

void unit(mat& a);

void move(float Tx, float Ty, mat& c);

//If sense=false then along hour-hand
//If sense=true then against hour-hand
void Rotate(float phi, mat& c, bool sense);

void Zoom(float S, mat& c);

void OriginalState(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy,mat& a,mat& b,mat& c);

//If coordinateAxis=false, then relatively Oy
//If coordinateAxis=true, then relatively Ox
void Representation(mat& a, bool coordinateAxis);

//If coordinateAxis=false, then relatively Oy
//If coordinateAxis=true, then relatively Ox
void RepresentationCentre(mat& a,int width, int height, bool coordinateAxis);

//If sense=false then along hour-hand
//If sense=true then against hour-hand
void RotateAboutCentre(float phi, int width, int height, mat& R, mat& T, mat& T1, bool sense);

void ZoomAboutCentre(float S, int width, int height, mat& R, mat& T, mat& T1);

//If sense=false then zoom to Ox
//If sense=true then zoom to Oy
void ZoomAboutAxes(float S,float minVal,float maxVal, int width, int height, mat& R, mat& T, mat& T1, bool sense);

void ShowNorm(float minYVal,float maxYVal,mat& R,mat& T,mat& T1);

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat& T);
bool Clip(point &A, point &B, point Pmin, point Pmax);
void ZoomResize(float S, int Wcx, int Wcy, mat& R, mat& T, mat& T1, bool sense);
point ConvertPoint(mat& T, point a);