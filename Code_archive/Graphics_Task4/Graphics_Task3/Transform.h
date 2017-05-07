value struct t_point
{
	float x;
	float y;
};

value struct t_line
{
	t_point start;
	t_point end;
	System::String ^name;
};

#define MDIM 3

typedef float t_vector[MDIM];
typedef float t_matrix[MDIM][MDIM];

extern t_matrix ETransform;

void t_times_matrix_to_matrix(t_matrix a, t_matrix b, t_matrix c);
void t_times_matrix_to_vector(t_matrix a, t_vector b, t_vector c);

void t_set(t_matrix a, t_matrix b);

void t_point_to_vector(t_point a, t_vector b);
void t_vector_to_point(t_vector a, t_point &b);

void t_make_uniform_vector(float x, float y, t_vector c);

void t_unit(t_matrix a);

void t_move(float Tx, float Ty, t_matrix c);
void t_rotate(float phi, t_matrix c);
void t_scale(float Sz, t_matrix c);
void t_scale_xy(float Sx, float Sy, t_matrix c);

void t_reflection_horizontal(t_matrix c);
void t_reflection_vertical(t_matrix c);

void t_frame(float Vx, float Vy, float Vcx, float Vcy,
			 float Wx, float Wy, float Wcx, float Wcy, t_matrix c);