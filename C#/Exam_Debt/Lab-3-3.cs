using System;

namespace LearningProg
{
    class Program
    {   // Лабораторная работа 3. Задание 3. Вариант 8
            static void Main(string[] args)
            {
                double result;
                int E = 22;
                double x = 1.5;

                Console.WriteLine("N" + "\t| arctg x\t|\tresult");
                Console.WriteLine("---------------------------------------");
                for (int j = 1; x <= 10; x += 0.5, j++)
                {
                    result = 3.14 / 2;
                    for (int i = 0; i < E; i++)
                    {
                        result += Math.Pow(-1, i + 1) / ((2 * i + 1) * Math.Pow(x, 2 * i + 1));
                    }
                    Console.WriteLine(j + "\t| arctg " + x + "\t=\t" + Math.Round(result, 5));
                }
            }
    }
}
