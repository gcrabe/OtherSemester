using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace NewAdo_Task3
{
    [Serializable]
    public class Rectangle : Figure
    {
        private Point angle;
        private float height;
        private float width;

        public Rectangle()
        { }

        public Rectangle(Point angle, float height, float width)
        {
            this.angle = angle;
            this.height = height;
            this.width = width;
        }

        public Point Angle
        {
            get
            {
                return angle;
            }
            set
            {
                angle = value;
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

        public override void DrawFigure(Graphics graphics, Pen pen)
        {
            graphics.DrawRectangle(pen, angle.X, angle.Y, width, height);
        }
    }
}
