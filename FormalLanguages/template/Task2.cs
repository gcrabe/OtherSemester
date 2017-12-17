using System;
using System.Collections.Generic;
using System.Collections;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution1_2
{
    class Task2
    {
        string[] F = {"q3", "q4", "q5", "q6", "q10" };

        public bool Automation(string s, int index, ref int m)
        {
            bool finalState = false;
            ArrayList states = new ArrayList();
            states.Add("q0");
            int i = index;
            while (i < s.Length)
            {
                states = Control(states, s[i]);
                if (IsF(states))
                {
                    finalState = true;
                    m = i - index + 1;
                }
                if (states.Count == 0)
                {
                    break;
                }
                i++;
            }
            return finalState;
        }

        private bool IsF(ArrayList states)
        {
            for(int i=0;i<F.Length;i++)
            {
                for(int j=0;j<states.Count;j++)
                {
                    if(F[i].Equals(states[j]))
                    {
                        return true;
                    }
                }
            }
            return false;
        }

        private ArrayList Control(ArrayList states, char sym)
        {
            ArrayList temp = new ArrayList();
            foreach (string i in states)
            {
                if (sym == '+' || sym == '-')
                {
                    switch (i)
                    {
                        case "q0":
                            temp.Add("q1");
                            temp.Add("q2");
                            break;
                        case "q7":
                            temp.Add("q9");
                            break;
                    }
                }

                if ('0' <= sym && sym <= '9')
                {
                    switch (i)
                    {
                        case "q0":
                            temp.Add("q3");
                            break;
                        case "q2":
                            temp.Add("q3");
                            break;
                        case "q3":
                            temp.Add("q3");
                            break;
                        case "q5":
                            temp.Add("q6");
                            break;
                        case "q6":
                            temp.Add("q6");
                            break;
                        case "q8":
                            temp.Add("q10");
                            break;
                        case "q9":
                            temp.Add("q10");
                            break;
                        case "q10":
                            temp.Add("q10");
                            break;
                        case "q11":
                            temp.Add("q6");
                            break;
                    }
                }

                if (sym == '.')
                {
                    switch (i)
                    {
                        case "q0":
                            temp.Add("q11");
                            break;
                        case "q1":
                            temp.Add("q11");
                            break;
                        case "q3":
                            temp.Add("q4");
                            temp.Add("q5");
                            break;
                    }
                }

                if (sym == 'e' || sym == 'E')
                {
                    switch (i)
                    {
                        case "q4":
                            temp.Add("q7");
                            temp.Add("q8");
                            break;
                        case "q6":
                            temp.Add("q7");
                            temp.Add("q8");
                            break;
                    }
                }
            }
            return temp;
        }
    }
}
