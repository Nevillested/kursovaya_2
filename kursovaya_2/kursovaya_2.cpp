using System;
using System.Threading;
using System.IO;

class Program
{
    static Mutex mutexObj = new Mutex();
    static int x = 0;


    static void Main(string[] args)
    {
        for (int i = 0; i < 10; i++)
        {
            Thread Reader = new Thread(Reading);
            Thread Writer = new Thread(Writeing);
            Random rnd = new Random();

            //Случайное число (в диапазоне от 0 до 2)
            int value = rnd.Next(0, 2);
            if (value == 0)
            {
                Writer.Name = $"Писатель";
                Writer.Start();
                Thread.Sleep(2000);
            }
            else
            {
                Reader.Name = $"Читатель";
                Reader.Start();
                Thread.Sleep(2000);
            }

        }

        Console.ReadLine();
    }
    public static void Reading()
    {
        //открываем файл для чтения
        string path = @"C:\Users\Van\Desktop\data.txt";

        using (StreamReader sr = new StreamReader(path, System.Text.Encoding.Default))
        {
            string line;
            while ((line = sr.ReadLine()) != null)
            {
                Console.WriteLine($"{Thread.CurrentThread.Name} прочитал " + line);
            }
        }

    }

    public static void Writeing()
    {
        mutexObj.WaitOne();

        //открываем файл для записи
        string writePath = @"C:\Users\Van\Desktop\data.txt";

        Random x = new Random();
        int n = x.Next(-100, 100);

        using (StreamWriter sw = new StreamWriter(writePath, false, System.Text.Encoding.Default))
        {
            sw.WriteLine(n);
        }
        Console.WriteLine($"{Thread.CurrentThread.Name} написал " + n);

        mutexObj.ReleaseMutex();
    }
}