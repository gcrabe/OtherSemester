using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.Xml.Linq;

namespace NewAdo_Task2
{
    class XmlParser
    {
        private XmlDocument document;

        public XmlParser()
        {
            document = new XmlDocument();
        }

        public void LoadDocument(string fileName)
        {
            try
            {
                document.Load(fileName);
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        }

        public void PrintDocument()
        {
            XDocument doc = XDocument.Load(document.CreateNavigator().ReadSubtree());

            foreach (XElement element in doc.Root.Elements())
            {
                Console.WriteLine(element.Name);

                foreach (XElement childElement in element.Elements())
                    Console.WriteLine("-" + childElement.Name + " : " + childElement.Value);
            }
        }

        public void LoadSchema(string fileName)
        {
            document.Schemas.Add(null, fileName);
        }

        public bool IsValid()
        {
            bool res = true;

            document.Validate((o, e) => 
            {
                Console.WriteLine(e.Message);
                res = false;
            });

            return res;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            XmlParser parser = new XmlParser();

            parser.LoadDocument("xmlfile.xml");
            parser.LoadSchema("xsdfile.xsd");

            if (parser.IsValid())
                parser.PrintDocument();
        }
    }
}
