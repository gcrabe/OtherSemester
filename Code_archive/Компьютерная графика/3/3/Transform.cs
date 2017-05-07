using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    class Transform
    {
        public int M = 3;     
        public void times(double[,] a, double[,] b, double[,] c)
        {
            for(int i = 0; i < 3; i++)
            {
                for(int j = 0; j < 3; j++)
                {
                    double scalaar = 0;
                    for(int k = 0; k < 3; k++)
                    {
                        scalaar += a[i, k] * b[k, j];
                    }
                    c[i, j] = scalaar;
                }
            }
        }
        public void timesMatVec(double[,] a, double[] b, double[] c)
        {
            for(int i = 0; i < 3; i++)
            {
                double scalaar = 0;
                for (int j = 0; j < 3; j++)
                     scalaar += a[i,j] * b[j];
                c[i] = scalaar;
            }
        }
        public void set(double[,] a, double[,] b)
        {
            for (int i = 0; i < 3; i++)
                 for (int j = 0; j < 3; j++)
                    b[i,j] = a[i,j];
        }
        public void point2vec(Point a, double[] b)
        {
            b[0] = a._x;
            b[1] = a._y;
            b[2] = 1;
        }
        public void vec2point(double[] a, Point b)
        {
            b._x = ((double)a[0]) / a[2];
            b._y = ((double)a[1]) / a[2];
        }
        public void makeHomogenVec(double x, double y, double[] c)
        {
            c[0] = x;
            c[1] = y;
            c[2] = 1;
        }           
        public void unit(double[,] a)
        {
            for (int i = 0; i < 3; i++)
            {
                 for (int j = 0; j < 3; j++)
                 { 
                     if (i == j) a[i,j] = 1;
                     else a[i,j] = 0;                     
                 }
            }
        }
        public void move(double tx, double ty, double[,] c)
        {
            unit(c);
            c[0, 2] = tx;
            c[1, 2] = ty;
        }
        public void rotate(double phi, double[,] c)
        {
            unit(c);
            c[0, 0] = Math.Cos(phi);
            c[0, 1] = -Math.Sin(phi);
            c[1, 0] = Math.Sin(phi);
            c[1, 1] = Math.Cos(phi);
        }
        public void scale(double S, double[,] c)
        {
            unit(c);
            c[0, 0] = S;
            c[1, 1] = S;
        }
        public void mirror(string axis, double[,] c)
        {
            unit(c);            
            if (axis == "horizontally")
            {
                c[1, 1] = -1;
            }
            else if (axis == "vertically")
            {
                c[0, 0] = -1;
            }
            else unit(c);
        }
        public void rotateAbout(double phi, double x, double y, double[,] c)
        {
            unit(c);
            c[0,0] = Math.Cos(phi); c[0,1] = -Math.Sin(phi);
            c[1,0] = Math.Sin(phi); c[1,1] = Math.Cos(phi);
            c[0,M - 1] = -x * (Math.Cos(phi) - 1) + y * Math.Sin(phi);
            c[1,M - 1] = -y * (Math.Cos(phi) - 1) - x * Math.Sin(phi);
        }
        public void resize(double Sx, double Sy, double[,] c)
        {
            unit(c);
            c[0,0] = Sx;
            c[1,1] = Sy;
        }
        public void horizontal(double Tx, double[,] c)
        {
            unit(c);
            c[0,0] = -Math.Cos(3.14); c[0,1] = Math.Sin(3.14);
            c[1,0] = Math.Sin(3.14); c[1,1] = Math.Cos(3.14);
            c[0,2] = 0;
            c[1,2] = Tx;
        }
        public void vertical(double Tx, double[,] c)
        {
            unit(c);
            c[0,0] = Math.Cos(3.14); c[0,1] = Math.Sin(3.14);
            c[1,0] = Math.Sin(3.14); c[1,1] = -Math.Cos(3.14);
            c[0,2] = Tx;
            c[1,2] = 0;
        }
        public void mirrorReflection(double[,] R, double[,] MatrixForMirrorReflection, double[,] Transformation, double height)
        {
            move(0, height, MatrixForMirrorReflection);
            unit(R);
            reflectionHorizontal(Transformation);
            times(MatrixForMirrorReflection, Transformation, R);
        }
        public void reflectionHorizontal(double[,] c)
        {
            unit(c);
            c[1, 1] = -1;
        }
        void stretch(double Sx, double Sy, double[,] c)
        {
            unit(c);
            c[0,0] = Sx;
            c[1,1] = Sy;
        }
        void mirror(bool axis, double[,] c)
        {
            unit(c);            
            if (axis == true)
            {
                c[1, 1] = -1;
            }
            else c[0, 0] = -1;
        }
        public void frame(double Vx, double Vy, double Vcx, double Vcy, double Wx, double Wy, double Wcx, double Wcy, double[,] c, double H)
        {
            /*double[,] R = new double[3, 3];
            double[,] T1 = new double[3, 3];
            double[,] MatrixForMirrorReflection = new double[3, 3];
            double[,] Transformation = new double[3, 3];
            double[,] intermediateMatrix = new double[3, 3];

            unit(R);
            unit(T1);
            move(-Vcx, -Vcy, R);                                       //Лехин вариант
            unit(T1);
            c[0, 0] = Wx / Vx;
            c[1, 1] = Wy / Vy;
            times(T1, R, R);
            mirrorReflection(intermediateMatrix, MatrixForMirrorReflection, Transformation, H);
            times(intermediateMatrix, R, R);
            move(Wcx, Wcy, intermediateMatrix);
            times(intermediateMatrix, R, c);*/

            unit(c);
            double[,] R = new double[3, 3];
            double[,] T1 = new double[3, 3];
            move(-Vcx, -Vcy, R);
            times(R, c, T1);
            set(T1, c);

            double xs = Wx / Vx;
            double ys = Wy / Vy;            

            stretch(xs, ys, R);
            times(R, c, T1);
            set(T1, c);

            mirror(true, R);
            times(R, c, T1);
            set(T1, c);

            move(Wcx, Wcy, R);
            times(R, c, T1);
            set(T1, c);

        }
    }
}
