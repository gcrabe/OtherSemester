using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Solution1_2
{
    class Task1
    {
        string []F = {"q2"};

        private bool IsF(string state)
        {
            for (int i=0;i<F.Length;i++)
            {
                if(F[i]==state)
                {
                    return true;
                }
            }
            return false;
        }

        private string Control(string state, char sym)
        {
            if(sym == '+' || sym == '-')
            {
                switch(state)
                {
                    case "q0":
                        return "q1";
                    default:
                        return "q3";
                }
            }

            if ('0' <= sym && sym <= '9')
            {
                switch(state)
                {
                    case "q0":
                        return "q2";
                    case "q1":
                        return "q2";
                    case "q2":
                        return "q2";
                    default:
                        return "q3";
                }
            }

            return "q3";
        }
        public bool automation(string s, int index, ref int m)
        {
            bool finalState = false;
            string state = "q0";
            int i = index;

            while(i<s.Length)
            {
                state = Control(state,s[i]);

                if(IsF(state))
                {
                    finalState = true;
                    m = i - index+1;
                }

                if(state=="q3")
                {
                    break;
                }

                i++;
            }

            return finalState;
        }
    }
}
