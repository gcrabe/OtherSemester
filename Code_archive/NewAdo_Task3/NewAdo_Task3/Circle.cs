using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace NewAdo_Task3
{
    [Serializable]
    public class Circle : Figure
    {
        private Point center;
        private float radius;

        public Circle()
        { }

        public Circle(Point center, float radius)
        {
            this.center = center;
            this.radius = radius;
        }

        public Point Center
        {
            get
            {
                return center;
            }
            set
            {
                center = value;
            }
        }

        public float Radius
        {
            get
            {
                return radius;
            }
            set
            {
                radius = value;
            }
        }

        public override void DrawFigure(Graphics graphics, Pen pen)
        {
            graphics.DrawEllipse(pen, center.X, center.Y, radius, radius);
        }
    }
}
