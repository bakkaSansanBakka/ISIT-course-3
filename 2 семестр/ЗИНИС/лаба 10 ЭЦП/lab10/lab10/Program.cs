using System;
using System.Numerics;
using System.Security.Cryptography;
using System.Text;

namespace lab10
{
    class Program
    {
        static void Main(string[] args)
        {
            string messageString = "Potapeyko Polina";
            Console.WriteLine("Message: " + messageString);

            //хэшируем сообщение
            SHA512 shaM = new SHA512Managed();
            string messageHash = Encoding.UTF8.GetString(shaM.ComputeHash(Encoding.UTF8.GetBytes(messageString)));

            Console.WriteLine("RSA");
            //подписываем хешированное сообщение
            BigInteger message = new BigInteger(Encoding.UTF8.GetBytes(messageHash));

            RSA.GenerateKeys();
            BigInteger encryptedMessage = RSA.Encrypt(message);
            Console.WriteLine("Encrypted Hash: " + encryptedMessage.ToString());

            //дешифруем и сравниваем с хешем
            BigInteger decryptedMessage = RSA.Decrypt(encryptedMessage);
            Console.WriteLine("Decrypted Hash: " + decryptedMessage.ToString());

            //проверка подписи
            Console.WriteLine("Hash Veryfied = " + (messageHash == (Encoding.UTF8.GetString(decryptedMessage.ToByteArray()))));
            Console.WriteLine();

            Console.WriteLine("El Gamal");

            ElGamal elGamal = new ElGamal();

            string encryptedHash = elGamal.Encrypt(messageHash, "");
            Console.WriteLine("Encrypted Hash: " + encryptedHash);

            string decryptedHash = elGamal.Decrypt(encryptedHash, "privateKey.txt");
            Console.WriteLine("Decrypted Hash: " + decryptedHash);

            Console.WriteLine("Hash Veryfied = " + (messageHash == decryptedHash));

            Console.WriteLine();


            Console.WriteLine("Shnorr");

            Console.InputEncoding = Encoding.ASCII;
            Shnorr.Do();

            //Console.WriteLine("veryfied = " + (hash == hash3));


        }
    }
}
