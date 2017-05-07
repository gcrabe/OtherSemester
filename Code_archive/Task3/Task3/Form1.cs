using System;
using System.Collections.Generic;
using System.Drawing;
using System.IO;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Serialization;

namespace Task3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        List<Figure> ListFigures = new List<Figure>();

        private void Form1_Load(object sender, EventArgs e)
        {
            this.XMLDeserialize("figures.xml");
            this.BinarySerialize();
        }

        public void XMLDeserialize(string fileName)
        {
            XmlSerializer read = new XmlSerializer(typeof(List<Figure>));
            XmlReader reader = XmlReader.Create(new FileStream(fileName, FileMode.Open));
            ListFigures = (List<Figure>)read.Deserialize(reader);
            MessageBox.Show("Объекты десериализованы из XML файла");
        }

        public void BinarySerialize()
        {
            BinaryFormatter formatter = new BinaryFormatter();

            using (FileStream fs = new FileStream("figures.dat", FileMode.OpenOrCreate))
            {
                formatter.Serialize(fs, ListFigures);
                MessageBox.Show("Объекты бинарно сериализованы");
            }
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            this.Refresh();
        }

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics gr = e.Graphics;
            gr.Clear(Color.White);
            foreach (var figure in ListFigures)
            {
                figure.draw(gr);
            }
        }
    }
}
