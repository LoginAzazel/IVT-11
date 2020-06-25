using System;

namespace KyrWordk3
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Серия выстрелов по мишени:");
            Console.WriteLine("Попадание точки в заштрихованную область");
            double x, y;
            int R;
            Console.WriteLine("Введите радиус мишени:");
            bool result0 = int.TryParse(Console.ReadLine(), out R);
            bool [] Target = new bool [10]; 

            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine("Координату Х:");
                bool result1 = double.TryParse(Console.ReadLine(), out x);
                Console.WriteLine("Координату Y:");
                bool result2 = double.TryParse(Console.ReadLine(), out y);
                if (result1 && result2 && result0)
                {
                    if (((x <= R && x >= -R) && (y <= R && y >= -R))
                       && ((x >= 0 && (Math.Pow(R, 2) >= x * x + y * y))
                       || Math.Cos(45) <= ((x * x + Math.Sqrt(x * x + y * y) - y * y) / (2 * Math.Sqrt(x * x + y * y) * x))))
                    {
                        Target[i] = true;
                    }
                    else
                    {
                        Target[i] = false;
                    }
                }
                else
                {
                    Console.WriteLine("Данные введены неверно");
                    Target[i] = false;
                }
            }

            Console.WriteLine(" Количество попаданий по мишени:");
            for (int i = 0; i < 10; i++)
            {
                Console.WriteLine(i + " | " + Target[i]);
            }
        }
    }
}
