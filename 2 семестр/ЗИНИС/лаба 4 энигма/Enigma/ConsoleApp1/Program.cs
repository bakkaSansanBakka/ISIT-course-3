using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;


namespace ConsoleApp1
{
    class Enigma
    {
        //FSOKANUERHMBTIYCWLQPZXVGJD
        private string rotorLeft = "FSOKANUERHMBTIYCWLQPZXVGJD";
        private string rotorMedium = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
        private string rotorRight = "LEYJVCNIXWPBQMDRTAKZGFUHOS";
        private string reflector = "AFBVCPDJEIGOHYKRLZMXNWTQSU";
        private const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        private Random random = new Random();

        private string rotorPosition;
        public string RotorPosition 
        { 
            get => RotorPosition; 
            set => RotorPosition = value; 
        }

      
        public static string Shift(string s, int count)
        {
            return s.Remove(0, count) + s.Substring(0, count);
        }

        public void ChangeRotorposition()
        {
            rotorLeft = Shift(rotorLeft, random.Next(0, 25));
            rotorRight = Shift(rotorLeft, random.Next(0, 25));
            rotorMedium = Shift(rotorLeft, random.Next(0, 25));
        }
        public void ShowRotors()
        {
            Console.WriteLine("rotorLeft: "+rotorLeft);
            Console.WriteLine("rotorRight: " + rotorRight);
            Console.WriteLine("rotorMedium: " + rotorMedium);
        }


        public string EnigmaCrypt(string message)
        {
            char cryptedSymbol;
            int index = 0;
            int counterForRightRotor = 0;
            StringBuilder cryptedMessage = new StringBuilder(message.Length);
            for (int currentIndexOfMessage = 0; currentIndexOfMessage < message.Length; currentIndexOfMessage++)
            {
                cryptedSymbol = message[currentIndexOfMessage];
                index = alphabet.IndexOf(cryptedSymbol);          // from al
                
                cryptedSymbol = rotorRight[index];                // from rot 1
                index = alphabet.IndexOf(cryptedSymbol);


                cryptedSymbol = rotorMedium[index];               // from rot 2
                index = alphabet.IndexOf(cryptedSymbol);

                cryptedSymbol = rotorLeft[index];                 // from rot 3
                index = reflector.IndexOf(cryptedSymbol);     //from refl
               
                if((index+1)%2==0)
                {
                    cryptedSymbol = reflector[index-1];
                }
                else
                {
                    cryptedSymbol = reflector[index+1];
                }

                index = alphabet.IndexOf(cryptedSymbol);          // from rot 3
                cryptedSymbol = rotorLeft[index];

                index = alphabet.IndexOf(cryptedSymbol);
                cryptedSymbol = rotorLeft[index];

                cryptedSymbol = rotorMedium[index];               // from rot 2
                index = alphabet.IndexOf(cryptedSymbol);

                cryptedSymbol = rotorRight[index];                // from rot 1
                index = alphabet.IndexOf(cryptedSymbol);


                cryptedMessage.Append(cryptedSymbol);

                rotorRight = Shift(rotorRight,1);
                if ((currentIndexOfMessage + 1) % 26 == 0)
                {
                    rotorMedium = Shift(rotorMedium,1);
                    counterForRightRotor++;
                    if (counterForRightRotor % 26 == 0)
                        rotorLeft = Shift(rotorLeft,1);
                }
            }   
            return cryptedMessage.ToString();
        }
    }

  
    
    class Program
    {
        static void Main(string[] args)
        {
      
            string message = "Potapeyko Polina Pavlovna";
            while (!Regex.IsMatch(message, @"^[a-zA-Z ]+$"))
            {
                Console.Write("Only letters A-Z is allowed, try again: ");
                message = Console.ReadLine();
            }
            message = message.Replace(" ", "").ToUpper();
            Console.WriteLine("Message: " + message);

            Enigma enigma = new Enigma();
            enigma.ShowRotors();
            Console.WriteLine("Crypted message: " + enigma.EnigmaCrypt(message));
            Console.WriteLine("-----------------------------------------------");
            enigma.ChangeRotorposition();
            Console.WriteLine("Message: " + message);
            enigma.ShowRotors();
            Console.WriteLine("Crypted message: " + enigma.EnigmaCrypt(message));
            Console.WriteLine("-----------------------------------------------");
            enigma.ChangeRotorposition();
            Console.WriteLine("Message: " + message);
            enigma.ShowRotors();
            Console.WriteLine("Crypted message: " + enigma.EnigmaCrypt(message));
            Console.WriteLine("-----------------------------------------------");
            enigma.ChangeRotorposition();
            Console.WriteLine("Message: " + message);
            enigma.ShowRotors();
            Console.WriteLine("Crypted message: " + enigma.EnigmaCrypt(message));
            Console.WriteLine("-----------------------------------------------");
            enigma.ChangeRotorposition();
            Console.WriteLine("Message: " + message);
            enigma.ShowRotors();
            Console.WriteLine("Crypted message: " + enigma.EnigmaCrypt(message));

            Console.ReadLine();
        }
    }
}
