using System;
using System.Drawing;

namespace Task3
{
    [Serializable]
    public class Triangle : Figure
    {
        Point a, b, c;

        public Triangle(Point a, Point b, Point c)
        {
            this.a = a;
            this.b = b;
            this.c = c;
        }
        public Triangle() { }

        public Point FirstPoint
        {
            get
            {
                return a;
            }

            set
            {
                a = value;
            }
        }

        public Point SecondPoint
        {
            get
            {
                return b;
            }

            set
            {
                b = value;
            }
        }

        public Point ThirdPoint
        {
            get
            {
                return c;
            }

            set
            {
                c = value;
            }
        }

        public override void draw(Graphics graphics)
        {
            Point[] points = {a, b, c};
            graphics.DrawPolygon(new Pen(Color.Purple), points);
        }
    }
}
