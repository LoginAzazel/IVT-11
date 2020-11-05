using System;

namespace LearningProg
{
    class Program
    {   // Лабораторная работа 2. Задание 2. Вариант 8
        public static bool GrafFunction(double x, double y, double R)
        {
            if( x >= 0 )
            {
                if (Math.Sqrt(x * x + y * y) >= R) return false;
                else return true;
            }

            if( x < 0 )
            {
                //double Cr = Math.Sqrt(R*R + R*R);
                double c = Math.Sqrt(x*x + y*y);
                double cY = Math.Asin(Math.Abs(y/c));

                if (Math.Tan(cY) >= 1 && y <= R && x <= R) return true;
            }
            return false;
        }
        static void Main(string[] args)
        {
            if( GrafFunction(-4, -2, 5) ) Console.WriteLine("Hit");
            else Console.WriteLine("Miss");
        }
    }
}
