using KyrWordk3;
using System;

namespace KyrWordk3
{
    class Date
    {
        bool Veso = false;
        private int day = 0;
        private int mounth = 0;
        private int year = 0;
        private int[] DaysInMounth = new int[12]
            {31,28,31,30,31,30,31,31,30,31,30,31};
        public Date(int d, int m, int y)
        {
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) Veso = true;
            else Veso = false;

            if (m > 0 && m <= 12 && ((DaysInMounth[m - 1] >= d && 0 < d) || (m == 2) && (Veso == true) && (29 >= d)))
            {
                day = d;
                mounth = m;
                year = y;
            } 
            else
            {
                Veso = false;
                Console.WriteLine("Error! Entered Data incorrectly");
            }
        }
        public bool ChangeData(int d, int m, int y)
        {
            if (m == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) Veso = true;
            else Veso = false;
            if (m > 0 && m <= 12 && ((DaysInMounth[m-1] >= d && 0 < d) || (m == 2) && (Veso == true) && (29 >= d)))
            {
                day = d;
                mounth = m;
                year = y;
                return true;
            }
            return false;
        }
        public bool SetDay(int d)
        {
            if (DaysInMounth[mounth - 1] >= d && 0 < d || (mounth == 2) && (Veso == true) && (29 >= d))
            {
                day = d;
                return true;
            }
            return false;
        }
        public bool SetMounth(int m)
        {
            if (m > 0 && m <= 12)
            {
                mounth = m;
                return true;
            }
            return false;
        }
        public bool SetYear(int y)
        {
            if (mounth == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) Veso = true;
            else Veso = false;
            year = y;
            return true;
        }

        public bool AddDay(int d)
        {
            day += d;
            while (day > DaysInMounth[mounth - 1] && Veso == false || mounth == 2 && Veso == true && day > 29 || (day > DaysInMounth[mounth - 1] && Veso == true && mounth != 2))
            {
                if (Veso == true && mounth == 2)
                    day -= 29;
                else
                { 
                    day -= DaysInMounth[mounth - 1];
                }
                mounth++;
                    if( mounth > 12 )
                    {
                        year++;
                    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) Veso = true;
                    else Veso = false;
                    mounth = 1;
                    }
            }
            return true;
        }
        public bool AddMounth(int m)
        {
            mounth += m;
            if (mounth > 12)
            {
                year++;
                if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) Veso = true;
                else Veso = false;
                mounth = 1;
            }
            return false;
        }
        public bool AddYear(int y)
        {
            year += y;
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) Veso = true;
            else Veso = false;
            return false;
        }
        public void show()
        {
            Console.WriteLine(day+"."+mounth+"."+year);
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Date A = new Date (31,12,2007);
            A.show();
            A.AddDay(61);
            A.show();
        }
    }
}
