#include <array>
#include <vector>

value struct point {
	float x, y;
	point (float _x, float _y): x(_x), y(_y) {}
};

value struct point3D {
	float x, y, z;
	point3D (float _x, float _y, float _z): x(_x), y(_y), z(_z) {}
};

value struct line {
	point start, end;
	System::String^ name;
};
#define M 3
#define N 4

typedef float vec[M];
typedef float vec3D[N];

typedef  float mat[M][M];
typedef float mat3D[N][N];

typedef System::Collections::Generic::List<point> polygon;
typedef System::Collections::Generic::List<point3D> polygon3D;

extern mat3D T;

void times(mat a, mat b, mat &R);
void timesMatVec(mat a, vec b, vec &R);
void set(mat a, mat &b);
void point2vec(point a, vec &b);
void vec2point(vec a, point &b);
void makeHomogenVec(float x, float y, vec &R);
void unit(mat &a);
void move(float Tx, float Ty, mat &R);
void rotate(float phi, mat &R);
void scale(float x, float y, mat &R);
void reflectHoriz(mat &R); 
void reflectVert(mat &R);
void start(float Tx, mat &R);
void frame (float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat &R);

//3D

void times3D (mat3D a, mat3D b, mat3D &R);
void timesMatVec3D (mat3D a, vec3D b, vec3D &R);
void set3D (mat3D a, mat3D &b);
void point2vec3D (point3D a, vec3D &b);
void vec2point3D (vec3D a, point3D &b);
void makeHomogenVec3D (float x, float y, float z, vec3D &R);
void unit3D (mat3D &a);
void move3D (float Tx, float Ty, float Tz, mat3D &R);
void rotate3D (point3D n, float phi, mat3D &R);
void scale3D (float Sx, float Sy, float Sz, mat3D &R);
void LookAt (point3D eye, point3D center, point3D up, mat3D &R);
void setTo2D (point3D a, point &b);
void Perspective (float fovy, float aspect, float near, float far, mat3D &R);
void Frustrum (float Vx, float Vy, float near, float far, mat3D &R);
void Ortho (float Vx, float Vy, float near, float far, mat3D &R);


