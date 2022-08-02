using System;
using System.Collections.Generic;
using System.Linq;
using System.Numerics;

namespace lab8
{
    class Program
    {
        static void Main(string[] args)
        {
            BigInteger p = BigInteger.Parse("6788923193742832419212371231");
            BigInteger q = BigInteger.Parse("3902847768726378127361823571");

            Console.WriteLine("=============RSA=============\n");
            Console.WriteLine("p = " + p);
            Console.WriteLine("q = " + q);
            string Message = "Potapeyko Polina Pavlovna";

            RSA(p, q, Message);
            Console.WriteLine();

            Console.WriteLine("=============El-Gamal=============\n");
            ElGamal(5935711, Message);
        }

        static void RSA(BigInteger p, BigInteger q, string Message)
        {
            Random rand = new Random();
            BigInteger n = p * q;
            Console.WriteLine("n = " + n);

            BigInteger e = q * p / rand.Next(1, 19);
            for (; e > 0; e--)
            {
                if (NOD(e, (p - 1) * (q - 1)) == 1)
                {
                    break;
                }
            }
            Console.WriteLine("e = " + e);

            BigInteger d = modInverse(e, (p - 1) * (q - 1));
            Console.WriteLine("d = " + d);

            string[] SplitMessage = Message.Split(' ');
            List<BigInteger> BlockMessage = new List<BigInteger>();

            for (int i = 0; i < SplitMessage.Length; i++)
            {
                BlockMessage.Add(0);
                for (int j = 0; j < SplitMessage[i].Length; j++)
                {
                    BlockMessage[i] += Convert.ToInt32(SplitMessage[i][j]);

                    if (j != SplitMessage[i].Length - 1)
                    {
                        BlockMessage[i] *= 1000;
                    }
                }
            }

            Console.WriteLine("\nMessage");
            foreach (var item in BlockMessage)
            {
                Console.WriteLine(item);
            }

            List<BigInteger> encryptArray = new List<BigInteger>();
            long ellapledTicks = DateTime.Now.Ticks;

            Console.WriteLine("\nEncrypt:");
            foreach (var item in BlockMessage)
            {
                encryptArray.Add(BigInteger.ModPow(item, e, n));
                Console.WriteLine(encryptArray[encryptArray.Count - 1]);
            }

            ellapledTicks = DateTime.Now.Ticks - ellapledTicks;
            Console.WriteLine();
            Console.WriteLine("Ecrypt time: " + ellapledTicks + " ticks");

            List<BigInteger> decryptArray = new List<BigInteger>();
            ellapledTicks = DateTime.Now.Ticks;

            foreach (var item in encryptArray)
            {
                decryptArray.Add(BigInteger.ModPow(item, d, n));
            }

            Console.WriteLine("\nDecrypt:");
            string stringDecryptMessage = "";
            for (int i = 0; i < decryptArray.Count; i++)
            {
                stringDecryptMessage += Convert.ToChar(Convert.ToInt32(decryptArray[i].ToString().Substring(0, decryptArray[i].ToString().Length % 3)));

                for (int j = decryptArray[i].ToString().Length % 3; j < decryptArray[i].ToString().Length; j += 3)
                {
                    stringDecryptMessage += Convert.ToChar(Convert.ToInt32(decryptArray[i].ToString().Substring(j, 3)));
                }

                stringDecryptMessage += " ";
            }
            Console.WriteLine(stringDecryptMessage);

            ellapledTicks = DateTime.Now.Ticks - ellapledTicks;
            Console.WriteLine();
            Console.WriteLine("Decryption time: " + ellapledTicks + " ticks");
        }

        public static void ElGamal(BigInteger p, string Message)
        {
            var rand = new Random();

            BigInteger g = p - rand.Next() % p;
            for (; g > 0; g--)
            {
                if (IsPRoot(g, p))
                    break;
            }
            BigInteger x = rand.Next() % p;

            var encrypt = "";
            var y = BigInteger.ModPow(g, x, p);

            Console.WriteLine("p = " + p);
            Console.WriteLine("g = " + g);
            Console.WriteLine("x = " + x);
            Console.WriteLine("y = " + y);

            long ellapledTicks = DateTime.Now.Ticks;

            foreach (int code in Message)
                if (code > 0)
                {
                    var k = rand.Next() % (p - 2) + 1;
                    var a = BigInteger.ModPow(g, k, p);
                    var b = BigInteger.ModPow(BigInteger.ModPow(y, k, p) * code, 1, p);
                    encrypt += a + " " + b + " ";
                }

            Console.WriteLine("Encrypt:" + encrypt);

            ellapledTicks = DateTime.Now.Ticks - ellapledTicks;
            Console.WriteLine();
            Console.WriteLine("Ecrypt time: " + ellapledTicks + " ticks\n");

            ellapledTicks = DateTime.Now.Ticks;

            var decrypt = "";
            var arr = encrypt.Split(' ').Where(xx => xx != "").ToArray();
            for (var i = 0; i < arr.Length; i += 2)
            {
                BigInteger a = BigInteger.Parse(arr[i]);
                BigInteger b = BigInteger.Parse(arr[i + 1]);

                if (a != 0 && b != 0)
                {
                    var deM = BigInteger.ModPow(b * BigInteger.ModPow(a, p - 1 - x, p), 1, p);
                    // m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p - т
                    var m = (char)deM;
                    decrypt += m;
                }
            }
            Console.WriteLine("Decrypt:" + decrypt);

            ellapledTicks = DateTime.Now.Ticks - ellapledTicks;
            Console.WriteLine();
            Console.WriteLine("Decrypt time: " + ellapledTicks + " ticks");
        }

        public static bool IsPRoot(BigInteger g, BigInteger n)
        {
            if (NOD(g, n) != 1)
                return false;

            if (BigInteger.ModPow(g, Euler(n) / 2, n) == 1)
                return false;

            List<BigInteger> factorisation = PrimeFactorization(g);

            foreach (var item in factorisation)
            {
                if (BigInteger.ModPow(g, item, n) == 1)
                    return false;
            }

            return true;
        }

        public static List<BigInteger> PrimeFactorization(BigInteger N)
        {
            List<BigInteger> result = new List<BigInteger>();
            for (int i = 0; N % 2 == 0; N /= 2)
            {
                result.Add(2);
            }
            for (int i = 3; i <= N;)
            {
                if (N % i == 0)
                {
                    result.Add(i);
                    N /= i;
                }
                else
                {
                    i += 2;
                }
            }
            return result;
        }

        public static BigInteger Euler(BigInteger n)
        {
            BigInteger result = n;
            for (int i = 2; i * i <= n; ++i)
                if (n % i == 0)
                {
                    while (n % i == 0)
                        n /= i;
                    result -= result / i;
                }
            if (n > 1)
                result -= result / n;
            return result;
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

        public static string GetBitByByte(int num)
        {
            string bit = "";
            for (int j = 8; j >= 0; j--)
                bit += num >> j & 1;
            return bit;
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
