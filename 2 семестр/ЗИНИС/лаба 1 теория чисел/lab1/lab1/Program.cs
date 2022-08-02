using System;

namespace lab1
{
    class Program
    {

        static void Main(string[] args)
        {
            Console.WriteLine("=== НОД чисел ===");
            Console.WriteLine("Введите количество чисел (2 или 3):");
            int x = Convert.ToInt32(Console.ReadLine());

            int num1, num2, num3;

            while (true)
            {
                if (x == 2 || x == 3)
                {
                    switch (x)
                    {
                        case 2:
                            Console.WriteLine("Введите первое число:");
                            num1 = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine("Введите второе число:");
                            num2 = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine($"НОД чисел равен: {NOD(num1, num2)}");
                            break;

                        case 3:
                            Console.WriteLine("Введите первое число:");
                            num1 = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine("Введите второе число:");
                            num2 = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine("Введите третье число:");
                            num3 = Convert.ToInt32(Console.ReadLine());
                            Console.WriteLine($"НОД чисел равен: {NOD(NOD(num1, num2), num3)}");
                            break;
                    }
                    break;
                }
                else
                {
                    Console.WriteLine("Некорректное количество, введите заново (2 или 3)");
                    x = Convert.ToInt32(Console.ReadLine());
                }
            }
            Console.WriteLine("=== Поиск простых чисел в заданном диапазоне ===");
            Console.Write("Введите левую границу диапазона: ");
            int m = Convert.ToInt32(Console.ReadLine());
            Console.Write("Введите правую границу диапазона: ");
            int n = Convert.ToInt32(Console.ReadLine());
            Console.Write("Найденные простые числа: ");
            SimpleNumber(m, n);
            Console.Write("\nНайденные простые числа в диапазоне [2,n]: ");
            SimpleNumber(2, n);

            Console.ReadLine();
        }

        static int NOD(int x, int y)
        {
            return y == 0 ? x : NOD(y, x % y);
        }

        static void SimpleNumber(int a, int b)
        {

            for (int i = a; i <= b; i++)
            {
                int cnt = 0;
                for (int j = 2; j <= i / 2; j++)
                {
                    if (i % j == 0)
                        cnt = 1;
                }
                if (cnt == 0)
                {
                    Console.Write(i + " ");
                }
            }
        }
    }
}
