using System;

namespace KurWork2
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Попадание точки в заштрихованную область");
            double x, y;
            int R;
            Console.WriteLine("Введите радиус окружности:");
            bool result0 = int.TryParse(Console.ReadLine(), out R);
            Console.WriteLine("Координату Х:");
            bool result1 = double.TryParse(Console.ReadLine(), out x);
            Console.WriteLine("Координату Y:");
            bool result2 = double.TryParse(Console.ReadLine(), out y);
            if (result1 && result2 && result0)
            {
                if(   ((x <= R && x >= -R) && (y <= R && y >= -R))
                   && (( x >= 0 && (Math.Pow(R, 2) >= x*x + y*y))
                   || Math.Cos(45) <= ((x*x + Math.Sqrt(x*x+y*y) - y*y)/(2*Math.Sqrt(x * x + y * y)*x) ) ) )
                    {
                        Console.WriteLine("Заданная точка принадлежит данной области");
                    } 
                else
                    {
                        Console.WriteLine("Заданная точка не принадлежит данной области");
                    }
            }
            else
            {
                Console.WriteLine("ERROR! DATE INCORRECTLY ENTERED");
            }
        }
    }
}
