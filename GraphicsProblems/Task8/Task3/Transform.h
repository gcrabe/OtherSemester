#include <array>
#include <vector>
#include <stack>

value struct point {
	float x;
	float y;
};

value struct line {
	point start;
	point end;
	System::String ^name;
};

#define M 3
//typedef float vec[M];
//typedef float mat[M][M];
typedef std::tr1::array<float, M> vec;
typedef std::tr1::array<vec, M> mat;

extern mat T;
extern mat backupT;
extern std::vector<mat> matrices;

typedef System::Collections::Generic::List<point> polygon;

typedef System::Collections::Generic::List<int> clr;
typedef System::Collections::Generic::List<point>s;
typedef System::Collections::Generic::List<float>ael;

void times(mat a, mat b, mat& c);
void timesMatVec(mat a, vec b, vec& c);

void set(mat a, mat& b);

void point2vec(point a, vec& b);
void vec2point(vec a, point &b);

void makeHomogenVec(float x, float y, vec& c);
void unit(mat& a);

void move(float Tx, float Ty, mat& c);

void rotate(float phi, mat& c, bool direction);
void scale(float S, mat& c);

void originalState(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy,mat& a,mat& b,mat& c);

void reflectDefault(mat& a, bool coordinateAxis);
void reflect(mat& a,int width, int height, bool coordinateAxis);

void rotateCenter(float phi, int width, int height, mat& R, mat& T, mat& T1, bool direction);
void scaleCenter(float S, int width, int height, mat& R, mat& T, mat& T1);
void scaleAxes(float S,float minVal,float maxVal, int width, int height, mat& R, mat& T, mat& T1, bool direction);

void showNorm(float minYVal,float maxYVal,mat& R,mat& T,mat& T1);

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat& T);
void scaleResize(float S, int Wcx, int Wcy, mat& R, mat& T, mat& T1, bool direction);

point ConvertPoint(mat& T, point a);
void frameIcon(float Vcx, float Vcy, float Vx, float Vy, float Wcx, float Wcy, float Wx, float Wy, mat &T);

polygon^ Pclip (polygon^ p, point Pmin, point Pmax);
polygon^ ConvertP(polygon^ P, mat T);

void Pfill (polygon^ P, System::Drawing::Bitmap^ image, System::Drawing::Color C);
void Sort(polygon^ P);
