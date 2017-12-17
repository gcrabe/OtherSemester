using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution4
{
    public class Auto
    {
        public static int numBranch = 0;
        HashSet<string> s;
        HashSet<string> f;
        HashSet<string> alphabet;
        Dictionary<string, Dictionary<string, HashSet<string>>> t;

        public HashSet<string> S
        {
            get
            {
                return s;
            }

            set
            {
                s = value;
            }
        }

        public HashSet<string> F
        {
            get
            {
                return f;
            }

            set
            {
                f = value;
            }
        }

        public HashSet<string> Alphabet
        {
            get
            {
                return alphabet;
            }

            set
            {
                alphabet = value;
            }
        }

        public Dictionary<string, Dictionary<string, HashSet<string>>> T
        {
            get
            {
                return t;
            }

            private set
            {
                t = value;
            }
        }

        public Auto()
        {
            this.S = new HashSet<string>();
            this.F = new HashSet<string>();
            this.Alphabet = new HashSet<string>();
            this.T = new Dictionary<string, Dictionary<string, HashSet<string>>>();
        }

        public Auto(char sym)
        {
            this.S = new HashSet<string>();
            this.F = new HashSet<string>();
            this.Alphabet = new HashSet<string>();
            this.T = new Dictionary<string, Dictionary<string, HashSet<string>>>();
            InitAutoSym(this.Alphabet, this.S, this.T, this.F, sym);
        }

        public Auto(string set)
        {
            this.S = new HashSet<string>();
            this.F = new HashSet<string>();
            this.Alphabet = new HashSet<string>();
            this.T = new Dictionary<string, Dictionary<string, HashSet<string>>>();
            if (set == "w")
            {
                InitAutoW(this.Alphabet, this.S, this.T, this.F);
            }
            if (set == "d")
            {
                InitAutoD(this.Alphabet, this.S, this.T, this.F);
            }
        }

        public Auto(HashSet<string> alph, HashSet<string> s,
        			Dictionary<string, Dictionary<string, HashSet<string>>> t,
        			HashSet<string> f)
        {
            this.Alphabet = new HashSet<string>(alph);
            this.S = new HashSet<string>(s);
            this.T = new Dictionary<string, Dictionary<string, HashSet<string>>>(t);
            this.F = new HashSet<string>(f);
        }

        public bool Automation(string s, int index, ref int m)
        {
            bool finalState = false;
            HashSet<string> states = new HashSet<string>(S);
            //states.Add("q0");
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

        private bool IsF(HashSet<string> states)
        {
            foreach (string j in states)
            {
                if (F.Contains(j))
                {
                    return true;
                }
            }
            
            return false;
        }

        private HashSet<string> Control(HashSet<string> states, char sym)
        {

            HashSet<string> temp = new HashSet<string>();
            foreach (string i in states)
            {
                if (T[i].ContainsKey(sym.ToString()) && T[i][sym.ToString()].Count!=0)
                {
                    foreach(string t in T[i][sym.ToString()])
                    {
                        if(!temp.Contains(t))
                        {
                            temp.Add(t);
                        }
                    }
                }
                
            }
            return temp;
        }

        private void InitAutoSym(HashSet<string> alph, HashSet<string> s, Dictionary<string, Dictionary<string, HashSet<string>>> t, HashSet<string> f, char sym)
        {
            alph.Add(sym.ToString());
            s.Add(Auto.numBranch.ToString());

            t.Add(Auto.numBranch.ToString(), new Dictionary<string, HashSet<string>>());
            t.Add((Auto.numBranch+1).ToString(), new Dictionary<string, HashSet<string>>());

            t[Auto.numBranch.ToString()].Add(sym.ToString(), new HashSet<string>());
            t[(Auto.numBranch+1).ToString()].Add(sym.ToString(), new HashSet<string>());
            t[Auto.numBranch.ToString()][sym.ToString()].Add((++Auto.numBranch).ToString());
            
            f.Add(Auto.numBranch.ToString());
            Auto.numBranch++;
        }

        private void InitAutoW(HashSet<string> alph, HashSet<string> s, Dictionary<string, Dictionary<string, HashSet<string>>> t, HashSet<string> f)
        {
            for(int c='a';c<='z';c++)
            {
                alph.Add(((Char)c).ToString());
            }

            for (int c = 'A'; c <= 'Z'; c++)
            {
                alph.Add(((Char)c).ToString());
            }

            s.Add(Auto.numBranch.ToString());
            t.Add(Auto.numBranch.ToString(), new Dictionary<string, HashSet<string>>());
            t.Add((Auto.numBranch+1).ToString(), new Dictionary<string, HashSet<string>>());

            HashSet<string> tmp = new HashSet<string>();
            tmp.Add((Auto.numBranch+1).ToString());
            foreach (string i in alph)
            {
                t[Auto.numBranch.ToString()].Add(i, new HashSet<string>(tmp));
                t[(Auto.numBranch+1).ToString()].Add(i, new HashSet<string>());
            }
            
            f.Add((++Auto.numBranch).ToString());
            Auto.numBranch++;
        }

        private void InitAutoD(HashSet<string> alph, HashSet<string> s, Dictionary<string, Dictionary<string, HashSet<string>>> t, HashSet<string> f)
        {
            for (int c = 0; c <= 9; c++)
            {
                alph.Add(c.ToString());
            }

            s.Add(Auto.numBranch.ToString());
            t.Add(Auto.numBranch.ToString(), new Dictionary<string, HashSet<string>>());
            t.Add((Auto.numBranch + 1).ToString(), new Dictionary<string, HashSet<string>>());

            HashSet<string> tmp = new HashSet<string>();
            tmp.Add((Auto.numBranch + 1).ToString());
            foreach (string i in alph)
            {
                t[Auto.numBranch.ToString()].Add(i, new HashSet<string>(tmp));
                t[(Auto.numBranch + 1).ToString()].Add(i, new HashSet<string>());
            }

            f.Add((++Auto.numBranch).ToString());
            Auto.numBranch++;
        }
    }
}
