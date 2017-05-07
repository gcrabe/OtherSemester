using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Schema;
using System.IO;

namespace AdoTask2
{
    class Program
    {
        static void Main(string[] args)
        {
            XmlDocument document = new XmlDocument();
            document.PreserveWhitespace = true;

            try
            {
                document.Load("C:\\THE_CODE\\AdoTask2\\AdoTask2\\document.xml");
            }
            catch (FileNotFoundException)
            {
                Console.WriteLine("!");
            }
        }
    }
}
