using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Xml;
using System.Xml.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace NewAdo_Task3
{
    public partial class Form1 : Form
    {
        private static  List<Figure> figures;
        private string inputFile;
        private string outputFile = "file.dat";

        public Form1()
        {
            InitializeComponent();
        }

        public static void DeserializeFromXML(string fileName)
        {
            XmlSerializer serializer = new XmlSerializer(typeof(List<Figure>));
            FileStream stream;
            XmlReader reader;

            try
            {
                stream = new FileStream(fileName, FileMode.Open);
                reader = XmlReader.Create(stream);

                figures = (List<Figure>)serializer.Deserialize(reader);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        public static void SerializeToBin(string fileName)
        {
            BinaryFormatter formatter = new BinaryFormatter();
            FileStream stream;

            try
            {
                stream = new FileStream(fileName, FileMode.OpenOrCreate);
                formatter.Serialize(stream, figures);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                inputFile = openFileDialog1.FileName;
            }

            if (Path.GetExtension(inputFile) == ".xml")
            {
                DeserializeFromXML(inputFile);
                SerializeToBin(outputFile);

                button1.Visible = label1.Visible = false;
            }
            else
            {
                label1.Text = "Incorrect extension. Choose .xml";
            }
        }
    }
}
