value struct point {
	double x, y;
};

value struct line {
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

void rotate(double phi, mat c, bool direction);
void scale(double S, mat c);

void reflect(mat a, int width, int height, bool axis);

void rotateCenter(double phi, int width, int height, mat R, mat T, mat T1,bool direction);
void scaleCenter(double S, int width, int height, mat R, mat T, mat T1);

void scaleAxes(double S, double Wcx, double Wcy, mat R, mat T, mat T1, bool direction);
void scaleAxesDr(double S, double minVal, double maxVal, int width, int height, mat R, mat T, mat T1, bool direction);

void showNorm(double minYVal, double maxYVal, mat R, mat T, mat T1);

void originalState(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy, mat a, mat b, mat c);

void frame(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy, mat T);

bool Clip(point &A, point &B, point Pmin, point Pmax);

void scaleResize(double S, int Wcx, int Wcy, mat R, mat T, mat T1, bool sense);

point ConvertPoint(mat T, point a);
