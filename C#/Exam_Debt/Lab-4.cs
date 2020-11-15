using System;

namespace LearningProg
{   // Лабораторная работа 4. Вариант 8
    class Date
    {   
        private bool Veso = false;
        private int day = 0;
        private int mounth = 0;
        private int year = 0;
        private int[] DaysInMounth = new int[12]
            {31,28,31,30,31,30,31,31,30,31,30,31};

        public Date(int d, int m, int y)
        {
            DataValidation(d,m,y);
        }
        public Date()
        {
            day = 1;
            mounth = 1;
            year = 1;
        }
        private void DefiningALeapYear()
        {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            {
                Veso = true;
                DaysInMounth[1] = 29;
            }
            else
            {
                Veso = false;
                DaysInMounth[1] = 28;
            }
        }
        private void DataValidation(int d, int m, int y)
        {
            if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
            {
                Veso = true;
                DaysInMounth[1] = 29;
            }
            else
            {
                Veso = false;
                DaysInMounth[1] = 28;
            }

            if (m > 12) m = 12;
            if (m < 1) m = 1;

            if (d > DaysInMounth[m - 1]) d = DaysInMounth[m - 1];
            if (d < 1) d = 1;

            day = d;
            mounth = m;
            year = y;
        }
        public Date ChangeData(int d, int m, int y)
        {
            DataValidation(d, m, y);
            return this;
        }
        public Date SetDay(int d)
        {
            DataValidation(d,mounth,year);
            return this;
        }
        public Date SetMounth(int m)
        {
            DataValidation(day, m, year);
            return this;
        }
        public Date SetYear(int y)
        {
            DataValidation(day, mounth, y);
            return this;
        }

        public Date AddDay(int d)
        {
            while( day + d <= 0 )
            {
                if(mounth - 1 <= 0)
                {
                    year--;
                    DefiningALeapYear();
                    mounth = 13;
                }
                mounth--;
                day += DaysInMounth[mounth-1];
            }
            if (d < 0)
            {
                day += d;
                return this;
            }

            int T = day + d;
            while ( T > DaysInMounth[mounth - 1])
            {
                T -= DaysInMounth[mounth - 1];
                if (mounth + 1 > 12)
                {
                    year++;
                    DefiningALeapYear();
                    mounth = 0;
                }
                mounth++;
                if (T <= DaysInMounth[mounth - 1])
                {
                    day = T;
                    return this;
                }
            }

            day += d;
            return this;
        }
        public Date AddMounth(int m)
        {
            int T = mounth + m;
            while( T > 12 )
            {
                year++;
                DefiningALeapYear();
                T -= 12;
                if (T <= 12)
                {
                    mounth = T;
                    if (day > DaysInMounth[mounth - 1]) day = DaysInMounth[mounth - 1];
                    return this;
                }
            }
            while (T < 0)
            {
                year--;
                DefiningALeapYear();
                T += 12;
                if (T <= 12 && T > 0)
                {
                    mounth = T;
                    if (day > DaysInMounth[mounth - 1]) day = DaysInMounth[mounth - 1];
                    return this;
                }
            }

            mounth += m;
            if (day > DaysInMounth[mounth - 1]) day = DaysInMounth[mounth - 1];
            return this;
        }
        public Date AddYear(int y)
        {
            year += y;
            DefiningALeapYear();

            if (day > DaysInMounth[mounth-1]) day = DaysInMounth[mounth-1];

            return this;
        }
        public int GetDay()
        {
            return day;
        }
        public int GetMounth()
        {
            return mounth;
        }
        public int GetYear()
        {
            return year;
        }
        public bool GetVeso()
        {
            return Veso;
        }
        public void show()
        {
            Console.WriteLine(day + "." + mounth + "." + year);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Date A = new Date(29, 2, 2000);
            A.show();       // Создание и вывод в кнсоль экземпляра класса
            Console.WriteLine();

            A.AddDay(1);
            A.show();       // Увеличение значени экземпляра на 1 день
            Console.WriteLine();

            A.AddDay(-1);
            A.show();       // Уменьшение значения экземпляра на 1 день
            Console.WriteLine();

            A.AddDay(-60);
            A.show();       // Уменьшение значения даты экземпляра на 60 день, в следствии чего,
            Console.WriteLine();    // значение параметра "год" будет уменьшено на единицу


            A.ChangeData(31, 12, 1999); // Меняет дату у экземпляра класса

            A.AddMounth(2);
            A.show();       // Увеличение значения параметра "месяц" на 2, устанавливает дату
            Console.WriteLine();    // на февраль високосного года

            A.AddMounth(-12);
            A.show();       // Меняет дату ровно на год назад. При этом меняя значение високосности года
            Console.WriteLine();

            A.AddYear(1);   A.AddDay(1);
            A.show();       // Увеличение значения даты экземпляра на 1 год и меняет число с 28 на 29
            Console.WriteLine();    // Тем самым показывая, что год является високосным
        }
    }
}
