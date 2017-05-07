using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Xml.Serialization;

namespace NewAdo_Task3
{
    [Serializable()]
    [XmlInclude(typeof(Line))]
    [XmlInclude(typeof(Circle))]
    [XmlInclude(typeof(Triangle))]
    [XmlInclude(typeof(Rectangle))]
    public abstract class Figure
    {
        public abstract void DrawFigure(Graphics graphics, Pen pen);
    }
}
