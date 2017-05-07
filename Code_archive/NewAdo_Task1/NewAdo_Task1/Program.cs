using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace NewAdo_Task1
{
    class Program
    {
        private static List<string> DirSearch(string dir)
        {
            List<string> files = new List<string>();

            try
            {
                foreach (string file in Directory.GetFiles(dir))
                    files.Add(file);

                foreach (string directory in Directory.GetDirectories(dir))
                    files.AddRange(DirSearch(directory));
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }

            return files;
        }

        static void Main(string[] args)
        {
            string inputPath = @"input.txt";
            string outputPath = @"output.txt";

            List<string> files = null;

            try
            {
                using (StreamReader reader = new StreamReader(inputPath, Encoding.GetEncoding(1251)))
                {
                    string directoryPath = reader.ReadToEnd();

                    files = DirSearch(directoryPath);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The file could not be read: " + e.Message);
            }

            Dictionary<string, int> extensions = new Dictionary<string, int>();

            foreach (string file in files)
            {
                string fileExtension = Path.GetExtension(file);

                if (!extensions.ContainsKey(fileExtension))
                    extensions.Add(fileExtension, 1);
                else
                    extensions[fileExtension]++;
            }

            List<Tuple<string, int, double>> ans = new List<Tuple<string, int, double>>();

            foreach (var ext in extensions)
            {
                string key = ext.Key.Remove(0, 1);
                int value = ext.Value;
                double percent = ((double)ext.Value / (double)files.Count) * 100.0;

                ans.Add(new Tuple<string, int, double>(key, value, percent));
            }

            ans.Sort((x, y) => y.Item2.CompareTo(x.Item2));

            try
            {
                using (StreamWriter writer = new StreamWriter(outputPath))
                {
                    foreach (var record in ans)
                        writer.WriteLine(record.Item1 + '#' + record.Item2.ToString() + '#' + record.Item3.ToString());
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The file could not be open: " + e.Message);
            }
        }
    }
}
