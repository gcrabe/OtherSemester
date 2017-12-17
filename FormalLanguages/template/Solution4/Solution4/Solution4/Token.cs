using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution4
{
    class Token: IComparable
    {
        Auto auto;
        string ind;
        int priority;
        
        public Token(string ind, int priority, Auto auto)
        {
            this.Ind = ind;
            this.Priority = priority;
            this.auto = auto;
        }

        public string Ind
        {
            get
            {
                return ind;
            }

            set
            {
                ind = value;
            }
        }

        public int Priority
        {
            get
            {
                return priority;
            }

            set
            {
                priority = value;
            }
        }

        public bool Automation(string s, int index, ref int m)
        {
            return auto.Automation(s,index,ref m);
        }

        public int CompareTo(Object b)
        {
            if(this.Priority>((Token)b).Priority)
            {
                return -1;
            }
            if (this.Priority < ((Token)b).Priority)
            {
                return 1;
            }
            return 0;
        }

    }
}
