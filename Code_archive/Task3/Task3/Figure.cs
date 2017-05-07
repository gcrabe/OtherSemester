using System;
using System.Drawing;
using System.Xml.Serialization;

namespace Task3
{
    [Serializable()]
    [XmlInclude(typeof(Circle))]
    [XmlInclude(typeof(Rectangle))]
    [XmlInclude(typeof(Line))]
    [XmlInclude(typeof(Triangle))]

    public abstract class Figure
    {
        public abstract void draw(Graphics graphics);
    }
}
