using System;

namespace LearningProg
{   // Лабораторная работа 10. Вариант 8.
    struct Train
    {
        public string nameStaition;
        public int trainNumber;
        private DateTime DepartureTime;

        public Train(int trainnumber, string namestation, int hour, int minute)
        {
            DateTime time = new DateTime(2000,1,1, hour, minute, 0);
            nameStaition = namestation;
            trainNumber = trainnumber;
            DepartureTime = time;
        }

        public void show()
        {
            Console.WriteLine($"Train Number: {trainNumber}\nName station: {nameStaition}\nDeparture Time: {DepartureTime.ToShortTimeString()}");
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            int Num;
            int N = 2;
            Train[] train = new Train[N];

            for (int i = 0; i < N; i++ )
            {
                Console.Write("Номер поезда: "); 
                if( !int.TryParse(Console.ReadLine(), out Num) )
                {
                    i--;
                    Console.WriteLine("Недопустимый вариант записи номера");
                    continue;
                }
                Console.Write("Название пункта назначения: "); string Station = Console.ReadLine();
                Console.Write("Дата отправки (Часы)/(Минуты): "); 
                int h = Convert.ToInt32(Console.ReadLine()); 
                int m = Convert.ToInt32(Console.ReadLine());
                if( !(h >= 0 && h < 24 && m >= 0 && m <= 60) )
                {
                    i--;
                    Console.WriteLine("Формат времени введен неверно");
                    continue;
                }
                train[i] = new Train(Num, Station, h, m);
            }

            Console.Write("Введите название станции: ");
            string tempStationName = Console.ReadLine();
            Console.WriteLine("Поезда прибывающие к станции: ");
            bool flag = false;
            for (int i = 0; i < N; i++)
            {
                if (train[i].nameStaition == tempStationName)
                {
                    flag = true;
                    train[i].show();
                    Console.WriteLine();
                }
            }
            if (!flag) Console.WriteLine("Отсутствуют");
        }
    }
}
