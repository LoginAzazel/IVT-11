using System;
using System.Text;
using System.IO;

namespace LearningProg
{   // Лабораторная работа 7. Вариант 8.

    class Program
    {
        static void Main(string[] args)
        {
            string path = @"C:\Dir";    // Сохраняем в строку путь к директории, где будет храниться наш файл
            DirectoryInfo dirInfo = new DirectoryInfo(path);
            if (!dirInfo.Exists)    // Создаем директорию на диске, чтоб избежать проблемы доступа
            {
                dirInfo.Create();
            }

            string text = "First of all, \"Hello World!\".\n And then you can say \"Lets Start\". End";  // Текст в файл

            using (FileStream fstream = new FileStream($"{path}\\textFile.txt", FileMode.OpenOrCreate))
            {                                                       // Создание текстового файла
                byte[] array = Encoding.Default.GetBytes(text); 
                fstream.Write(array, 0, array.Length);
            }

            using (FileStream fstream = File.OpenRead($"{path}\\textFile.txt")) // Открытие и чтение файла 
            {  
                byte[] array = new byte[fstream.Length];
                fstream.Read(array, 0, array.Length);
                string textFromFile = Encoding.Default.GetString(array);

                for(int i = 0; i < textFromFile.Length; i++)    // Вывод на экран цитат
                {                                     
                    if(textFromFile[i] == '"')
                    {
                        Console.Write("\"");
                        do
                        {
                            i++;
                            Console.Write(textFromFile[i]);
                        } while(textFromFile[i] != '"');
                        Console.WriteLine();
                    }
                }
            }
        }
    }
}
