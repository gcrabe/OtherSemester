using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace Solution4
{
    class Program
    {
        static void Main(string[] args)
        {
            Program prog = new Program();
            StreamReader inp = new StreamReader("tokens.txt");
            string[] descriptionTokens = inp.ReadToEnd().Split('\n');
            List<Token> tokens = new GenerationTokens(descriptionTokens).GetTokens();
            inp.Close();

            inp = new StreamReader("program.txt");
            string data = inp.ReadToEnd();
            inp.Close();

            LexicalAnalyzer anlz = new LexicalAnalyzer(tokens,data);
            StreamWriter oup = new StreamWriter("result.txt");
            oup.Write(anlz.Analyzer());
            oup.Close();
        }
    }
}
