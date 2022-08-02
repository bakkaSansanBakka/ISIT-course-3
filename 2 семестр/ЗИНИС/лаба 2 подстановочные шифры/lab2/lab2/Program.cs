using System.Text;
using System.Diagnostics;

namespace lab2
{
    class Program
    {
        class Caesar
        {
            private static string alpha = "abcdefghijklmnopqrstuvwxyz";
            private static char[] newAlpha = new char[26];

            public static string encrypt(string Message)
            {
                string res = "";
                foreach (char ch in Message)
                {
                    for (int i = 0; i < alpha.Length; i++)
                    {
                        if (ch == alpha[i])
                        {
                            res += newAlpha[i];
                            break;
                        }
                    }
                }
                return res;
            }

            public static string decrypt(string Message)
            {
                string res = "";
                foreach (char ch in Message)
                {
                    for (int i = 0; i < newAlpha.Length; i++)
                    {
                        if (ch == newAlpha[i])
                        {
                            res += alpha[i];
                            break;
                        }
                    }
                }
                return res;
            }

            public static void createNewAlpha(string keyWord, int key) // создаёт новый алфавит с помощью ключа
            {
                bool findSame = false;
                key--;
                int beg = 0, current = key;
                // добавить ключевое слово в новый алфавит
                for (int i = key; i < keyWord.Length + key; i++)
                {
                    for (int j = key; j < keyWord.Length + key; j++)
                    {
                        if (keyWord[i - key] == newAlpha[j])
                        {
                            findSame = true;
                            break;
                        }
                    }
                    if (!findSame)// если повторений нету, то буква добавляется в новый алфавит
                    {
                        newAlpha[current] = keyWord[i - key];
                        current++;
                    }
                    findSame = false;
                }

                // добавить буквы после ключевого слова
                for (int i = 0; i < alpha.Length; i++)
                {
                    for (int j = 0; j < newAlpha.Length; j++)
                    {
                        if (alpha[i] == newAlpha[j])
                        {
                            findSame = true;
                            break;
                        }
                    }
                    if (!findSame)
                    {
                        newAlpha[current] = alpha[i];
                        current++;
                    }
                    findSame = false;
                    if (current == newAlpha.Length)
                    {
                        beg = i;
                        break;
                    }
                }

                // добавить буквы после ключевого слова
                current = 0;
                for (int i = beg; i < alpha.Length; i++)
                {
                    for (int j = 0; j < newAlpha.Length; j++)
                    {
                        if (alpha[i] == newAlpha[j])
                        {
                            findSame = true;
                            break;
                        }
                    }
                    if (!findSame)
                    {
                        newAlpha[current] = alpha[i];
                        current++;
                    }
                    findSame = false;
                }
            }

            public static string getNewAlpha()
            {
                string strNewAlpha = new string(newAlpha);
                return strNewAlpha;
            }
        }

        static void Main(string[] args)
        {
            Console.WriteLine("---------------Шифр Цезаря--------------------");

            Console.Write("Ключевое слово: potapeyko");

            Caesar.createNewAlpha("potapeyko", 1);
            Console.WriteLine();
            Console.WriteLine("Зашифрованный алфавит: " + Caesar.getNewAlpha());
            Console.WriteLine();

            string open = "", close = "";

            using (StreamReader reader = new StreamReader(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 2 подстановочные шифры\lab2\english.txt"))
            {
                open = reader.ReadToEnd().ToLower();
            }
            Stopwatch stopWatch = new Stopwatch();
            stopWatch.Start();

            close = Caesar.encrypt(open);
            Console.WriteLine();
            Console.WriteLine("\nЗашифрованное сообщение: " + close);
            stopWatch.Stop();
            TimeSpan ts = stopWatch.Elapsed;
            string elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                 ts.Hours, ts.Minutes, ts.Seconds,
                 ts.Milliseconds / 10);
            Console.WriteLine("\nRunTime " + elapsedTime + "\n");

            stopWatch.Restart();
            open = Caesar.decrypt(close);
            Console.WriteLine();
            Console.WriteLine("\nРасшифрованное сообщение: " + open);
            stopWatch.Stop();
            ts = stopWatch.Elapsed;
            elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                ts.Hours, ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            Console.WriteLine("\nRunTime " + elapsedTime + "\n");


            Console.WriteLine("---------------таблица Трисемуса--------------------");
            string keyWordTsiremus = "Polina";

            Trisinus.createTableTrisemus(keyWordTsiremus);
            Console.WriteLine();
            stopWatch.Restart();
            close = Trisinus.encryptTrisemus(open);
            Console.WriteLine("Зашифрованное сообщение: " + close);

            stopWatch.Stop();
            Trisinus.EntropyEnglishAlphabet(close);
            ts = stopWatch.Elapsed;
            elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                ts.Hours, ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            Console.WriteLine("\nRunTime " + elapsedTime + "\n");

            stopWatch.Restart();
            open = Trisinus.decryptTrisemus(close);
            Console.WriteLine();
            Console.WriteLine("Расшифрованное сообщение: " + open);
            stopWatch.Stop();
            Trisinus.EntropyEnglishAlphabet(open);
            ts = stopWatch.Elapsed;
            elapsedTime = String.Format("{0:00}:{1:00}:{2:00}.{3:00}",
                ts.Hours, ts.Minutes, ts.Seconds,
                ts.Milliseconds / 10);
            Console.WriteLine("\nRunTime " + elapsedTime + "\n");
            Console.ReadKey();


        }


        class Trisinus
        {

            private static string alpha = "abcdefghijklmnopqrstuvwxyz";
            private static char[] newAlpha = new char[26];
            private static int columnCount = 13;
            private static int rowCount = 2;
            private static char[,] tableTrisemus = new char[rowCount, columnCount];

            public static void EntropyEnglishAlphabet(string text)
            {
                int[] countLetter = new int[26];
                int countLettersInFile = 0;
                double[] probabilityLetters = new double[26];
                text = text.ToLower();
                countLettersInFile = text.Count();

                Console.WriteLine();



                if (!File.Exists(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 2 подстановочные шифры\lab2\mes.txt"))
                {

                    for (int j = 0; j < 26; j++)
                    {

                        using (StreamWriter writer = new StreamWriter(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 2 подстановочные шифры\lab2\mes.txt", true, Encoding.Default))
                        {

                            countLetter[j] = text.Count(x => x == alpha[j]);
                            writer.WriteLine($"{alpha[j]}={countLetter[j]}");

                        }

                    }
                }
                else
                {
                    for (int j = 0; j < 26; j++)
                    {

                        using (StreamWriter writer = new StreamWriter(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 2 подстановочные шифры\lab2\mesShyfr.txt", true, Encoding.Default))
                        {

                            countLetter[j] = text.Count(x => x == alpha[j]);
                            writer.WriteLine($"{alpha[j]}={countLetter[j]}");

                        }

                    }
                }

            }

            public static void createTableTrisemus(string keyWord)
            {

                keyWord = new string(keyWord.ToLower().Distinct().ToArray());
                int current = 0;
                bool findSame = false;
                double row = (double)keyWord.Length / (double)columnCount;

                for (int i = 0; i < Math.Ceiling(row); i++)
                {
                    for (int j = 0; (j < columnCount) && current < keyWord.Length; j++)
                    {
                        if (!findSame)
                        {
                            tableTrisemus[i, j] = keyWord[current];
                            current++;
                        }
                    }
                }

                for (int h = 0; h < alpha.Length; h++)
                {
                    findSame = false;
                    for (int i = 0; i < tableTrisemus.GetLength(0); i++)
                    {
                        for (int j = 0; j < tableTrisemus.GetLength(1); j++)
                        {
                            if (alpha[h] == tableTrisemus[i, j])
                            {
                                findSame = true;
                                break;
                            }
                        }
                        if (findSame)
                            break;
                    }
                    if (!findSame)
                    {
                        tableTrisemus[current / columnCount, current % columnCount] = alpha[h];
                        current++;
                    }
                }

                Console.WriteLine("Таблица:");
                for (int i = 0; i < tableTrisemus.GetLength(0); i++)
                {
                    for (int j = 0; j < tableTrisemus.GetLength(1); j++)
                    {
                        Console.Write(tableTrisemus[i, j] + "\t");
                    }
                    Console.WriteLine();
                }
            }

            public static string encryptTrisemus(string Message)
            {
                string result = "";

                foreach (var item in Message)
                {
                    for (int i = 0; i < tableTrisemus.GetLength(0); i++)
                    {
                        for (int j = 0; j < tableTrisemus.GetLength(1); j++)
                        {
                            if (tableTrisemus[i, j] == item)
                            {
                                if (tableTrisemus[(i + 1) % rowCount, j] == ' ')
                                {
                                    result += tableTrisemus[(i + 2) % rowCount, j];
                                }
                                else
                                {
                                    result += tableTrisemus[(i + 1) % rowCount, j];
                                }
                            }
                        }
                    }
                }

                return result;
            }

            public static string decryptTrisemus(string Message)
            {
                string result = "";

                foreach (var item in Message)
                {
                    for (int i = 0; i < tableTrisemus.GetLength(0); i++)
                    {
                        for (int j = 0; j < tableTrisemus.GetLength(1); j++)
                        {
                            if (tableTrisemus[i, j] == item)
                            {
                                if (tableTrisemus[(i + rowCount - 1) % rowCount, j] == ' ')
                                {
                                    result += tableTrisemus[(i + rowCount - 2) % rowCount, j];
                                }
                                else
                                {
                                    result += tableTrisemus[(i + rowCount - 1) % rowCount, j];
                                }
                            }
                        }
                    }
                }

                return result;
            }
        }

    }
}


