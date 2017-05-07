using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    class Clip
    {
        double scalar(ref Point A, ref Point B)
        {
            return A._x * B._x + A._y * B._y;
        }

        public bool clip(ref Point A, ref Point B, Point Pmin, Point Pmax)
        {
            float tmin = 0, tmax = 1;
            int pi = 0, qi = 0;
            for (int i = 1; i < 5; i++)
            {
                Point p = new Point();
                p._x = B._x - A._x;
                p._y = B._y - A._y;
                Point N = new Point();
                N._x = 0;
                N._y = 0;
                Point F = new Point();

                switch (i)
                {
                    case 1:
                        N._x = 1;
                        F = Pmin;
                        break;
                    case 2:
                        N._y = -1;
                        F._x = Pmin._x;
                        F._y = Pmax._y;
                        break;
                    case 3:
                        N._x = -1;
                        F = Pmax;
                        break;
                    case 4:
                        N._y = 1;
                        F._x = Pmax._x;
                        F._y = Pmin._y;
                        break;
                }
                pi = (int)scalar(ref p, ref N);
                Point sub = new Point();
                sub._x = A._x - F._x;
                sub._y = A._y - F._y;
                qi = (int)scalar(ref sub, ref N);

                if (pi == 0)
                {
                    if (qi < 0)
                        return false;
                }
                else
                {
                    if (pi > 0)
                        tmin = Math.Max(tmin, -(float)qi / pi);
                    else
                        tmax = Math.Min(tmax, -(float)qi / pi);
                    if (tmin > tmax)
                        return false;
                }
            }

            Point An = new Point();
            Point Bn = new Point();
            An._x = A._x + (B._x - A._x) * tmin;
            An._y = A._y + (B._y - A._y) * tmin;
            Bn._x = A._x + (B._x - A._x) * tmax;
            Bn._y = A._y + (B._y - A._y) * tmax;
            A = An;
            B = Bn;
            return true;
        }
    }
}
