using KyrWordk3;
using System;

namespace KyrWordk3
{
    class Program
    {
        static void Main(string[] args)
        {
            const int x = 6, y = 5;
            int[] Characteristic = new int[6] { 0, 0, 0, 0, 0, 0 };
            int[] Sum = new int[6] { 0, 0, 0, 0, 0, 0 };
            int[,] Array = new int[y, x]
            {
                {-1,  3,  -5,  7,   9,   2},
                {-2,  4,  6,   8,   10,  -3},
                {-43, 45, 34,  22,  4,   -5},
                {0,   3,  -6,  -88,  45,  2},
                {55,  32, 21,  33,  4,   1}
            };



            for (int i = 0; i < y; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    if (Array[i, j] % 2 != 0 && Array[i, j] < 0)
                    {
                        Characteristic[j] += Array[i, j];
                    }
                }
            }

            

            for (int i = 0; i < y; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    if (Characteristic[j] != 0) Sum[j] += Array[i, j];
                }
            }

            Console.WriteLine("Характеристики столбцов: ");
            for (int i = 0; i < x; i++) Console.Write(Characteristic[i] * (-1) + "\t");
            Console.WriteLine();

            Console.WriteLine("Сумма элементов в столбцах, где есть хоть одно отрицательное число:");
            for (int i = 0; i < x; i++) Console.Write(Sum[i] + "\t");
            Console.WriteLine();

            Console.WriteLine("Матрица: ");
            for (int i = 0; i < y; i++)
            {
                for (int j = 0; j < x; j++)
                {
                    Console.Write(Array[i, j] + "\t");
                }
                Console.WriteLine();
            }

        }
    }
}
