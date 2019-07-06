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

void rotate(float phi, mat c, bool direction);
void scale(float S, mat c);

void reflect(mat a, int width, int height, bool axis);

void rotateCenter(float phi, int width, int height, mat R, mat T, mat T1,bool direction);
void scaleCenter(float S, int width, int height, mat R, mat T, mat T1);

void scaleAxes(float S, float minVal, float maxVal, int width, int height, mat R, mat T, mat T1, bool direction);

void showNorm(float minYVal, float maxYVal, mat R, mat T, mat T1);
