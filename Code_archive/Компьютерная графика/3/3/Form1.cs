using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace _3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();            
        }

        List<Line> lines = new List<Line>();
        Transform tr = new Transform();
        public double[,] T = new double[3, 3];

        double left, right, top, bottom;

        double Wcx, Wcy, Wx, Wy;      
        double Vcx, Vcy, Vx, Vy;

        private bool drawNames = true;

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.Clear(Color.White);
            Pen blackPen = new Pen(Color.Black);
            blackPen.Width = 1;

            Pen rectPen = new Pen(Color.Chocolate);
            rectPen.Width = 3;

            Clip cl = new Clip();

            g.DrawRectangle(rectPen, (float)Wcx, (float)top, (float)Wx, (float)Wy);

            for (int i = 0; i < lines.Count; i++)
            {
                double[] A = new double[3];
                double[] B = new double[3];
                tr.point2vec(lines[i]._start, A);
                tr.point2vec(lines[i]._end, B);

                double[] A1 = new double[3];
                double[] B1 = new double[3];
                tr.timesMatVec(T, A, A1);
                tr.timesMatVec(T, B, B1);

                Point a = new Point();
                Point b = new Point();
                tr.vec2point(A1, a);
                tr.vec2point(B1, b);
                if (cl.clip(ref a, ref b, new Point((float)Wcx, (float)top), new Point((float)(Wx + Wcx), (float)(Wy + top))))
                {
                    g.DrawLine(blackPen, (float)a._x, (float)a._y, (float)b._x, (float)b._y);
                    if (this.drawNames)
                    {
                        g.DrawString(lines[i].name, new Font("Times New Roman", 7, FontStyle.Regular), Brushes.Green, new PointF(((float)(a._x + b._x)) / 2 - 10, (float)(a._y + b._y) / 2 + 5));
                    }
                }
            }            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            lines.Clear();
            tr.unit(T);

            left = 70;
            right = 70;
            top = 70;
            bottom = 70;

            Wcx = left;
            Wcy = this.ClientRectangle.Height - bottom;
            Wx = this.ClientRectangle.Width - left - right;
            Wy = this.ClientRectangle.Height - top - bottom;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            lines.Clear();
            tr.unit(T);
            string[] data = File.ReadAllLines(@"C:\Users\Виктор\Desktop\Компьютерная графика\3\input1.txt");        
            //string[] data = File.ReadAllLines(@"C:\Users\Виктор\Downloads\Task_4_ConmputerGraphics\Task_3_ConmputerGraphics\PICTURE.txt");

            /*double[,] R = new double[3, 3];
            double[,] T1 = new double[3, 3];                   в нижний левый угол
            tr.horizontal(this.ClientSize.Height, R);
            tr.times(R, T, T1);
            tr.set(T1, T);*/

            string[] firstLine = data[0].Split(' ');
            Vcx = double.Parse(firstLine[0]);
            Vcy = double.Parse(firstLine[1]);
            Vx = double.Parse(firstLine[2]);
            Vy = double.Parse(firstLine[3]);
            

            for (int i = 1; i < data.Length; i++)
            {
                string[] elementsOfLine = data[i].Split(' ');
                if (elementsOfLine.Count() > 1 && elementsOfLine[0] != "#")
                {
                    Line buf = new Line(new Point(double.Parse(elementsOfLine[0]), double.Parse(elementsOfLine[1])), new Point(double.Parse(elementsOfLine[2]), double.Parse(elementsOfLine[3])));
                    if(elementsOfLine.Count() == 5)
                    {
                        buf.name = elementsOfLine[4];
                    }
                    
                    lines.Add(buf);
                }
            }

            tr.frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T, this.ClientRectangle.Height);

            Refresh();
        }

        private void Form1_KeyDown(object sender, KeyEventArgs e)
        {
            double[,] R = new double[3, 3];
            double[,] T1 = new double[3, 3];

            switch(e.KeyCode)
            {
                case Keys.W:
                    tr.move(0, -1, R);
                    break;

                case Keys.S:
                    tr.move(0, 1, R);
                    break;

                case Keys.A:
                    tr.move(-1, 0, R);
                    break;

                case Keys.D:
                    tr.move(1, 0, R);
                    break;

                case Keys.E:
                    tr.rotate(0.05,R);
                    break;

                case Keys.X:
                    tr.scale(1.1, R); 
                    break;

                case Keys.Q:
                    tr.rotate(-0.05, R);
                    break;

                case Keys.Z:
                    tr.scale(1/1.1, R);
                    break;

                case Keys.T:
                    tr.move(0, -6, R);
                    break;

                case Keys.G:
                    tr.move(0, 6, R);
                    break;

                case Keys.F:
                    tr.move(-6, 0, R);
                    break;

                case Keys.H:
                    tr.move(6, 0, R);
                    break;

                case Keys.U:
                    tr.horizontal(this.ClientSize.Height, R);
                    break;

                case Keys.J:
                    tr.vertical(this.ClientSize.Width, R);
                    break;

                case Keys.R: //5
                    tr.move(-Width / 2, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.rotate(0.05, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width / 2, Height / 2, R);
                    break;

                case Keys.Y: //5
                    tr.move(-Width / 2, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.rotate(-0.05, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width / 2, Height / 2, R);
                    break;

                case Keys.C:
                    tr.move(-Width / 2, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.scale(1/1.1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width / 2, Height / 2, R);
                    break;

                case Keys.V:
                    tr.move(-Width / 2, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.scale(1.1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width / 2, Height / 2, R);
                    break;

                case Keys.I: 
                    tr.move(-Width / 2, 0, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.resize(1.1, 1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width/ 2, 0, R);
                    break;

                case Keys.O: 
                    tr.move(-Width / 2, 0, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.resize(1/1.1, 1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(Width / 2, 0, R);
                    break;

                case Keys.K: 
                    tr.move(0, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.resize(1, 1.1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(0, Height / 2, R);
                    break;

                case Keys.L: 
                    tr.move(0, -Height / 2, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.resize(1, 1/1.1, R);
                    tr.times(R, T, T1);
                    tr.set(T1, T);
                    tr.move(0, Height / 2, R);
                    break;

                case Keys.Escape:
                    tr.unit(T);
                    tr.unit(R);
                    tr.frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T, this.ClientRectangle.Height);
                    break;

                default:
                    tr.unit(R);
                    break;
            }
            tr.times(R, T, T1);
            tr.set(T1, T);
            Refresh();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            double oldWx = Wx;
            double oldWy = Wy;
            Wcy = this.ClientRectangle.Height - bottom;
            Wx = this.ClientRectangle.Width - left - right;
            Wy = this.ClientRectangle.Height - top - bottom;
            tr.frame(Vx, Vy, Vcx, Vcy, Wx, Wy, Wcx, Wcy, T, this.ClientRectangle.Height);
            Refresh();
        }
    }
}
