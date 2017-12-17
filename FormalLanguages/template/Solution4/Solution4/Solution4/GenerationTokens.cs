using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Solution4
{
    class GenerationTokens
    {
        string[] descriptionTokens;
        List<Token> tokens;

        public GenerationTokens(string[] descriptionTokens)
        {
            this.descriptionTokens = descriptionTokens;
            this.tokens = new List<Token>();
        }

        public List<Token> GetTokens()
        {
            foreach (string i in descriptionTokens)
            {
                string[] parts = PickOutParts(i);
                string reg = ProcessReg(parts[2]);
                Auto auto = GenerationAuto(reg);
                Token token = new Token(parts[0], int.Parse(parts[1]), auto);
                tokens.Add(token);
            }
            return tokens;
        }

        private string[] PickOutParts(string str)
        {
            string[] parts = new string[3];
            int ind1 = str.IndexOf(' ');
            parts[0] = str.Substring(1, ind1 - 1);
            int ind2 = str.IndexOf(' ', ind1 + 1);
            parts[1] = str.Substring(ind1 + 1, ind2 - ind1 - 1);
            parts[2] = "("+str.Substring(ind2 + 1, str.Length - 1 - ind2 - 1)+")";
            return parts;
        }

        private string ProcessReg(string reg)
        {

            string outReg = "";
            for (int i = 0; i < reg.Length; i++)
            {
                if (reg[i] == ',' && IsPartReg(reg, i - 1))
                {
                    outReg += '|';
                    continue;
                }
                if (reg[i] == '+' && IsPartReg(reg, i - 1))
                {
                    outReg += '|';
                    continue;
                }
                if (reg[i] == '('
                    &&
                    ((i > 0 && (reg[i - 1] == ')' && IsPartReg(reg, i - 2)))
                    ||
                    (i > 0 && (reg[i - 1] == '*' && reg[i - 2] == ')' && IsPartReg(reg, i - 3)))))
                {
                    outReg += '.';
                }

                outReg += reg[i];

                if (CanPointSet(reg, i))
                {
                    outReg += '.';
                }
            }
            return outReg;
        }
        private Auto GenerationAuto(string reg)
        {
            Stack<Auto> operands = new Stack<Auto>();
            Stack<char> operations = new Stack<char>();

            for (int i = 0; i < reg.Length; i++)
            {
                //1. New operand
                //2. New operation
                //1.
                if (reg[i] == '\\')
                {
                    if (reg[i + 1] == 'w' || reg[i + 1] == 'd')
                    {
                        operands.Push(new Auto(reg[i + 1].ToString()));
                        if (operations.Count != 0)
                        {
                            if (operations.Peek() == '.')
                            {
                                Auto b = operands.Pop();
                                Auto a = operands.Pop();
                                operands.Push(Operator.Сatenation(a, b));
                                operations.Pop();
                            }
                        }

                        i++;
                        continue;
                    }

                    if (reg[i + 1] == 'n' || reg[i + 1] == 'r' || reg[i + 1] == 't')
                    {
                        char c=' ';
                        if(reg[i + 1] == 'n')
                        {
                            c = '\n';
                        }
                        if (reg[i + 1] == 'r')
                        {
                            c = '\r';
                        }
                        if (reg[i + 1] == 't')
                        {
                            c = '\t';
                        }

                        operands.Push(new Auto(c));
                        if (operations.Count != 0)
                        {
                            if (operations.Peek() == '.')
                            {
                                Auto b = operands.Pop();
                                Auto a = operands.Pop();
                                operands.Push(Operator.Сatenation(a, b));
                                operations.Pop();
                            }
                        }

                        i++;
                        continue;
                    }

                    operands.Push(new Auto(reg[i + 1]));

                    if(operations.Count!=0)
                    {
                        if(operations.Peek()=='.')
                        {
                            Auto b = operands.Pop();
                            Auto a = operands.Pop();
                            operands.Push(Operator.Сatenation(a, b));
                            operations.Pop();
                        }
                    }

                    i++;
                    continue;
                }
                //1.
                if (IsLetter(reg[i]) || IsDigit(reg[i]))
                {
                    operands.Push(new Auto(reg[i]));

                    if (operations.Count != 0)
                    {
                        if (operations.Peek() == '.')
                        {
                            Auto b = operands.Pop();
                            Auto a = operands.Pop();
                            operands.Push(Operator.Сatenation(a, b));
                            operations.Pop();
                        }
                    }

                    continue;
                }


                //2.
                if (reg[i] == '*' && IsPartReg(reg, i - 1))
                {
                    Auto a = operands.Pop();
                    operands.Push(Operator.Iteration(a));
                    continue;
                }

                if (reg[i] == '(' && IsPartReg(reg, i - 1))
                {
                    operations.Push(reg[i]);
                    continue;
                }

                //2.
                if (reg[i] == ')' && IsPartReg(reg, i - 1))
                {
                    operands.Push(CalcExp(operands, operations));

                    if (operations.Count != 0)
                    {
                        if (operations.Peek() == '.')
                        {
                            Auto b = operands.Pop();
                            Auto a = operands.Pop();
                            operands.Push(Operator.Сatenation(a, b));
                            operations.Pop();
                        }
                    }
                    continue;
                }
                if(reg[i]=='|' || reg[i]=='.')
                {
                    operations.Push(reg[i]);
                }
            }

            Console.WriteLine(operands.Count);
            return operands.Pop();
        }

        private bool IsPartReg(string s, int index)
        {
            if (index < 0)
            {
                return true;
            }

            int count = 0;
            for (int i = index; i >= 0; i--)
            {
                if (s[i] == '\\')
                {
                    count++;
                    continue;
                }
                break;
            }

            return count % 2 == 0;
        }

        private bool CanPointSet(string s, int i)
        {
            if (s.Length <= i + 1)
            {
                return false;
            }

            if (IsSym(s, i) && (IsSym(s, i + 1) || (s[i + 1] == '\\') || s[i + 1] == '('))
            {
                return true;
            }

            if ((s[i] == '*' || s[i] == ')') && IsPartReg(s, i - 1) && (IsSym(s, i + 1) || (s[i + 1] == '\\')))
            {
                return true;
            }

            return false;
        }

        private bool IsSym(string s, int i)
        {

            if (('0' <= s[i] && s[i] <= '9')
                ||
                ('a' <= s[i] && s[i] <= 'z')
                ||
                ('A' <= s[i] && s[i] <= 'Z')
                ||
                (!IsPartReg(s, i - 1)))
            {
                return true;
            }

            return false;
        }

        private bool IsLetter(char c)
        {

            if (('a' <= c && c <= 'z')
                ||
                ('A' <= c && c <= 'Z'))
            {
                return true;
            }

            return false;
        }

        private bool IsDigit(char c)
        {

            if ('0' <= c && c <= '9')
            {
                return true;
            }

            return false;
        }

        private Auto CalcExp(Stack<Auto>operands,Stack<char>operation)
        {
            Auto res= operands.Pop();

            while (operation.Peek() != '(')
            {
                if (operands.Count != 0)
                {
                    Auto b = operands.Pop();
                    res = Operator.Association(b, res);
                }
                operation.Pop();
            }
            operation.Pop();

            return res;
        }
    }
}
