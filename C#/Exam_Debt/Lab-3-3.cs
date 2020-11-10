using System;

namespace LearningProg
{
    class Program
    {   // Лабораторная работа 3. Задание 3. Вариант 8
        static void Main(string[] args)
        {
            double result, Cache = 1, preCache;
            double e = 0.0001;
            double x = 1.5;
            int i = 0;

            Console.WriteLine("N\t| arctg x\t|\tresult rad\t| result deg");
            Console.WriteLine("-------------------------------------------------------------");

            for (int j = 1; x <= 10; x += 0.5, j++)
            {
                result = Math.PI / 2;
                do
                {
                    preCache = Cache;
                    Cache = Math.Pow(-1, i + 1) / ((2 * i + 1) * Math.Pow(x, 2 * i + 1));
                    result += Cache;
                    i++;
                } while (Math.Abs(preCache - Cache) > e);
                Console.WriteLine(j + "\t| arctg " + x + "\t|\t" + Math.Round(result, 8) + "\t| " + Math.Round(result*180/Math.PI, 8));
                Cache = 1; i = 0;
            }
        }
    }
}
