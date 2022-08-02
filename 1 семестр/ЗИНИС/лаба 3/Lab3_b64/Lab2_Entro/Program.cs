using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Задание 1-----------------------------------------------");
            string base64 = "";
            using (StreamReader streamReader = new StreamReader(@"..\..\..\english.txt"))
            {
                string file = streamReader.ReadToEnd();
                
                byte[] ascii = Encoding.ASCII.GetBytes(file);
                base64 = Convert.ToBase64String(ascii);
            }

            using (StreamWriter streamWriter = new StreamWriter(@"..\..\..\english_base64.txt", true, System.Text.Encoding.Default))
            {
                streamWriter.WriteLine(base64);
            }

            Console.WriteLine("Документ переведен в формат base64");

            Console.WriteLine("Задание 2-----------------------------------------------");
            Console.WriteLine("Исходный алфавит----------------------------------------");

            const int ENGLISHLETTERSAMOUNT = 26;
            int[] countLetter = new int[ENGLISHLETTERSAMOUNT];
            int countLettersInFile = 0;
            double[] probabilityLetters = new double[ENGLISHLETTERSAMOUNT];
            double entropyShannon = 0;
            double entropyChartly = 0;
            double alphabetRedundancy = 0;
            string alphabetLetters = "abcdefghijklmnopqrstuvwxyz";
            using (StreamReader streamReader = new StreamReader(@"..\..\..\english.txt"))
            {
                string file = streamReader.ReadToEnd().ToLower();
                countLettersInFile = file.Count();

                Console.WriteLine($"Количество символов в файле: {countLettersInFile}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой буквы:");

                for (int i = 0; i < ENGLISHLETTERSAMOUNT; i++)
                {
                    countLetter[i] = file.Count(x => x == alphabetLetters[i]);
                    Console.WriteLine($"{ alphabetLetters[i]}: { countLetter[i]}");

                    probabilityLetters[i] = (double)countLetter[i] / countLettersInFile;
                    Console.WriteLine($"P({alphabetLetters[i]}): {probabilityLetters[i]}");
                    Console.WriteLine();
                    if (countLetter[i] != 0)
                    {
                        entropyShannon += (-1) * probabilityLetters[i] * Math.Log(probabilityLetters[i], 2);
                    }
                }
            }

            Console.WriteLine("Энтропия английского алфавита по Шеннону:");
            Console.WriteLine(entropyShannon);

            entropyChartly = Math.Log(ENGLISHLETTERSAMOUNT, 2);
            Console.WriteLine("Энтропия английского алфавита по Хартли:");
            Console.WriteLine(entropyChartly);

            alphabetRedundancy = ((entropyChartly - entropyShannon) / entropyChartly) * 100;
            Console.WriteLine("Избыточность английского алфавита:");
            Console.WriteLine(Math.Round(alphabetRedundancy) + "%");


            Console.WriteLine("Base64------------------------------------------------------");

            const int BASE64SYMBOLSAMOUNT = 64;
            int[] countLetterInFile = new int[BASE64SYMBOLSAMOUNT];
            int allLettersInFileAmount = 0;
            double[] probabilityLettersBASE64 = new double[BASE64SYMBOLSAMOUNT];

            string base64Letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            using (StreamReader streamReader = new StreamReader(@"..\..\..\english_base64.txt"))
            {
                string file = streamReader.ReadToEnd().ToLower();
                allLettersInFileAmount = file.Count();

                Console.WriteLine($"Количество символов в файле: {allLettersInFileAmount}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой буквы:");

                for (int i = 0; i < 64; i++)
                {
                    countLetterInFile[i] = file.Count(x => x == base64Letters[i]);
                    Console.WriteLine($"{ base64Letters[i]}: { countLetterInFile[i]}");

                    probabilityLettersBASE64[i] = (double)countLetterInFile[i] / allLettersInFileAmount;
                    Console.WriteLine($"P({base64Letters[i]}): {probabilityLettersBASE64[i]}");
                    Console.WriteLine();
                    if (countLetterInFile[i] != 0)
                    {
                        entropyShannon += (-1) * probabilityLettersBASE64[i] * Math.Log(probabilityLettersBASE64[i], 2);
                    }

                }
            }

            Console.WriteLine("Энтропия base64 по Шеннону:");
            Console.WriteLine(entropyShannon);

            entropyChartly = Math.Log(BASE64SYMBOLSAMOUNT, 2);
            Console.WriteLine("Энтропия base64 по Хартли:");
            Console.WriteLine(entropyChartly);

            alphabetRedundancy = (entropyChartly - entropyShannon) / entropyChartly * 100;
            Console.WriteLine("Избыточность base64:");
            Console.WriteLine(Math.Abs(Math.Round(alphabetRedundancy)) + "%");


            Console.WriteLine("Задание 3-----------------------------------------------------------");

            string name = "Polina";
            string surname = "Potapeyko";

            buffersXOR(name, surname);

            Console.ReadLine();
        }

        public static void buffersXOR(string bufferOne, string bufferTwo)
        {
            byte[] asciiName = Encoding.ASCII.GetBytes(bufferOne);
            byte[] asciiSurname = Encoding.ASCII.GetBytes(bufferTwo);

            Console.WriteLine($"Входные данные: {bufferOne} {bufferTwo}");

            string base64Name;
            string base64Surname;

            byte[] newasciiName;
            byte[] newasciiSurname;

            Console.WriteLine("В кодах ASCII: \n");

            if (asciiName.Length < asciiSurname.Length)
            {
                newasciiSurname = asciiSurname;
                newasciiName = new byte[asciiSurname.Length];
                for (int i = 0; i < asciiName.Length; i++)
                {
                    newasciiName[i] = asciiName[i];
                    Console.Write(newasciiName[i] + " ");
                }
                for (int i = asciiName.Length; i < asciiSurname.Length; i++)
                {
                    newasciiName[asciiName.Length + 1] = 0;
                    Console.Write(newasciiName[i] + " ");
                }
                Console.WriteLine();
                for (int i = 0; i < asciiSurname.Length; i++)
                {
                    Console.Write(newasciiSurname[i] + " ");
                }

                base64Name = Convert.ToBase64String(newasciiName);
                base64Surname = Convert.ToBase64String(asciiSurname);

                Console.WriteLine($"\nВ формате base64: {base64Name} {base64Surname}");
            }
            else
            {
                newasciiName = asciiName;
                newasciiSurname = new byte[asciiName.Length];
                for (int i = 0; i < asciiSurname.Length; i++)
                {
                    newasciiSurname[i] = asciiSurname[i];
                    Console.WriteLine(newasciiSurname[i]);
                }
                for (int i = asciiSurname.Length; i < asciiName.Length; i++)
                {
                    newasciiSurname[asciiSurname.Length + 1] = 0;
                    Console.WriteLine(newasciiSurname[i]);
                }

                base64Name = Convert.ToBase64String(newasciiName);
                base64Surname = Convert.ToBase64String(asciiSurname);

                Console.WriteLine();
                Console.WriteLine($"В формате base64: {base64Name} {base64Surname}");
            }

            Console.WriteLine("\n\nРезультат логического сложения в ASCII:");
            int[] result = new int[newasciiName.Length];
            for (int i = 0; i < newasciiName.Length; i++)
            {
                result[i] = newasciiName[i] ^ newasciiSurname[i] ^ newasciiSurname[i];

                char ch = (char)result[i];
                Console.Write(ch);
            }
        }
    }
}
    