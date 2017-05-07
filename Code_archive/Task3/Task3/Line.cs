using System;
using System.Drawing;

namespace Task3
{
    [Serializable]
    public class Line : Figure
    {
        private Point a, b;

        public Line(Point a, Point b)
        {
            this.a = a;
            this.b = b;
        }

        public Line() { }

        public Point BeginPoint
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

        public Point EndPoint
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

        public override void draw(Graphics graphics)
        {
            graphics.DrawLine(new Pen(Color.SeaGreen), a, b);
        }
    }
}
