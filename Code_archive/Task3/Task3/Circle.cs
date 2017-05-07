using System;
using System.Drawing;
using System.Xml.Serialization;

namespace Task3
{
    [Serializable]
    [XmlType("Circle")]
    public class Circle : Figure
    {
        Point centr;
        float radius;

        public Circle(Point centr, float radius)
        {
            this.centr = centr;
            this.radius = radius;
        }

        public Circle() { }

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

        public Point Center
        {
            get
            {
                return centr;
            }

            set
            {
                centr = value;
            }
        }

        public override void draw(Graphics graphics)
        {
            graphics.DrawEllipse(new Pen(Color.DarkGoldenrod), centr.X, centr.Y, radius, radius);
        }
    }
}
