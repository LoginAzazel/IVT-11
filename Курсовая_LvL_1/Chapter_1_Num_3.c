#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void clear() // Функция для очистки экрана.
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
    "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void F1()
{
    clear();
    int i,Argument = 0;      // Побочные переменные
    double Formula = 0; // Переменные для записи значения формул
    double Accuracy;   // Показатель точности функции 
    int Range;      // Количетво членов в ряде
    int Chase = 0;  // Переменная хранящая прошлое знаечение вычисления

    printf("\tPI = 4*(1 - ( 1/3 )+( 1/5 ) - ( 1/7 )+( 1/9 ) - ... )\n\n"
            "\t\tТочность\t|\tКоличество членов ряда\t|\tЗначение PI\n");
    Accuracy = 1;  // Начальная точность
    Range = 0;     // Количество задействованных членов ряда
    Argument = 1;  // Значение аргумента под А
                        // Отталкиваясь от которого, мы задем числовой ряд
    do
    {
        if(Range % 2 == 0) 
        { Formula += 4*((double)1/Argument); } // Если член ряда нечетный, то записываем его со знаком "+"
        else               
        { Formula -= 4*((double)1/Argument); } // Если член ряда четный, то записываем его со знаком "-"
        Argument += 2;          // Увеличиваем значение знаменателя следуюего члена последовательности 

        Range++;         // Увеличиваем переменную отвечающую за колличество членов ряда
        if( Accuracy > (double)1/Argument )
        {
            Accuracy *= 0.1;
        } 
        if( Range % 5 == 0)
        printf("\t\t- %.3lf -\t|\t\t- %d -\t\t|\t- %.4lf\n",Accuracy, Range, Formula);
        if( Range >= 205) break;
    } while( Accuracy >= 0.001);
}



void F2()
{
    clear();
    int a = 2,i = 2,Argument = 0;      // Побочные переменные
    double Formula = 3; // Переменные для записи значения формул
    double Accuracy;   // Показатель точности функции 
    int Range;      // Количетво членов в ряде
    double Chase = 0;  // Переменная хранящая прошлое знаечение вычисления
    printf("\t PI = 3 + 4*( 1/(2*3*4) - 1/(4*5*6) + 1/(6*7*8) - ...)\n\n"
            "\t\tТочность\t|\tКоличество членов ряда\t|\tЗначение PI\n");
    Accuracy = 1;  // Начальная точность
    Range = 0;     // Количество задействованных членов ряда
    Argument = 1;  // Значение аргумента под А
                        // Отталкиваясь от которого, мы задем числовой ряд
    do
    { 
        Range++; 
        Argument = a*(a+1)*(a+2);
        if(Range % 2 == 0) 
        { Formula -= 4*((double)1/Argument); } // Если член ряда нечетный, то записываем его со знаком "+"
        else               
        { Formula += 4*((double)1/Argument); } // Если член ряда четный, то записываем его со знаком "-"
        Chase = 4*(double)1/Argument;
        if( Accuracy > (double)1/Argument )
        {
            Accuracy *= 0.1;
        }
        printf("\t- %.7lf -\t\t|\t\t- %d -\t\t|\t- %.4lf\n",Accuracy, Range, Formula);
        Argument = (double)Argument/a; a += 2; 
        if( Range >= 205) break;
    } while( Accuracy >= 0.0000001);
}


void F3()
{
    clear();
    int a = 2, Argument = 0;      // Побочные переменные
    double Formula = 6; // Переменные для записи значения формул
    double Accuracy;   // Показатель точности функции 
    int Range;      // Количетво членов в ряде
    double Chase = 0;  // Переменная хранящая прошлое знаечение вычисления
    printf("\t PI = ( 6*( 1 + 1/2^2 + 1/3^2 + 1/4^2 + ...) )^0.5\n\n"
            "\t\tТочность\t|\tКоличество членов ряда\t|\tЗначение PI\n");
    Accuracy = 1;  // Начальная точность
    Range = 1;     // Количество задействованных членов ряда
    Argument = 1;  // Значение аргумента под А
                        // Отталкиваясь от которого, мы задем числовой ряд
    do
    {
        Range++; // Увеличиваем переменную отвечающую за колличество членов ряда
        Argument = a*a;
        a++;
        Formula += 6*((double)1/Argument);

        if( Accuracy > (double)1/Argument )
        {
            Accuracy *= 0.1;
        } 
        if( Range % 5 == 0)
        printf("\t\t- %.5lf -\t|\t\t- %d -\t\t|\t- %.4lf\n",Accuracy, Range, (double)pow(Formula,0.5));
        if( Range >= 305) break;
    } while( Accuracy >= 0.000001);
}



int main()
{
    int NumFormul;
    Again:
    clear(); // Для более лучшей наглядности, очистим экран консоли
                    // Функция очищает экран
    printf("\t___ Задание 3 ___\n\n"
            " PI = 4*(1 - ( 1/3 )+( 1/5 ) - ( 1/7 )+( 1/9 ) - ... )\n"
            " PI = 3 + 4*( 1/(2*3*4) - 1/(4*5*  6) + 1/(6*7*8) - ...)\n"
            " PI = ( 6*( 1 + 1/2^2 + 1/3^2 + 1/4^2 + ...) )^0.5\n\n"
            "\t\nНомер метода?\n");
    scanf("%d",&NumFormul);
    switch (NumFormul)
    {
    case 1:
    F1();
    break;
    
    case 2:
    F2();
    break;

    case 3:
    F3();
    break;

    default:
    printf("Нет такой формулы. Введите число от 1 до 3\\n");
    goto Again;
    }

    return 0;
}
