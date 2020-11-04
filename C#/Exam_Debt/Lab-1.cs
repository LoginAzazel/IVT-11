using System;

namespace KurWork1
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Линейные программы");
            double z1, z2;
            double x, y;

            bool result1 = double.TryParse(Console.ReadLine(), out x);
            bool result2 = double.TryParse(Console.ReadLine(), out y);
            if (result1 && result2)
            {
                z1 = Math.Pow(Math.Cos(x), 4) + Math.Pow(Math.Sin(y), 2) + Math.Pow(Math.Sin(2 * x), 2)/4 - 1;
                z2 = Math.Sin(y + x) * Math.Sin(y - x);
                Console.WriteLine( Math.Round(z1, 4) + " == " + Math.Round(z2, 4));
            }
            else
            {
                Console.WriteLine("ERROR! DATE INCORRECTLY ENTERED");
            }
        }
    }
}
