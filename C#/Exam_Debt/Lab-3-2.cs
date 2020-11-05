using System;

namespace LearningProg
{
    class Program
    {   // Лабораторная работа 2. Задание 2. Вариант 8
        public static bool GrafFunction(double x, double y, double R)
        {
            if (x >= 0)
            {
                if (Math.Sqrt(x * x + y * y) >= R) return false;
                else return true;
            }

            if (x < 0)
            {
                //double Cr = Math.Sqrt(R*R + R*R);
                double c = Math.Sqrt(x * x + y * y);
                double cY = Math.Asin(Math.Abs(y / c));

                if (Math.Tan(cY) >= 1 && y <= R && x <= R) return true;
            }
            return false;
        }
        static void Main(string[] args)
        {
            double R = 5;
            double[] x = new double [10];
            double[] y = new double [10];

            for (int i = 0; i < 10; i++)
            {
                Console.Write("Enter X: ");
                double.TryParse(Console.ReadLine(), out x[i]);
                Console.Write("Enter Y: ");
                double.TryParse(Console.ReadLine(), out y[i]);

            }

            Console.WriteLine("\t --Table of Hits--\n------------------------------\n   x\t\t| y\t\t| Hit/Miss");
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(i+1 + ") X = " + x[i] + "\t| Y = " + y[i] +" \t| " + GrafFunction(x[i], y[i], R) );
            }
        }
    }
}
