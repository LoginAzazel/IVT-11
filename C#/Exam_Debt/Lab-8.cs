using System;

namespace LearningProg
{   // Лабораторная работа 8. Вариант 8.
    class StudentGroup
    {
        private int studentsNum = 0;
        private string[,] ArrayStudents = null; 

        private bool checkID_inArray(string[,] arrayStudents)
        {
            for (int i = 0; i < arrayStudents.GetLength(0); i++)
            {
                for (int j = i+1; j < arrayStudents.GetLength(0); j++)
                {
                    if (arrayStudents[i, 0] == arrayStudents[j, 0]) return false;
                }
            }
            return true;
        }

        private bool checkID(string id)
        {
            for (int i = 0; i < ArrayStudents.GetLength(0); i++)
            {
                if (ArrayStudents[i, 0] == id) return false;
            }
            return true;
        }

        public StudentGroup()
        {

        }

        public StudentGroup(string[,] arrayStudents)
        {
            if (checkID_inArray(arrayStudents)) 
            {

                if (arrayStudents.GetLength(1) == 4)
                {
                    studentsNum = arrayStudents.Length / 4;
                    ArrayStudents = new string[studentsNum, 4];

                    for (int i = 0; i < studentsNum; i++)
                    {
                        ArrayStudents[i, 3] = arrayStudents[i, 3];
                        ArrayStudents[i, 2] = arrayStudents[i, 2];
                        ArrayStudents[i, 1] = arrayStudents[i, 1];
                        ArrayStudents[i, 0] = arrayStudents[i, 0];
                    }
                }
                else
                {
                    Console.WriteLine("Таблица не соответствует критериям класса\n (ID) (Имя) (Фамилия) (Дата рождения)");
                }
            }
            else Console.WriteLine("В таблице есть повторяющийся ID. Номер студента должен быть уникальным");
        }

        public bool ChangeStudentInfo(int id, string name, string subname, string date)
        {
            return ChangeStudentInfo(id.ToString(), name, subname, date);
        }

            public bool ChangeStudentInfo(string id, string name, string subname, string date)
        {
            if(checkID(id))
            {
                Console.WriteLine("Студента с данным номером нет");
            }
            else
            {
                int i = 0; while (ArrayStudents[i, 0] != id) i++;
                ArrayStudents[i, 3] = date;
                ArrayStudents[i, 2] = subname;
                ArrayStudents[i, 1] = name;
                ArrayStudents[i, 0] = id;
            }
            return true;
        }

        public bool DeleteStudent( int id )
        {
            return DeleteStudent(id.ToString());
        }

        public bool DeleteStudent( string id)
        {
            for(int i = 0; i < studentsNum; i++)
            {
                if( ArrayStudents[i, 0] == id )
                {
                    string[,] TempArrayStudents = new string[studentsNum-1, 4];
                    for (int j = 0, c = 0; j < studentsNum; j++, c++)
                    {
                        if (j != i)
                        {
                            TempArrayStudents[c, 3] = ArrayStudents[j, 3];
                            TempArrayStudents[c, 2] = ArrayStudents[j, 2];
                            TempArrayStudents[c, 1] = ArrayStudents[j, 1];
                            TempArrayStudents[c, 0] = ArrayStudents[j, 0];
                        }
                        else
                        {
                            c--;
                            continue;
                        }
                    }

                    studentsNum--;
                    ArrayStudents = null;
                    ArrayStudents = new string[studentsNum, 4];
                    for (int k = 0; k < studentsNum; k++)
                    {
                        ArrayStudents[k, 3] = TempArrayStudents[k, 3];
                        ArrayStudents[k, 2] = TempArrayStudents[k, 2];
                        ArrayStudents[k, 1] = TempArrayStudents[k, 1];
                        ArrayStudents[k, 0] = TempArrayStudents[k, 0];
                    }
                    return true;
                }
            }
            return false;
        }

        public void SortId()
        {
            string[] tId = new string[4];
            for(int i = 0; i < studentsNum; i++)
            {
                tId[0] = ArrayStudents[i, 0]; 
                tId[1] = ArrayStudents[i, 1];
                tId[2] = ArrayStudents[i, 2];
                tId[3] = ArrayStudents[i, 3];

                for (int j = i; j < studentsNum; j++)
                {
                    int TempID1 = int.Parse(tId[0]), TempID2 = int.Parse(ArrayStudents[j, 0]);
                    if ( TempID1 > TempID2 )
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            ArrayStudents[i, k] = ArrayStudents[j, k];
                            ArrayStudents[j, k] = tId[k];
                            tId[k] = ArrayStudents[i, k];
                        }
                    }
                }
            }
        }

        public void SortName()
        {
            string[] tName = new string[4];
            for (int i = 0; i < studentsNum; i++)
            {
                tName[0] = ArrayStudents[i, 0];
                tName[1] = ArrayStudents[i, 1];
                tName[2] = ArrayStudents[i, 2];
                tName[3] = ArrayStudents[i, 3];

                for (int j = i; j < studentsNum; j++)
                {
                    string TempID1 = tName[1], TempID2 = ArrayStudents[j, 1];
                    if (TempID1[0] > TempID2[0])
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            ArrayStudents[i, k] = ArrayStudents[j, k];
                            ArrayStudents[j, k] = tName[k];
                            tName[k] = ArrayStudents[i, k];
                        }
                    }
                }
            }
        }

        public void SortSubname()
        {
            string[] tName = new string[4];
            for (int i = 0; i < studentsNum; i++)
            {
                tName[0] = ArrayStudents[i, 0];
                tName[1] = ArrayStudents[i, 1];
                tName[2] = ArrayStudents[i, 2];
                tName[3] = ArrayStudents[i, 3];

                for (int j = i; j < studentsNum; j++)
                {
                    string TempID1 = tName[2], TempID2 = ArrayStudents[j, 2];
                    if (TempID1[0] > TempID2[0])
                    {
                        for (int k = 0; k < 4; k++)
                        {
                            ArrayStudents[i, k] = ArrayStudents[j, k];
                            ArrayStudents[j, k] = tName[k];
                            tName[k] = ArrayStudents[i, k];
                        }
                    }
                }
            }
        }

        public bool FoundStudent( string name, string subname)
        {
            for (int i = 0; i < studentsNum; i++)
            {
                if (name == ArrayStudents[i, 1] && subname == ArrayStudents[i, 2] )
                {
                    Console.WriteLine($"{ArrayStudents[i, 0]}\t{ArrayStudents[i, 1]}\t{ArrayStudents[i, 2]}\t{ArrayStudents[i, 3]}");
                    return true;
                }
            }
            return false;
        }

        public bool FoundName( string name )
        {
            for (int i = 0; i < studentsNum; i++)
            {
                if (name == ArrayStudents[i, 1])
                {
                    Console.WriteLine($"{ArrayStudents[i, 0]}\t{ArrayStudents[i, 1]}\t{ArrayStudents[i, 2]}\t{ArrayStudents[i, 3]}");
                    return true;
                }
            }
            return false;
        }

        public bool FoundSubname( string subname)
        {
            for (int i = 0; i<studentsNum; i++)
            {
                if (subname == ArrayStudents[i, 2])
                {
                    Console.WriteLine($"{ArrayStudents[i, 0]}\t{ArrayStudents[i, 1]}\t{ArrayStudents[i, 2]}\t{ArrayStudents[i, 3]}");
                    return true;
                }
}
            return false;
        }

        public bool FoundID( string id )
        {
            for(int i = 0; i < studentsNum; i++)
            {
                if( id == ArrayStudents[i,0] )
                {
                    Console.WriteLine($"{ArrayStudents[i,0]}\t{ArrayStudents[i, 1]}\t{ArrayStudents[i, 2]}\t{ArrayStudents[i, 3]}");
                    return true;
                }
            }
            return false; 
        }

        public bool FoundID( int id )
        {
            return FoundID(id.ToString());
        }

        public bool AddStudent(string id, string name, string subname, string date)
        {
            if (checkID(id))
            {
                studentsNum++;
                string[,] TempArrayStudents = new string[studentsNum, 4];
                for (int i = 0; i < studentsNum - 1; i++)
                {
                    TempArrayStudents[i, 3] = ArrayStudents[i, 3];
                    TempArrayStudents[i, 2] = ArrayStudents[i, 2];
                    TempArrayStudents[i, 1] = ArrayStudents[i, 1];
                    TempArrayStudents[i, 0] = ArrayStudents[i, 0];
                }
                TempArrayStudents[studentsNum - 1, 3] = date;
                TempArrayStudents[studentsNum - 1, 2] = subname;
                TempArrayStudents[studentsNum - 1, 1] = name;
                TempArrayStudents[studentsNum - 1, 0] = id;

                ArrayStudents = null;
                ArrayStudents = new string[studentsNum, 4];
                for (int i = 0; i < studentsNum; i++)
                {
                    ArrayStudents[i, 3] = TempArrayStudents[i, 3];
                    ArrayStudents[i, 2] = TempArrayStudents[i, 2];
                    ArrayStudents[i, 1] = TempArrayStudents[i, 1];
                    ArrayStudents[i, 0] = TempArrayStudents[i, 0];
                }
            } 
            else
            {
                Console.WriteLine("Студент под этим номером уже существует");
                return false;
            }
            return true;
        }

        public void AddStudent(int id, string name, string subname, string date)
        {
            AddStudent(id.ToString(), name, subname, date);
        }

        public void show()
        {
            for(int i = 0; i < studentsNum; i++)
            {
                Console.WriteLine($"\t{ArrayStudents[i, 0]}\t{ArrayStudents[i, 1]}\t{ ArrayStudents[i, 2]}\t{ ArrayStudents[i, 3]}");
            }
        }

    }
    class Program
    {
        static void Main(string[] args)
        {
            string[,] arrayStudents = new string[4, 4]  {
            { "123", "Viktor", "Cold", "3.4.1997" },
            { "281", "Jo", "Ground", "20.12.1999"},
            { "892",  "Oleg", "Karp", "5.6.2000" },
            { "120", "Name", "Subname", "3.4.1999" }
            };

            StudentGroup IVT = new StudentGroup(arrayStudents);

            IVT.AddStudent(666, "Alex","Kurgan", "6.6.2000");   // Дбавление нового студента
            Console.WriteLine();
            IVT.show();

            Console.WriteLine();
            IVT.FoundID(281);           // Поиск по ID
            IVT.FoundName("Viktor");    // Поиск по Имени
            IVT.FoundSubname("Kurgan"); // Поиск по фамилии
            IVT.FoundStudent("Jo","Ground");    // Поиск студента по имени и фамилии

            Console.WriteLine();
            IVT.SortId();   // Сортировка списка по ID студентов
            IVT.show();

            Console.WriteLine();
            IVT.SortName();   // Сортировка списка по имени студентов
            IVT.show();

            Console.WriteLine();
            IVT.SortSubname();   // Сортировка списка по фамилии студентов
            IVT.show();

            Console.WriteLine();
            IVT.ChangeStudentInfo(123, "!Victor", "!Cold", "0.0.0");   // Изменить данные о студенте
            IVT.show();

            Console.WriteLine();
            IVT.DeleteStudent(123);   // Удалить студента по ID
            IVT.show();
        }
    }
}
