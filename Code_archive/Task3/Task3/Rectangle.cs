using System;
using System.Drawing;

namespace Task3
{
    [Serializable]
    public class Rectangle : Figure
    {
        Point leftUpPoint;
        float width, height;

        public Rectangle(Point a, float width, float height)
        {
            this.leftUpPoint = a;
            this.width = width;
            this.height = height;
        }

        public Rectangle() { }

        public Point LeftUpPoint
        {
            get
            {
                return leftUpPoint;
            }

            set
            {
                leftUpPoint = value;
            }
        }

        public float Width
        {
            get
            {
                return width;
            }

            set
            {
                width = value;
            }
        }

        public float Height
        {
            get
            {
                return height;
            }

            set
            {
                height = value;
            }
        }

        public override void draw(Graphics graphics)
        {
            graphics.DrawRectangle(new Pen(Color.Coral), leftUpPoint.X, leftUpPoint.Y, width, height);
        }
    }
}
