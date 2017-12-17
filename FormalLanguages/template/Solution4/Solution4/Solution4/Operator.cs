using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution4
{
    public class Operator
    {
        public static Auto Association(Auto a, Auto b)
        {
            //1
            HashSet<string> alphabet = new HashSet<string>(a.Alphabet.Concat(b.Alphabet));
            //2
            HashSet<string> s = new HashSet<string>(a.S.Concat(b.S));
            //3
            Dictionary<string, Dictionary<string, HashSet<string>>> t = MakeTForAssociation(a,b, alphabet);
            //4
            HashSet<string> f = new HashSet<string>(a.F.Concat(b.F));

            return new Auto(alphabet,s,t,f);
        }

        public static Auto Сatenation(Auto a, Auto b)
        {
            //1
            HashSet<string> alphabet = new HashSet<string>(a.Alphabet.Concat(b.Alphabet));
            //2
            HashSet<string> s = new HashSet<string>(a.S);
            //3
            Dictionary<string, Dictionary<string, HashSet<string>>> t = MakeTForCatenation(a, b, alphabet);
            //4
            HashSet<string> f = new HashSet<string>(b.F.Concat(AddF(a.F,b.S,b.F)));

            return new Auto(alphabet, s, t, f);
        }

        public static Auto Iteration(Auto a)
        {
            //1
            HashSet<string> alphabet = new HashSet<string>(a.Alphabet);
            //2
            HashSet<string> s = new HashSet<string>(a.S);
            //3
            Dictionary<string, Dictionary<string, HashSet<string>>> t = MakeTForIteration(a);
            //4
            HashSet<string> f = new HashSet<string>(a.F);

            s.Add(Auto.numBranch.ToString());
            f.Add(Auto.numBranch.ToString());
            Auto.numBranch++;

            return new Auto(alphabet, s, t,f);
        }

        private static Dictionary<string, Dictionary<string, HashSet<string>>> MakeTForAssociation(Auto a,Auto b, HashSet<string> alphabet)
        {
            Dictionary<string, Dictionary<string, HashSet<string>>> c = new Dictionary<string, Dictionary<string, HashSet<string>>>(a.T.Count+b.T.Count);

            foreach (string i in a.T.Keys)
            {
                Dictionary<string, HashSet<string>> temp = new Dictionary<string, HashSet<string>>();
                foreach (string j in alphabet)
                {
                    temp.Add(j, new HashSet<string>());
                }
                c.Add(i, temp);
            }

            foreach (string i in b.T.Keys)
            {
                if (!c.ContainsKey(i))
                {
                    Dictionary<string, HashSet<string>> temp = new Dictionary<string, HashSet<string>>();
                    foreach (string j in alphabet)
                    {
                        temp.Add(j, new HashSet<string>());
                    }
                    c.Add(i, temp);
                }
            }

            foreach(string i in a.T.Keys)
            {
                foreach (string j in a.T[i].Keys)
                {
                    c[i][j] = new HashSet<string>(c[i][j].Concat(a.T[i][j]));
                }
            }

            foreach (string i in b.T.Keys)
            {
                foreach (string j in b.T[i].Keys)
                {
                    c[i][j] = new HashSet<string>(c[i][j].Concat(b.T[i][j]));
                }
            }

            return c;
        }

        private static Dictionary<string, Dictionary<string, HashSet<string>>> MakeTForCatenation(Auto a, Auto b, HashSet<string> alphabet)
        {
            Dictionary<string, Dictionary<string, HashSet<string>>> c = new Dictionary<string, Dictionary<string, HashSet<string>>>(a.T.Count + b.T.Count);

            foreach (string i in a.T.Keys)
            {
                Dictionary<string, HashSet<string>> temp = new Dictionary<string, HashSet<string>>();
                foreach (string j in alphabet)
                {
                    temp.Add(j, new HashSet<string>());
                }
                c.Add(i, temp);
            }

            foreach (string i in b.T.Keys)
            {
                if (!c.ContainsKey(i))
                {
                    Dictionary<string, HashSet<string>> temp = new Dictionary<string, HashSet<string>>();
                    foreach (string j in alphabet)
                    {
                        temp.Add(j, new HashSet<string>());
                    }
                    c.Add(i, temp);
                }
            }

            foreach (string i in a.T.Keys)
            {
                foreach (string j in a.T[i].Keys)
                {
                    c[i][j] = new HashSet<string>(c[i][j].Concat(a.T[i][j]));
                }
            }

            foreach (string i in b.T.Keys)
            {
                foreach (string j in b.T[i].Keys)
                {
                    c[i][j] = new HashSet<string>(c[i][j].Concat(b.T[i][j]));
                }
            }


            foreach (string i in b.S)
            {
                foreach (string k in alphabet)
                {
                    if (c[i][k].Count != 0)
                    {
                        foreach (string j in a.F)
                        {
                            c[j][k]=new HashSet<string>(c[j][k].Concat(c[i][k]));
                        }
                    }
                }
            }

            return c;
        }

        private static HashSet<string> AddF(HashSet<string> af, HashSet<string> bs, HashSet<string> bf)
        {
            HashSet<string> c=new HashSet<string>();

            foreach (string i in bs)
            {
                if (bf.Contains(i))
                {
                    c = af;
                    break;
                }
            }

            return c;
        }

        private static Dictionary<string, Dictionary<string, HashSet<string>>> MakeTForIteration(Auto a)
        {
            Dictionary<string, Dictionary<string, HashSet<string>>> c = new Dictionary<string, Dictionary<string, HashSet<string>>>(a.T);

            foreach (string i in a.S)
            {
                foreach (string j in a.Alphabet)
                {
                    if (a.T[i][j].Count > 0)
                    {
                        foreach(string k in a.F)
                        {
                            c[k][j] = new HashSet<string>(c[k][j].Concat(a.T[i][j]));
                        }
                    }
                }
            }

            Dictionary<string, HashSet<string>> temp = new Dictionary<string, HashSet<string>>();
            foreach (string i in a.Alphabet)
            {
                temp.Add(i,new HashSet<string>());
            }
            c.Add(Auto.numBranch.ToString(),temp);

            return c;
        }
    }
}
