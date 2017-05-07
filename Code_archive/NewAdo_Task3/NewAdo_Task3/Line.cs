using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace NewAdo_Task3
{
    [Serializable]
    public class Line : Figure
    {
        private Point start;
        private Point end;

        public Line()
        { }

        public Line(Point start, Point end)
        {
            this.start = start;
            this.end = end;
        }

        public Point Start
        {
            get
            {
                return start;
            }
            set
            {
                start = value;
            }
        }

        public Point End
        {
            get
            {
                return end;
            }
            set
            {
                end = value;
            }
        }

        public override void DrawFigure(Graphics graphics, Pen pen)
        {
            graphics.DrawLine(pen, start, end);
        }
    }
}
