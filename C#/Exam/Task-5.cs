using KyrWordk3;
using System;

namespace KyrWordk3
{
    class Program
    {
        static void Main(string[] args)
        {
            const int N = 10;
            double sum = 0;
            double[] Array = new double[N]
                {88, 6, -0.3, 0.5, 0.9, -4, 3, 9, 2, 0.88 };
            double min = Array[0];
            bool result = true;

            for (int i = 0; i < N; i++)
            {
                if (Array[i] < min) min = Array[i];
                if (Array[i] < 0 && result)
                {
                    result = false;
                    if (i + 1 == N) continue;
                    for(int j = i + 1; Array[j] > 0; j++)
                    {                 
                        sum += Array[j];
                        if (j == N) break;
                    }
                }
            }

            Console.WriteLine("Min = " + min);
            Console.WriteLine("Сумма элементов между первым и вторым отрицательным числом = " + sum);

            int Voulum = 0;
            double temp;
            for (int i = 0; i < N; i++)
            {
                if(Array[i] <= 1 && Array[i] >= -1)
                {
                    temp = Array[Voulum];
                    Array[Voulum] = Array[i];
                    Array[i] = temp;
                    Voulum++;
                }
            }

            Console.WriteLine("Отсортированный массив: ");
            for (int i = 0; i < N; i++)
            {
                Console.WriteLine(Array[i]);
            }
        }
    }
}
