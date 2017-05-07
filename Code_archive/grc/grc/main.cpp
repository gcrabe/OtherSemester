#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <time.h>

#include <omp.h>

const double EPS = 1e-8;
const double DELTA = 10.0;

const int NUM_AREAS = 1000;
const int ITER_MAX = (int) 1e6;
const int MAXN = 20;
const int NDIM = 6;

const double ALPHA = 1.0;
const double BETA = 0.5;
const double GAMMA = 2.0;

double tin[MAXN], tout[MAXN];
double v[MAXN], s[MAXN];

FILE *foutput;

struct Point
{
	double x[NDIM];

	Point()
	{
		for (int i = 0; i < NDIM; i++)
			x[i] = 0.0;
	}

	Point(double* d)
	{
		for (int i = 0; i < NDIM; i++)
			x[i] = d[i];
	}

	void operator += (const Point &p)
	{
		for (int i = 0; i < NDIM; i++)
			x[i] += p.x[i];
	}

	Point operator / (double d)
	{
		Point res;

		for (int i = 0; i < NDIM; i++)
			res.x[i] = x[i] / d;

		return res;
	}

	friend Point operator * (Point p, double d)
	{
		Point res;

		for (int i = 0; i < NDIM; i++)
			res.x[i] = p.x[i] * d;

		return res;
	}

	friend Point operator - (Point p, Point q)
	{
		Point res;

		for (int i = 0; i < NDIM; i++)
			res.x[i] = p.x[i] - q.x[i];

		return res;
	}

	friend Point operator + (Point p, Point q)
	{
		Point res;

		for (int i = 0; i < NDIM; i++)
			res.x[i] = p.x[i] + q.x[i];

		return res;
	}

	friend double Distantion(Point p, Point q)
	{
		double sum = 0.0;

		for (int i = 0; i < NDIM; i++)
			sum += (p.x[i] - q.x[i]) * (p.x[i] - q.x[i]);

		return sqrt(sum);
	}

	void Print()
	{
		for (int i = 0; i < NDIM; i++)
			fprintf(foutput, "x [ %d ] = %.10lf\n", i, x[i]);

		fprintf(foutput, "\n");
	}
};

double function(Point p)
{
	double res = 0;

	for (int i = 0; i < MAXN; i++)
		res += (tout[i] - ((p.x[0] * tin[i] - 1.0) * (p.x[1] * pow(v[i], 0.56) + p.x[2] * pow(v[i], 0.8)) + p.x[3] / (s[i] * s[i]) + p.x[4] * tin[i] + p.x[5]))
				* (tout[i] - ((p.x[0] * tin[i] - 1.0) * (p.x[1] * pow(v[i], 0.56) + p.x[2] * pow(v[i], 0.8)) + p.x[3] / (s[i] * s[i]) + p.x[4] * tin[i] + p.x[5]));

	return res;
}

class Simplex
{
public:
	Point v[NDIM + 1];

	Simplex()
	{
		for (int i = 0; i <= NDIM; i++)
			v[i] = Point();
	}

	Simplex(Point *p)
	{
		for (int i = 0; i <= NDIM; i++)
			v[i] = p[i];
	}

	void Print()
	{
		for (int i = 0; i <= NDIM; i++)
			v[i].Print();

		printf("\n");
	}
};

void QSort(Simplex *s, double *f, int first, int last)
{
	int i = first, j = last;
	double x = f[(first + last) / 2];
	double temp;
	Point ptemp;

	do
	{
		while (f[i] < x) i++;
		while (f[j] > x) j--;

		if (i <= j)
		{
			if (f[i] > f[j])
			{
				temp = f[i];
				f[i] = f[j];
				f[j] = temp;

				ptemp = s->v[i];
				s->v[i] = s->v[j];
				s->v[j] = ptemp;
			}

			i++;
			j--;
		}
	} while (i <= j);

	if (i < last)
		QSort(s, f, i, last);
	if (first < j)
		QSort(s, f, first, j);
}

void SimplexSort(Simplex *s, double *f)
{
	QSort(s, f, 0, NDIM);
}

bool nmQuitCase(Simplex *s)
{
	Point center;

	for (int i = 0; i <= NDIM; i++)
		center += s->v[i];

	center = center / (double)(NDIM + 1);

	for (int i = 0; i <= NDIM; i++)
	{
		double dist = Distantion(s->v[i], center);
		if (dist > EPS)
			return false;
	}

	return true;
}

double NelderMeadAlgorithm(Simplex* smpl, Point &xres)
{
	double f[NDIM + 1];

	Point 	xh, xg, xl, xr, xe, xs;
	double 	fh, fg, fl, fr, fe, fs;

	Point tempV;
	double tempD;

	for (int i = 0; i <= NDIM; i++)
		f[i] = function(smpl->v[i]);

	int iter = 0;

	while (!nmQuitCase(smpl))
	{
		bool flag;
		Point xc;

		if (iter > ITER_MAX)
			break;

		iter++;

		SimplexSort(smpl, f);

		xh = smpl->v[NDIM];		fh = f[NDIM];
		xg = smpl->v[NDIM - 1];	fg = f[NDIM - 1];
		xl = smpl->v[0];		fl = f[0];

		for (int i = 0; i < NDIM; i++)
			xc += smpl->v[i];

		xc = xc / (double)NDIM;

		xr = xc * (1 + ALPHA) - xh * ALPHA;
		fr = function(xr);

		if (fr <= fl)
		{
			xe = xc * (1 - GAMMA) + xr * GAMMA;
			fe = function(xe);

			if (fe < fl)
			{
				smpl->v[NDIM] = xe;
				f[NDIM] = fe;
			}
			else
			{
				smpl->v[NDIM] = xr;
				f[NDIM] = fr;
			}
		}

		if (fl < fr && fr <= fg)
		{
			smpl->v[NDIM] = xr;
			f[NDIM] = fr;
		}

		flag = false;

		if (fh >= fr && fr > fg)
		{
			flag = true;

			tempD = fh;
			tempV = xh;

			smpl->v[NDIM] = xr;
			f[NDIM] = fr;

			xr = tempV;
			fr = tempD;
		}

		if (fr > fh)
			flag = true;

		if (flag)
		{
			xs = xh * BETA + xc * (1 - BETA);
			fs = function(xs);

			if (fs < fh)
			{
				tempD = fh;
				tempV = xh;

				smpl->v[NDIM] = xs;
				f[NDIM] = fs;

				xs = tempV;
				fs = tempD;
			}
			else
			{
				for (int i = 0; i <= NDIM; i++)
					smpl->v[i] = xl + (smpl->v[i] - xl) / 2.0;
			}
		}
	}

	xres = xl;

	return fl;
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	FILE *finput = fopen("table.txt", "rt");
	foutput = fopen("testout.txt", "wt");

	double ans = DBL_MAX;
	Point ptans, ptcur;

	for (int i = 0; i < MAXN; i++)
		fscanf(finput, "%lf %lf %lf %lf", &v[i], &tin[i], &s[i], &tout[i]);

	double start = clock();

	Simplex* smplarr[NUM_AREAS];

	for (int idSmpl = 0; idSmpl < NUM_AREAS; idSmpl++)
	{
		Point pts[NDIM + 1];
		double xval[NDIM];

		for (int i = 0; i < NDIM; i++)
			xval[i] = (double)(rand() % 10) * pow(-1.0, rand() % 2) + DELTA * (double)(rand() % 10);

		for (int idVertex = 0; idVertex <= NDIM; idVertex++)
		{
			if (idVertex < NDIM)
				xval[idVertex] += 1.0;

			pts[idVertex] = Point(xval);

			if (idVertex < NDIM)
				xval[idVertex] -= 1.0;
		}

		smplarr[idSmpl] = new Simplex(pts);
	}

	double res[NUM_AREAS];
	int idcalc;

#pragma omp parallel for private(idcalc, ptcur) shared(res, smplarr, tin, tout, v, s) schedule(dynamic)
	for (idcalc = 0; idcalc < NUM_AREAS; idcalc++)
	{
		res[idcalc] = NelderMeadAlgorithm(smplarr[idcalc], ptcur);

		if (res[idcalc] + EPS < ans)
		{
			ans = res[idcalc];
			ptans = ptcur;
		}
	}

	fprintf(foutput, "%.2lf\n", (clock() - start) / CLOCKS_PER_SEC);
	fprintf(foutput, "%.20lf\n", ans);
	ptans.Print();
	
	return 0;
}
