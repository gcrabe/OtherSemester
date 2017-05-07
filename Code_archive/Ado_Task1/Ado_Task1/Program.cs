using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Ado_Task1
{
    public class MultiSet<T> : Dictionary<T, int>
    {
        public MultiSet() : base() { }
        public MultiSet(IDictionary<T, int> dictionary) : base(dictionary) { }
        public MultiSet(IEqualityComparer<T> comparer) : base(comparer) { }
        public MultiSet(IDictionary<T, int> dictionary, IEqualityComparer<T> comparer) : base(dictionary, comparer) { }

        public MultiSet(IEnumerable<T> collection, IEqualityComparer<T> comparer)
            : this(comparer)
        {
            foreach (var element in collection)
                Add(element);
        }

        public MultiSet(IEnumerable<T> collection)
            : this(collection, EqualityComparer<T>.Default) { }

        public IEnumerable<T> AsPlainEnumerable()
        {
            return this.SelectMany(pair => Enumerable.Range(1, pair.Value).Select(_ => pair.Key));
        }

        public void Add(T key)
        {
            this[key] = this[key] + 1;
        }

        public new int this[T key]
        {
            get
            {
                int n = 0;
                TryGetValue(key, out n);
                return n;
            }
            set
            {
                if (value < 0)
                    throw new ArgumentOutOfRangeException("Count of elements must be great or equals than zero");
                base[key] = value;
            }
        }

        public override int GetHashCode()
        {
            return this.Aggregate(0, (res, p) => res ^ Comparer.GetHashCode(p.Key) ^ p.Value.GetHashCode());
        }

        public override bool Equals(object obj)
        {
            var other = (MultiSet<T>)obj;
            return Count == other.Count && this.All(p => other[p.Key] == p.Value);
        }
    }

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
            string inputPath = @".\input.txt";
            string outputPath = @".\output.txt";

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

            MultiSet<string> extensions = new MultiSet<string>();

            foreach (string file in files)
                extensions.Add(Path.GetExtension(file));

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
                        writer.WriteLine(record.Item1  + '#' + record.Item2.ToString() + '#' + record.Item3.ToString());
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The file could not be open: " + e.Message);
            }
        }
    }
}
