﻿using System.Numerics;
using System.Security.Cryptography;
using System.Text;

namespace lab10
{
    public static class Shnorr
    {
        public static BigInteger CalculateMd5Hash(string input)
        {
            var md5 = MD5.Create();
            var inputBytes = Encoding.ASCII.GetBytes(input);
            var hash = md5.ComputeHash(inputBytes);
            return new BigInteger(hash.Concat(new byte[] { 0 }).ToArray());
        }
        public static void Do()
        {
            BigInteger p = 2267;
            BigInteger q = 103;

            string text = File.ReadAllText(".\\Test.txt");
            BigInteger g = 354;
            BigInteger obg = 967;
            int x = 30;

            BigInteger y = BigInteger.ModPow(obg, x, p);
            BigInteger a = BigInteger.Pow(g, 13) % p;
            BigInteger hash = CalculateMd5Hash(text + a.ToString());
            Console.WriteLine("Encrypted Hash: " + hash);

            File.WriteAllText(".\\shnorr.txt", hash.ToString());
            BigInteger b = (13 + x * hash) % q;
            BigInteger dov = BigInteger.ModPow(g, b, p);
            BigInteger X = (dov * BigInteger.ModPow(y, hash, p)) % p;
            BigInteger hash2 = CalculateMd5Hash((text + X.ToString()));
            Console.WriteLine("Decrypted Hash: " + hash2);

            Console.WriteLine("Hash Veryfied = " + (hash == hash2));
        }
    }
}
