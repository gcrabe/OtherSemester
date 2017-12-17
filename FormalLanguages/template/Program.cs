using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution1_2
{
    class Program
    {
        static void Main(string[] args)
        {
            Task1 task1 = new Task1();
            Task2 task2 = new Task2();

            string[] testsP = { "5.3","5", "+75", "-25", "-.3", "-3.", "3.", ".3", ".3e8", "3.e8", "3.e+8", "+3.e8", "+.3e8", "+.3e+8", "+3.e+8", "+3.5e+15" };
            string[] testsN = { ".", "+.", "+.e5", "-.e+", "-.e+5", "-e+5", ".e3", ".e+3", "+.e+3", "+e1", "e1"};

            for (int i=0;i<testsN.Length;i++)
            {
                int index = 0;
                int m = 0;
                //Console.WriteLine(task1.automation(input, index, ref m).ToString() + " "+m);
                Console.WriteLine("Input: " + testsN[i] + " " + task2.Automation(testsN[i], index, ref m).ToString() + " " + m);
            }

            /*
            for (int i = 0; i < testsN.Length; i++)
            {
                int index = 0;
                int m = 0;
                //Console.WriteLine(task1.automation(input, index, ref m).ToString() + " "+m);
                Console.WriteLine("Input: " + testsN[i] + " " + task2.automation(testsN[i], index, ref m).ToString() + " " + m);
            }*/

            /*
            string input = "";
            int index = 0;
            int m = 0;
            //Console.WriteLine(task1.automation(input, index, ref m).ToString() + " "+m);
            Console.WriteLine("Input: " + input + " " + task2.automation(input, index, ref m).ToString() + " " + m);
            */
        }
    }
}
