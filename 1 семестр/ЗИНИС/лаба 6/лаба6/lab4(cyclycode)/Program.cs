using System;
using System.Linq;

namespace lab4_cyclycode_ 
{
    class Program
    {
        static void Main(string[] args)
        {
            st.z = 0;
            //10010011010001101000100110111001
            Console.WriteLine("Введите слово:");
            int[] word = Console.ReadLine().ToCharArray().Select(x => x - '0').ToArray();
            int k = st.NewMethod1(word);
            Console.WriteLine(k);
            if (k == 32)
            {
                int r = st.NewMethod(word);
                int n = k + r;

                Console.WriteLine("Xk={0} k={1} r={2} n={3} Полином={4}", word.getmas(), k, r, n, st.GetP(r).getmas());
                Console.WriteLine("Xr={1}", st.GetXkmod(word, n).getmas(), st.GetXr(r, st.GetXkmod(word, n), st.GetP(r)).getmas());
                Console.WriteLine("Xn={0}", st.GetXn(r, st.GetP(r), st.GetXkmod(word, n), n, st.GetXr(r, st.GetXkmod(word, n), st.GetP(r))).getmas());

                Console.WriteLine("Отправляем:");

                int[] Yn = Console.ReadLine().ToCharArray().Select(x => x - '0').ToArray();
                //  Console.WriteLine(Yn.getmas());
                int[] sindrom = st.GetXr(r, Yn, st.GetP(r));
                Console.WriteLine("Синдром: {0} ", st.GetXr(r, Yn, st.GetP(r)).getmas());
                if (st.GetXr(r, Yn, st.GetP(r)).getmas() != "0")
                {
                    Console.WriteLine("E= {0} ", st.GetVector(n, st.GetP(r), r, Yn).getmas());
                    Console.WriteLine("Исправленное сообщение = {0} ", st.GetYFix(Yn, st.GetVector(n, st.GetP(r), r, Yn), st.GetP(r), r).getmas());
                }
                else
                {
                    Console.WriteLine("Сообщение = {0}", st.GetXn(r, st.GetP(r), st.GetXkmod(word, n), n, st.GetXr(r, st.GetXkmod(word, n), st.GetP(r))).getmas());
                }
            }
            else
            {
                Console.WriteLine("\nДлина не 32 ");
            }
            Console.ReadLine();
        }
    }
}

