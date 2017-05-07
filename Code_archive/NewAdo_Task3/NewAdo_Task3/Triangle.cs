using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace NewAdo_Task3
{
    [Serializable]
    public class Triangle : Figure
    {
        private Point first;
        private Point second;
        private Point third;

        public Triangle()
        { }

        public Triangle(Point fs, Point sc, Point td)
        {
            first = fs;
            second = sc;
            third = td;
        }

        public Point First
        {
            get
            {
                return first;
            }
            set
            {
                first = value;
            }
        }

        public Point Second
        {
            get
            {
                return second;
            }
            set
            {
                second = value;
            }
        }

        public Point Third
        {
            get
            {
                return third;
            }
            set
            {
                third = value;
            }
        }

        public override void DrawFigure(Graphics graphics, Pen pen)
        {
            graphics.DrawPolygon(pen, new Point[] {first, second, third});
        }
    }
}
