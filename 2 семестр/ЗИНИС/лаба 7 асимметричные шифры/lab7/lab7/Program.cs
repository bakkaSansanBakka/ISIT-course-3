using System;
using System.Linq;
using System.Text;
using System.Numerics;
using System.Collections.Generic;

namespace Lab7
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger[] d = Vector100();
            BigInteger FullD = 0;

            for (int i = 0; i < d.Length; i++)
            {
                FullD += d[i];
            }

            string ns = "26525285981219105863630847123456";
            BigInteger n = BigInteger.Parse(ns);
            Console.WriteLine("n = " + n);

            BigInteger a = n - BigInteger.Parse("12112345678909876532356728901456");
            for (; a < n; a++)
            {
                if (NOD(a, n) == 1)
                {
                    break;
                }
            }
            Console.WriteLine("a = " + a);

            BigInteger[] e = new BigInteger[d.Length];
            Console.WriteLine("e = ");
            Console.Write("{");

            for (int i = 0; i < d.Length; i++)
            {
                e[i] = (d[i] * a) % n;
                Console.Write(e[i]);
                Console.Write(", ");
            }
            Console.Write("}");
            Console.WriteLine();

            string[] messageBit = toBin("Potapeyko Polina Pavlovna");
            BigInteger[] crypt = new BigInteger[messageBit.Length];
            Console.WriteLine();

            long ellapledTicks = DateTime.Now.Ticks;

            for (int i = 0; i < messageBit.Length; i++)
            {
                char[] b = messageBit[i].ToCharArray();
                for (int j = 0; j < b.Length; j++)
                {
                    crypt[i] += BigInteger.Parse(b[j].ToString()) * e[j];
                }
            }

            Console.WriteLine("encrypt:");
            foreach (var item in crypt)
            {
                Console.WriteLine(item);
            }

            ellapledTicks = DateTime.Now.Ticks - ellapledTicks;
            Console.WriteLine();
            Console.WriteLine("Encrypt time: " + ellapledTicks + " ticks");

            BigInteger moda = modInverse(a, n);
            Console.WriteLine();
            Console.WriteLine("a^(-1)= " + moda);

            BigInteger[] startEncrypt = new BigInteger[crypt.Length];
            long ellapledTicks2 = DateTime.Now.Ticks;

            for (int i = 0; i < crypt.Length; i++)
            {
                startEncrypt[i] = (crypt[i] * moda) % n;
            }

            string[] encrypt = new string[startEncrypt.Length];
            for (int i = 0; i < startEncrypt.Length; i++)
            {
                string currentWord = "";
                BigInteger toNull = startEncrypt[i];

                for (int j = d.Length - 1; j >= 0; j--)
                {

                    if (toNull >= d[j])
                    {
                        toNull -= d[j];
                        currentWord += "1";
                    }
                    else
                    {
                        currentWord += "0";
                    }

                }
                encrypt[i] = new string(currentWord.ToCharArray().Reverse().ToArray());
            }

            ellapledTicks2 = DateTime.Now.Ticks - ellapledTicks2;

            string bicaryEncrypt = "";
            for (int i = 0; i < encrypt.Length; i++)
            {
                bicaryEncrypt += encrypt[i];
            }

            string dec = "";
            for (int i = 0; i < bicaryEncrypt.Length / 8; i++)
            {
                string array = bicaryEncrypt.Substring(i * 8, 8);
                int intchar = 0;
                for (int j = array.Length - 1; j >= 0; j--)
                {
                    intchar += Int32.Parse(array[j].ToString()) * (int)Math.Pow(2, array.Length - 1 - j);
                }
                dec += Convert.ToChar(intchar);
            }

            Console.WriteLine();
            Console.WriteLine("Decrypt:");
            Console.WriteLine(dec);
            Console.WriteLine();
            Console.WriteLine("Decrypt time: " + ellapledTicks2 + " ticks");

        }

        public static BigInteger modInverse(BigInteger a, BigInteger n)
        {
            BigInteger i = n, v = 0, d = 1;
            while (a > 0)
            {
                BigInteger t = i / a, x = a;
                a = i % x;
                i = x;
                x = d;
                d = v - t * x;
                v = x;
            }
            v %= n;
            if (v < 0) v = (v + n) % n;
            return v;
        }

        static BigInteger[] Vector100()
        {
            Random rnd = new Random();
            BigInteger[] mass = new BigInteger[8];
            mass[0] = rnd.Next(1, 9);
            Console.WriteLine("d = ");
            Console.Write("{" + mass[0]);
            for (int i = 1; i < 8; i++)
            {
                Console.Write(", ");
                for (int j = 0; j < mass.Length; j++)
                {
                    BigInteger coef = rnd.Next(70, 150);
                    mass[i] += mass[j] * coef;

                }

                Console.Write(mass[i]);
            }
            Console.WriteLine("}");
            return mass;
        }

        static string[] toBin(string str)
        {
            string[] result = new string[str.Length];

            Console.WriteLine("FIO:" + str);

            for (int i = 0; i < str.Length; i++)
            {
                string bit = "";
                for (int j = 7; j >= 0; j--)
                    bit += str[i] >> j & 1;
                result[i] = bit;
            }

            return result;
        }

        static BigInteger NOD(BigInteger x, BigInteger y)
        {
            while (x != 0 && y != 0)
            {
                if (x > y)
                    x = x % y;
                else
                    y = y % x;
            }
            return (x + y);
        }
    }
}
