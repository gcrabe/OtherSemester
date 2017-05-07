using System;
using System.Xml;
using System.Xml.Linq;

namespace Task2
{
    class Program
    {
        static string xmlFile = "XML.xml";
        static string xsdFile = "XSD.xsd";
        
        static void Main()
        {
            XmlDocument doc = new XmlDocument();
            doc.Load(xmlFile);
            
            if (IsValidXml(doc))
                PrintXmlDoc(xmlFile);
        }

        static bool IsValidXml(XmlDocument doc)
        {
            bool flag = true;
            
            doc.Schemas.Add(null, xsdFile);
            doc.Validate((o, e) => 
            {
                Console.WriteLine(e.Message); 
                flag = false; 
            });

            return flag;
        }
        
        static void PrintXmlDoc(string xmlFile)
        {
            string fileName = xmlFile;
            XDocument doc = XDocument.Load(fileName);
            foreach (XElement el in doc.Root.Elements())
            {
                //Выводим имя элемента
                Console.WriteLine("{0}", el.Name);
                //выводим в цикле названия всех дочерних элементов и их значения
                foreach (XElement element in el.Elements())
                    Console.WriteLine("    {0}: {1}", element.Name, element.Value);
            }
        }
    }
}
