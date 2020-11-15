using System;

namespace LearningProg
{   // Лабораторная работа 5. Вариант 8.
    class RandomArray
    {
        private double min;
        private int N;
        double[] rndArray;
        public RandomArray(int n)
        {
            N = n;
            Random rnd = new Random();
            rndArray = new double[N];

            for(int i = 0; i < N; i++)
            {
                rndArray[i] = rnd.NextDouble() * rnd.Next(-5, 5);
            }
        }
        public void show()
        {
            for (int i = 0; i < N; i++)
            {
                Console.WriteLine(i + 1 +") " + Math.Round(rndArray[i], 2) );
            }
        }
        public double[] GetArray()
        {
            return rndArray;
        }
        public double GetMinElement()
        {
            return min;
        }
        public int GetnumberMinElement()
        {
            return N;
        }
    }
    class Program
    {
        static void show(double [] Array, int N) 
        {
            for (int i = 0; i < N; i++)
            {
                Console.WriteLine(i + ") " + Math.Round(Array[i], 2));
            }
        }

        static int NumberMinElement(double [] Array, int N)
        {
            int nmin = 0;
            double min = Array[0];
            for(int i = 0; i < N; i++)
            {
                if (min > Array[i])
                {
                    min = Array[i];
                    nmin = i;
                }
            }
            return nmin;
        }

        static double Sum(double[] Array, int N)
        {
            double Sum = 0;
            bool flag = false;
            for(int i = 0; i < N; i++)
            {
                if (flag && Array[i] < 0) return Sum;
                if (flag) Sum += Array[i];
                if (Array[i] < 0) flag = true;
            }

            return Sum;
        }

        static void Sort(double[] Array, int N)
        {
            int count = 0;
            double temp;
            for (int i = 0; i < N; i++)
            {
                if (Array[i] <= 1 && Array[i] >= -1)
                {
                    temp = Array[count];
                    Array[count] = Array[i];
                    Array[i] = temp;
                    count++;
                }
            }
        }

        static void Main(string[] args)
        {
            int N = 10;
            RandomArray Obj = new RandomArray(N);
            double[] A = Obj.GetArray();
            Sort(A,N);

            show(A, N);
            Console.WriteLine("\n\n" + NumberMinElement(A, N) + "\n\n" + Math.Round(Sum(A,N), 2));
            
        }
    }
}
