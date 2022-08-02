using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab4_cyclycode_
{
    public static class st
    {
        public static int z = 0;
        public static int[] GetVector(int n, int[] pol, int r, int[]Yn)
        {
            int[] vec = new int[n];
            int[] Rx;
            int[] YnTemp=Yn;
            for (int i = 0; i < n; i++)
            {
                if (i == 0) vec[0] = 1;
                else vec[i] = 0;
            }
            Rx =GetXr(r, vec, pol);
            //return Rx;
            for (int i = 0; i < n; i++)
            {
                if (!sravnenie(Rx, GetXr(r, YnTemp, pol)))
                        YnTemp = plusnull(YnTemp);
                else
                {
                    vec[0] = 0;
                    vec[i] = 1;
                    break;
                }
            }
            return vec;
        }
        public static int[] plusnull(int[] YnTemp)
        {
            int[] res=new int[YnTemp.Length+1];
            for (int i = 0; i < res.Length - 1; i++ )
            {
                res[i] = YnTemp[i];
            }
            res[res.Length - 1] = 0;
            return res ;
        }

        public static bool sravnenie(int[] Rx, int[]sin)
            {
            if (Rx.Length != sin.Length)
                return false;
            for (int i = 0; i < Rx.Length; i++)
            {
                if (Rx[i] != sin[i])
                    return false;
                       
            }
            return true;
            }
        public static int GetWeight(int[]V)
        {
            int w = 0;
            for (int i = 0; i < V.Length; i++)
            {
                if (V[i] == 1)
                    w++;
            }
            return w;
        }

        public static int[] GetV(int[]Yn,int[] sin)
        {
            int[] V = new int[Yn.Length];
            for (int i = 0; i < Yn.Length; i++)
            {
                V[i] = 0; 
            }
            Array.Reverse(sin);
            for (int i = sin.Length - 1; i >= 0; i--)
            {
                V[Yn.Length - 1 - i] = sin[i];
            }
            return V;
        }
        public static int[] GetYFix(int[]Yn,int[]vec,int[] pol,int r)
        { //int[] sin;
           // int s = 0; 
            int[] YnFixed = Yn;
            int w = GetWeight(vec);
            if (w==1 || w==0)
            {
                for (int i = 0; i < Yn.Length; i++)
                {
                    YnFixed[i] = Yn[i] ^ vec[i];
                }
                return YnFixed;
            }

            return YnFixed;
        }
        public static int[] SdvigR(int[] Yn)
        {
            var tmp = Yn[Yn.Length - 1];
            for (var i = Yn.Length - 1; i != 0; --i) Yn[i] = Yn[i - 1];
            Yn[0] = tmp;
            return Yn;
        }
        public static int[] SdvigL(int[]Yn)
        {
            var tmp = Yn[0];

            for (var j =1; j <Yn.Length; j++)
            {
                Yn[j - 1] = Yn[j];
            }
            Yn[Yn.Length - 1] = tmp;
            return Yn;
        }
        public static int[,] MatrixG(int k, int r)
        {
            int[] Pol = st.GetP(r);
            int n = k + r;
            int[,] G = new int[k, n];
            for (int i = 0; i < k; i++)
            {
                int[] str = new int[n];
                    Array.Copy(Pol, 0, str, i, Pol.Length);
                for (int j = 0; j < n; j++)
                {
                  G[i,j]=str[j]  ;
                    Console.Write("{0} ",G[i, j]);
                }
                Console.WriteLine();
            }

            return G;
        }
        public static string getmas(this int[] mas)
        {
            if (mas == null)
            {
                return null;
            }
            else
            {
                string s = "";


                for (int i = 0; i < mas.Length; i++)
                {
                    s += (mas[i]).ToString();
                }
                return s;

            }
        }
        public static int NewMethod1(int[] xk) => xk.Length;
        public static int NewMethod(int[] xk)
        {
            int k = NewMethod1(xk);
            return (Int32)(Math.Ceiling(Math.Log10(k) / Math.Log10(2)) + 1);
        }
        public static int[] GetP(int r)
        {
            int[] Pol = new int[] { 1, 0, 0, 1, 0, 0, 1 };
            return Pol;
        }
        public static int[] GetXkmod(int[] Xk, int n)
        {
            int[] Xkmod = new int[n];
            Array.Copy(Xk, Xkmod, Xk.Length);
            for (int i = Xk.Length; i < n; i++) { Xkmod[i] = 0; }
            return Xkmod;
        }
        public static int[] Sdvig(int[] Xkmod)
        {
            int[] SXkmod;
            for (int i = 0; i < Xkmod.Length; i++)
            {
                if (Xkmod[i] == 1)
                {
                    SXkmod = new int[Xkmod.Length - i];
                    Array.Copy(Xkmod, i, SXkmod, 0, SXkmod.Length);
                    return SXkmod;
                }
            }
            return new int[] { 0 };
        }

        public static int[] GetXr(int r, int[] Xkmod, int[] Pol)
        {

            int[] Xr = new int[Xkmod.Length];
            Array.Copy(Xkmod, Xr, Xkmod.Length);
            while (Pol.Length <= Xr.Length)
            {
                for (int i = 0; i < Pol.Length; i++)
                {
                    Xr[i] = Xr[i] ^ Pol[i];
                }

                Xr = Sdvig(Xr);
            }


            return Xr;
        }
        public static int[] GetXn(int r, int[] Pol, int[] Xkmod, int n, int[] Xr)
        {
            int[] Xn = new int[n];

            Array.Copy(Xkmod, Xn, Xkmod.Length);
            Array.Reverse(Xr);
            for (int i = Xr.Length - 1; i >= 0; i--)
            {
                Xn[Xn.Length - 1 - i] = Xr[i];
            }
            return Xn;
        }

    }
}
