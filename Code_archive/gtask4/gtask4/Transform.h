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

//If route=false then along hour-hand
//If route=true then against hour-hand
void Rotate(float phi, mat c, bool route);

void Zoom(float S, mat c);

void OriginalState(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy,mat a,mat b,mat c);

//If axis=false, then relatively Oy
//If axis=true, then relatively Ox
void Representation(mat a, bool axis);

//If axis=false, then relatively Oy
//If axis=true, then relatively Ox
void RepresentationCenter(mat a,int width, int height, bool axis);

//If route=false then along hour-hand
//If route=true then against hour-hand
void RotateAboutCenter(float phi, int width, int height, mat R, mat T, mat T1, bool route);

void ZoomAboutCenter(float S, int width, int height, mat R, mat T, mat T1);

//If route=false then zoom to Ox
//If route=true then zoom to Oy
void ZoomAboutAxes(float S,float minVal,float maxVal, int width, int height, mat R, mat T, mat T1, bool route);

void ShowNorm(float minYVal,float maxYVal,mat R,mat T,mat T1);

void frame(float Vx, float Vy, float Vcx, float Vcy, float Wx, float Wy, float Wcx, float Wcy, mat T);
/*
bool Clip(point &A, point &B, point Pmin, point Pmax);
*/
void ZoomResize(float S, int Wcx, int Wcy, mat R, mat T, mat T1, bool route);


