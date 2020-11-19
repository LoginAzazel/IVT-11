using System;

namespace LearningProg
{   // Лабораторная работа 6. Вариант 8.
    class RandomArray
    {   
        private int N, M;
        int[,] rndArray;
        int[] Characteristic, Temp, Sum;
        public RandomArray(int n, int m)
        {
            N = n;  M = m;
            Random rnd = new Random();
            rndArray = new int[N,M];
            
            for(int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                {
                    rndArray[i,j] = rnd.Next(-10, 25);
                }
            CreateCharacteristic();
        }

        private void CreateCharacteristic()
        {
            Characteristic = new int[M];

            for (int i = 0; i < M; i++)
            {
                Characteristic[i] = 0;
                for (int j = 0; j < N; j++)
                {
                    if (rndArray[j, i] < 0 && rndArray[j, i] % 2 != 0) Characteristic[i] += rndArray[j, i];
                }
            }
        }

        public void Sort()
        {
            Temp = new int[N];
            int min = Characteristic[0], cTemp;

            for (int n = 0; n < M; n++)
                for (int k = n; k < M; k++)
                {
                    if (Characteristic[n] > Characteristic[k])
                    {
                        cTemp = Characteristic[n];
                        Characteristic[n] = Characteristic[k];
                        Characteristic[k] = cTemp;
                            for (int j = 0; j < N; j++)
                            {
                                Temp[j] = rndArray[j, n];
                                rndArray[j, n] = rndArray[j, k];
                                rndArray[j, k] = Temp[j];
                            }
                    }
                }
        }

        public void SumColumn()
        {
            Sum = new int [M];
            for (int i = 0; i < M; i++)
            {
                Sum[i] = 0;
                for (int j = 0; j < N; j++)
                {
                    if (rndArray[j, i] < 0)
                    {
                        for (int k = 0; k < N; k++)
                        {
                            Sum[i] += rndArray[k,i];
                        }
                        break;
                    }
                }
            }
        }

        public void show()
        {
            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < M; j++)
                {
                    Console.Write("\t" + rndArray[i, j], 2);
                }
                Console.WriteLine();
            }
        }

        public void showCharactiristic()
        {
            Console.WriteLine();
            for (int i = 0; i < M; i++) Console.Write("\t" + Characteristic[i]);
            Console.WriteLine();
        }

        public void showSum()
        {
            Console.WriteLine();
            for (int i = 0; i < M; i++) Console.Write("\t" + Sum[i]);
        }
        public int[] GetCharactiristic()
        {
            return Characteristic;
        }
        public int[,] GetArray()
        {
            return rndArray;
        }
        
        public int GetMinElement()
        {
            int nmin = 0;
            int min = rndArray[0,0];
            for (int i = 0; i < N; i++)
                for (int j = 0; j < M; j++)
                {
                if (min > rndArray[i,j])
                {
                    min = rndArray[i,j];
                    nmin = i;
                }
            }
            return min;
        }
    }
    class Program
    {  
        static void Main(string[] args)
        {
            int N = 5, M = 10;
            RandomArray array = new RandomArray(N,M);

            Console.WriteLine(" Изначальный массив:");
            array.show();   // Вывод на экран неотсортированного, рандомносгенерированного двумерного массива 
            Console.WriteLine(" Характеристика:");    //  с характеристиками по столбцам
            array.showCharactiristic();

            array.Sort();

            Console.WriteLine("\n\n Отсортированный массив:");
            array.show();   // Вывод на экран отсортированнного по характеристикам массива
            Console.WriteLine(" Характеристика:");
            array.showCharactiristic();

            Console.WriteLine(" Сумма столбцов с отрицательными членами:");
            array.SumColumn();
            array.showSum();
        }
    }
}
