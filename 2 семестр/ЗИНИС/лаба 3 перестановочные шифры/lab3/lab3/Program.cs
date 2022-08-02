using System.Text.RegularExpressions;

namespace lab3
{
    class Program
    {
        private static string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        static void Main(string[] args)
        {
            Console.WriteLine("============== Маршрутная перестановка зигзагом ==============");
            string message = "";
            Cipher cipher = new Cipher();

            using (StreamReader sr = new StreamReader(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 3 перестановочные шифры\lab3\message.txt"))
            {
                string s = sr.ReadToEnd();
                string shRoute = cipher.RoutePerestShifr(s);
                Console.WriteLine("Исходный текст:\n" + s);
                Console.WriteLine("\nЗашифрованный текст:\n" + shRoute);
                string deshRoute = cipher.RoutePerestDeshifr(shRoute, s.Length);
                for (int i = 0; i < alpha.Length; i++)
                {
                    Console.WriteLine("{0}-{1}", alpha[i], Counter(alpha[i], shRoute));
                }
                Console.WriteLine("\nРасшифрованный текст:\n" + deshRoute);
            }

            using (StreamReader reader = new StreamReader(@"E:\3 курс\2 семестр\ЗИиНИС\лаба 3 перестановочные шифры\lab3\message.txt"))
            {
                message = reader.ReadToEnd().ToUpper();
                message = Regex.Replace(message, "[^A-Za-z]", "");
            }

            //int s = 100;

            //ZigzagRoutePermutation(message, s);

            char[] keyword1 = "polina".ToCharArray();
            char[] keyword2 = "potapeyko".ToCharArray();

            Console.WriteLine("\n\n============== Множественная перестановка ==============");

            MultiplePermutation(message, keyword1, keyword2);
        }

        static int Counter(char c, string s)
        {
            int counter = 0;
            foreach (char ch in s)
                if (c == ch)
                    counter++;
            return counter;
        }

        static void ZigzagRoutePermutation(string word, int s)
        {
            //EntropyEnglishAlphabet(word);
            int k = (int)Math.Floor((word.Length - 1) / (double)s) + 1;
            char[,] array = new char[s, k];

            for (int i = 0, t = 0; i < array.GetLength(0); i++)
            {
                for (int j = 0; j < array.GetLength(1); j++)
                {
                    array[i, j] = word[t];
                    t++;
                }
            }

            for (int i = 0; i < array.GetLength(0); i++)
            {
                for (int j = 0; j < array.GetLength(1); j++)
                {
                    Console.Write(array[i, j] + " ");
                }
                Console.WriteLine();
            }

            char[] cipher = new char[word.Length];

            for (int i = 0, t = 0; i < array.GetLength(1); i++)
            {
                int j;
                j = i % 2 == 0 ? array.GetLength(0) - 1 : 0;
                for (; ; t++)
                {
                    cipher[t] = array[j, i];
                    if (i % 2 == 0)
                    {
                        if (j == 0)
                        {
                            cipher[t] = array[j, i];
                            t++;
                        }
                        j--;
                        if (j < 0)
                            break;
                    }
                    else
                    {
                        if (j == array.GetLength(0) - 1)
                        {
                            cipher[t] = array[j, i];
                            t++;
                        }
                        j++;
                        if (j >= array.GetLength(0))
                            break;
                    }
                }
            }

            string result = "";
            foreach (var item in cipher)
            {
                result += item;
                Console.Write(item);
            }
            Console.WriteLine("\n");
            EntropyEnglishAlphabet(result);
        }

        static void MultiplePermutation(string message, char[] keyword1, char[] keyword2)
        {
            EntropyEnglishAlphabet(message);
            char[,] array = new char[keyword2.Length, keyword1.Length];
            for (int i = 0, k = 0; i < keyword2.Length; i++)
            {
                for (int j = 0; j < keyword1.Length; j++, k++)
                {
                    array[i, j] = message[k];
                }
            }

            Console.WriteLine("============== Начальное состояние таблицы ==============");
            Console.Write("\t");
            for (int i = 0; i < keyword1.Length; i++)
            {
                Console.Write(keyword1[i] + "\t");
            }
            Console.WriteLine();
            for (int i = 0, k = 0; i < keyword2.Length; i++)
            {
                bool ooo = true;
                for (int j = 0; j < keyword1.Length; j++, k++)
                {
                    if (ooo)
                        Console.Write(keyword2[i] + "\t");
                    Console.Write(array[i, j] + "\t");
                    ooo = false;
                }
                Console.WriteLine();
            }

            for (int y = 0; y < keyword1.Length; y++)
            {
                for (int i = 0; i < keyword2.Length - 1; i++)
                {
                    if (keyword2[i] > keyword2[i + 1])
                    {
                        char save;
                        for (int j = 0; j < keyword1.Length; j++)
                        {
                            save = array[i, j];
                            array[i, j] = array[i + 1, j];
                            array[i + 1, j] = save;
                        }
                        save = keyword2[i];
                        keyword2[i] = keyword2[i + 1];
                        keyword2[i + 1] = save;
                    }
                }
            }

            Console.WriteLine("\n");

            Console.WriteLine("============== Таблица после сортировки по строкам ==============");
            Console.Write("\t");
            for (int i = 0; i < keyword1.Length; i++)
            {
                Console.Write(keyword1[i] + "\t");
            }
            Console.WriteLine();
            for (int i = 0, k = 0; i < keyword2.Length; i++)
            {
                bool ooo = true;
                for (int j = 0; j < keyword1.Length; j++, k++)
                {
                    if (ooo)
                        Console.Write(keyword2[i] + "\t");
                    Console.Write(array[i, j] + "\t");
                    ooo = false;
                }
                Console.WriteLine();
            }


            for (int y = 0; y < keyword2.Length; y++)
            {
                for (int i = 0; i < keyword1.Length - 1; i++)
                {
                    if (keyword1[i] > keyword1[i + 1])
                    {
                        char save;
                        for (int j = 0; j < keyword2.Length; j++)
                        {
                            save = array[j, i];
                            array[j, i] = array[j, i + 1];
                            array[j, i + 1] = save;
                        }
                        save = keyword1[i];
                        keyword1[i] = keyword1[i + 1];
                        keyword1[i + 1] = save;
                    }
                }
            }
            Console.WriteLine("\n");
            Console.WriteLine("============== Конечная отсортированная таблица ==============");
            Console.Write("\t");
            for (int i = 0; i < keyword1.Length; i++)
            {
                Console.Write(keyword1[i] + "\t");
            }
            Console.WriteLine();
            for (int i = 0, k = 0; i < keyword2.Length; i++)
            {
                bool ooo = true;
                for (int j = 0; j < keyword1.Length; j++, k++)
                {
                    if (ooo)
                        Console.Write(keyword2[i] + "\t");
                    Console.Write(array[i, j] + "\t");
                    ooo = false;
                }
                Console.WriteLine();
            }

            string result = "";
            for (int i = 0; i < keyword2.Length; i++)
            {
                for (int j = 0; j < keyword1.Length; j++)
                {
                    result += array[i, j];
                }
            }
            Console.WriteLine(result);
            EntropyEnglishAlphabet(result);
        }

        public static void EntropyEnglishAlphabet(string text)
        {
            int[] countLetter = new int[26];
            int countLettersInFile = 0;
            double[] probabilityLetters = new double[26];
            text = text.ToUpper();
            countLettersInFile = text.Count();

            Console.WriteLine();
            Console.WriteLine($"Количество символов в файле: {countLettersInFile}");
            Console.WriteLine();
            Console.WriteLine("Количество вхождений каждой буквы:");

            for (int j = 0; j < 26; j++)
            {
                countLetter[j] = text.Count(x => x == alpha[j]);
                Console.WriteLine($"{ alpha[j]}: { countLetter[j]}");

                probabilityLetters[j] = (double)countLetter[j] / countLettersInFile;
                Console.WriteLine($"P({alpha[j]}): {Math.Round(probabilityLetters[j], 5)}");
                Console.WriteLine();
            }
        }

        class Cipher
        {
            char[,] massChar;
            string rs = String.Empty;
            List<int> list1;
            List<int> list2;
            public string RoutePerestShifr(string msg)
            {
                int counter = 0;
                string res = String.Empty;
                char[,] massChar = new char[25, (msg.Length / 25) + 1];
                for (int i = 0; i < massChar.GetLength(1); i++)
                    for (int j = 0; j < massChar.GetLength(0); j++)
                    {
                        if (counter < msg.Length)
                            massChar[j, i] = msg[counter];
                        counter++;
                    }
                for (int i = 0; i < massChar.GetLength(0); i++)
                    for (int j = 0; j < massChar.GetLength(1); j++)
                        res += massChar[i, j];
                return res;
            }

            public string RoutePerestDeshifr(string msg, int length)
            {
                int counter = 0;
                string res = String.Empty;
                char[,] massChar = new char[25, (length / 25) + 1];
                for (int i = 0; i < massChar.GetLength(0); i++)
                    for (int j = 0; j < massChar.GetLength(1); j++)
                    {
                        if (counter < msg.Length)
                            massChar[i, j] = msg[counter];
                        counter++;
                    }
                for (int i = 0; i < massChar.GetLength(1); i++)
                    for (int j = 0; j < massChar.GetLength(0); j++)
                        res += massChar[j, i];
                return res.Remove(length);
            }
        }
    }
}
