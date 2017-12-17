using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution4
{
    class LexicalAnalyzer
    {
        string inputS;
        StringBuilder outputS;

        List<Token> tokens;
        int[]m;

        public LexicalAnalyzer(List<Token> tokens, string inp)
        {
            this.tokens = new List<Token>(tokens);
            this.inputS = inp;
            this.m = new int[tokens.Count];
            this.outputS = new StringBuilder();
        }

        public string Analyzer()
        {
            tokens.Sort();
            int i = 0;
            while (i < inputS.Length)
            {
                //Определяем m
                DefineToken(ref inputS, i);
                //Определяем номер token
                int numToken = FindNumToken();

                if(numToken==-1)
                {
                    outputS.AppendLine("Не достигнут конец строки");
                    break;
                }
                //Выводим token
                PrintToken(numToken,inputS.Substring(i,m[numToken]));
                i += m[numToken] - 1;
                //Обнуляем массив
                Array.Clear(m, 0, tokens.Count);
                i++;
            }
            return outputS.ToString();
        }

        private void DefineToken(ref string s, int index)
        {
            for (int j = 0; j < tokens.Count; j++)
            {
                tokens[j].Automation(s, index, ref m[j]);
            }
        }

        private int FindNumToken()
        {
            int maxEl = m.Max();
            if (maxEl != 0)
            {
                return Array.IndexOf(m, maxEl);
            }

            return -1;
        }

        private void PrintToken(int numToken, string token)
        {
            outputS.Append("<" + tokens[numToken].Ind + ",");
            for (int i = 0; i < token.Length; i++)
            {
                if (token[i] == ' ')
                {
                    outputS.Append(" ");
                    continue;
                }
                if (token[i] == '\n')
                {
                    outputS.Append("\\n");
                    continue;
                }
                if (token[i] == '\r')
                {
                    outputS.Append("\\r");
                    continue;
                }
                if (token[i] == '\t')
                {
                    outputS.Append("\\t");
                    continue;
                }
                outputS.Append(token[i]);
            }
            outputS.AppendLine(">");
        }
    }
}
