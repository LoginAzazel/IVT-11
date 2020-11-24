using System;

namespace LearningProg
{   // Лабораторная работа 9. Вариант 8. Задание 2.
        // (Вариант 8) mod (Всего заданий 6) = 2-ое задание

    public abstract class Vehicle
    {
        public double CoordinateX { get; set; }
        public double CoordinateY { get; set; }
        public double Price { get; set; }
        public double Speed { get; set; }
        public int Year_of_construction { get; set; }

        public void Coordinate(double CoordinateX, double CoordinateY)
        {
            this.CoordinateX = CoordinateX;
            this.CoordinateY = CoordinateY;
        }

        public void ChangeSpeed(double speed)
        {
            Speed = speed;
        }
    }

    class Plane : Vehicle
    {
        private double Height = 0;
        private int NumberOfPassengers = 0;
        public Plane(double prise, int year_of_construction)
        {
            Price = prise;
            Year_of_construction = year_of_construction;
        }

        public void ChangeHeight( double height)
        {
            Height = height;
        }

        public void ChangeNumOfPassengers(int passengers)
        {
            NumberOfPassengers = passengers;
        }

        public Plane Clone()
        {
            var VehicleClone = new Plane(Price, Year_of_construction);
            VehicleClone.Price = Price;
            VehicleClone.Year_of_construction = Year_of_construction;
            VehicleClone.Height = Height;
            VehicleClone.NumberOfPassengers = NumberOfPassengers;
            return VehicleClone;
        }

        public void show()
        {
            Console.WriteLine($"\tPrise\tYear of construction\tHeight\tNumber of Passengers");
            Console.WriteLine($"\t{Price}\t\t{Year_of_construction}\t\t{Height}\t\t{NumberOfPassengers}");
        }
    }

    class Ship : Vehicle
    {
        private int NumberOfPassengers;
        public Ship(double prise, int year_of_construction, string destinationPort)
        {
            Price = prise;
            Year_of_construction = year_of_construction;
            DestinationPort = destinationPort;
        }
        public void ChangeNumOfPassengers(int passengers)
        {
            NumberOfPassengers = passengers;
        }
        public string DestinationPort { get; set; }

        public Ship Clone()
        {
            var VehicleClone = new Ship(Price, Year_of_construction, DestinationPort);
            VehicleClone.Price = Price;
            VehicleClone.Year_of_construction = Year_of_construction;
            VehicleClone.DestinationPort = DestinationPort;
            VehicleClone.NumberOfPassengers = NumberOfPassengers;
            return VehicleClone;
        }

        public void show()
        {
            Console.WriteLine($"\tPrise\tYear of construction\tDestinationPort\tNumber of Passengers");
            Console.WriteLine($"\t{Price}\t\t{Year_of_construction}\t\t{DestinationPort}\t\t{NumberOfPassengers}");
        }
    }

    class Car : Vehicle
    {
        public Car(double prise, int year_of_construction)
        {
            Price = prise;
            Year_of_construction = year_of_construction;
        }

        public Car Clone()
        {
            var VehicleClone = new Car(Price, Year_of_construction);
            VehicleClone.Price = Price;
            VehicleClone.Year_of_construction = Year_of_construction;
            return VehicleClone;
        }

        public void show()
        {
            Console.WriteLine($"\tPrise\tYear of construction");
            Console.WriteLine($"\t{Price}\t\t{Year_of_construction}");
        }
    }

    class Program
    { 
        static void Main(string[] args)
        {
            Vehicle[] CarPark = new Vehicle[3];
            Ship Mashine1 = new Ship(200, 2000, "North");
            Car Mashine2 = new Car(400, 2004);
            Plane Mashine3 = new Plane(2500, 2020);

            CarPark[0] = Mashine1;
            CarPark[1] = Mashine2;
            CarPark[3] = Mashine3;
        }
    }
}
