using System;

namespace lab6
{
    class BBS
    {
        private int p;
        private int q;
        private const int n = 256;
        private int x0;
        private int x;

        public BBS(int p, int q, int x)
        {
            if (p % 4 == 3 && q % 4 == 3)
            {
                this.p = p;
                this.q = q;
            }
            else
            {
                Console.WriteLine("Incorrect p and q");
                p = 11;
                q = 19;
            }
            if (IsCoprime(n, x))

                this.x = x;
            else
            {
                Console.WriteLine("Incorrect x");
                x = 3;
            }

            x0 = ((int)Math.Pow(x, 2)) % n;
        }

        public int ResultCurrentXvalue(int numberOfX)
        {
            int a = ((int)Math.Pow(2, numberOfX)) % n;
            return ((int)Math.Pow(x0, a)) % n;
        }


        private static bool IsCoprime(int num1, int num2)
        {
            if (num1 == num2)
            {
                return num1 == 1;
            }
            else
            {
                if (num1 > num2)
                {
                    return IsCoprime(num1 - num2, num2);
                }
                else
                {
                    return IsCoprime(num2 - num1, num1);
                }
            }
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("BBS:");
            BBS bbs = new BBS(11, 19, 3);
            Console.WriteLine(bbs.ResultCurrentXvalue(2));
            Console.WriteLine("===========");
            Console.WriteLine("RC4:");
            int[] K = { 123, 125, 41, 84, 203 };
            RC4(8, K);
        }

        static void RC4(int n, int[] K)
        {
            int[] S = new int[(int)Math.Pow(2, n)];
            int[] KTable = new int[S.Length];

            for (int i = 0; i < S.Length; i++)
            {
                S[i] = i;
            }

            for (int i = 0; i < KTable.Length; i++)
            {
                KTable[i] = K[i % K.Length];
            }

            for (int i = 0, j = 0; i < S.Length; i++)
            {
                j = (j + S[i] + KTable[i]) % S.Length;
                int save = S[i];
                S[i] = S[j];
                S[j] = save;
            }

            int[] result = new int[S.Length];

            for (int i = 0, j = 0, u = 0; u < S.Length; u++)
            {
                i = (i + 1) % S.Length;
                j = (j + S[i]) % S.Length;
                int save = S[i];
                S[i] = S[j];
                S[j] = save;
                int a = (S[i] + S[j]) % S.Length;
                result[i] = S[a];
            }

            for (int i = 0; i < result.Length; i++)
            {
                Console.WriteLine(GetBitByByte(result[i]));
            }

        }
        public static string GetBitByByte(int num)
        {
            string bit = "";
            for (int j = 8; j >= 0; j--)
                bit += num >> j & 1;
            return bit;
        }
    }
}