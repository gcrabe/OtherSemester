using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _3
{
    public class Point
    {
        public double _x, _y;

        public Point()
        {

        }

        public Point(double x, double y)
        {
            _x = x;
            _y = y;
        }
    }

    public class Line
    {
        public Point _start, _end;
        public string name;

        public Line(Point start, Point end)
        {
            _start = start;
            _end = end;
        }
    }
}
