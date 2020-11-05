using System;

namespace LearningProg
{
    class Program
    {   // Лабораторная работа 2. Задание 1. Вариант 8
        public static double GrafFunction(double x, double R)
        {
            if(x >= -10 && x < -6)
            {
                double Y = Math.Sqrt(R * R - Math.Pow(x + (6 + R), 2)) - R;
                return Y;
            }
            
            if(x >= -6 && x <= 2)
            {
                double pX;
                if (x >= 0) pX = 8 + (x - 2);
                else pX = 6 + x;

                double cY = Math.Asin( (R + 2) / Math.Sqrt(64+Math.Pow(R+2,2)) );
                double Y = Math.Sin(cY) * pX / Math.Cos(cY);

                return Y - R;
            }

            if (x <= 8 && x > 6) return Math.Pow(x-6, 2);

            return 0;
        }
        static void Main(string[] args)
        {
            double Y = GrafFunction(-9, 2);

            Console.WriteLine( Y );
        }
    }
}
