using System;
using System.IO;
using System.Linq;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            double russian = 0;
            double binary = 0;
            Console.WriteLine("Задание а------------------------------------------------");
                        
            int[] countLetter1 = new int[33];
            int countLettersInFile1;
            double[] probabilityLetters1 = new double[33];

            string letters1 = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
            using (StreamReader streamReader = new StreamReader(@"..\..\..\..\russian.txt"))
            {
                string file1 = streamReader.ReadToEnd().ToLower();
                countLettersInFile1 = file1.Count();

                Console.WriteLine($"Количество символов в файле: {countLettersInFile1}\n");
                Console.WriteLine("Количество вхождений каждой буквы:");

                for (int i = 0; i < 33; i++)
                {
                    countLetter1[i] = file1.Count(x => x == letters1[i]);
                    Console.WriteLine($"{ letters1[i]}: { countLetter1[i]}");

                    probabilityLetters1[i] = (double)countLetter1[i] / countLettersInFile1;
                    Console.WriteLine($"P({letters1[i]}): {probabilityLetters1[i]}");
                    Console.WriteLine();
                    if (countLetter1[i] != 0)
                    {
                        russian += (-1) * probabilityLetters1[i] * Math.Log(probabilityLetters1[i], 2);
                    }
                }
                Console.WriteLine($"Энтропия русского алфавита: {russian}");
            }

            Console.WriteLine("\nЗадание б --------------------------------------------------");

            int[] countLetter2 = new int[2];
            int countLettersInFile2 = 0;
            double[] probabilityLetters2 = new double[2];

            string letters3 = "01";
            using (StreamReader streamReader = new StreamReader(@"..\..\..\..\binary.txt"))
            {
                string file2 = streamReader.ReadToEnd();
                countLettersInFile2 = file2.Count();
                Console.WriteLine($"Количество символов в файле: {countLettersInFile2}");
                Console.WriteLine();
                Console.WriteLine("Количество вхождений каждой цифры:");

                for (int j = 0; j < 2; j++)
                {
                    countLetter2[j] = file2.Count(x => x == letters3[j]);
                    Console.WriteLine($"{ letters3[j]}: { countLetter2[j]}");

                    probabilityLetters2[j] = (double)countLetter2[j] / countLettersInFile2;
                    Console.WriteLine($"P({letters3[j]}): {probabilityLetters2[j]}");
                    Console.WriteLine();

                    binary += (probabilityLetters2[j] * Math.Log(probabilityLetters2[j], 2) * (-1));

                }
                Console.WriteLine($"Энтропия бинарного алфавита: {binary}");
            }

            Console.WriteLine("\nЗадание в ----------------------------------------------------------");

            Console.WriteLine("Введите ФИО: ");
            string FIO = Console.ReadLine();

            double countRussianInformation = russian * FIO.Replace(" ", "").ToLower().Count();

            Console.WriteLine("Количество информации в сообщении с использованием энтропии русского алфавита:");
            Console.WriteLine(countRussianInformation);

            Console.WriteLine();
            double ascii = FIO.ToLower().Count() * 8;

            Console.WriteLine();
            Console.WriteLine("Количество информации в сообщении с использованием ASCII для бинарного алфавита:");
            double ASСIIbinaryInformation = ascii * binary;
            Console.WriteLine(ASСIIbinaryInformation);

            Console.WriteLine("\nЗадание г ---------------------------------------------------");

            Console.WriteLine("Расчет количества информации в сообщении с вероятностью ошибки (в кодах ASCII)");

            double p = 0.1;
            double q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 0.1");
            double conditionalEntropyBinary = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            double effectiveEntropyBinary = binary - conditionalEntropyBinary;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            double countBinaryInformation = effectiveEntropyBinary * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 0.1 с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();

            p = 0.5;
            q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 0.5");
            conditionalEntropyBinary = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            effectiveEntropyBinary = Math.Abs(binary - conditionalEntropyBinary);
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            countBinaryInformation = effectiveEntropyBinary * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 0.5 с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();


            p = 1.0;
            q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 1.0");
            conditionalEntropyBinary = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyBinary}");
            conditionalEntropyBinary = binary - conditionalEntropyBinary;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyBinary}");
            Console.WriteLine("Информация полностью ошибочна");
            countBinaryInformation = effectiveEntropyBinary * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 1.0 с использованием энтропии бинарного алфавита:");
            Console.WriteLine(countBinaryInformation);
            Console.WriteLine();

            Console.WriteLine("Расчет количества информации в сообщении с вероятностью ошибки (исходный алфавит)");

            p = 0.1;
            q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 0.1");
            double conditionalEntropyRussian = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyRussian}");
            double effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyRussian}");
            countRussianInformation = effectiveEntropyRussian * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 0.1 с использованием энтропии исходного алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();

            p = 0.5;
            q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 0.5");
            conditionalEntropyRussian = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyRussian}");
            effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyRussian}");
            countRussianInformation = effectiveEntropyRussian * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 0.5 с использованием энтропии исходного алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();

            p = 1.0;
            q = 1 - p;
            Console.WriteLine("Вероятность ошибочной передачи = 1.0");
            conditionalEntropyRussian = -p * Math.Log(p, 2) - q * Math.Log(q, 2);
            Console.WriteLine($"Условная энтропия = {conditionalEntropyRussian}");
            effectiveEntropyRussian = russian - conditionalEntropyRussian;
            Console.WriteLine($"Эффективная энтропия = {effectiveEntropyRussian}");
            Console.WriteLine("Информация полностью ошибочна");
            countRussianInformation = effectiveEntropyRussian * FIO.Replace(" ", "").ToLower().Count();
            Console.WriteLine("Количество эффективной информации в сообщении с вероятносью ошибки 1.0 с использованием энтропии исходного алфавита:");
            Console.WriteLine(countRussianInformation);
            Console.WriteLine();
        }
    }
}
