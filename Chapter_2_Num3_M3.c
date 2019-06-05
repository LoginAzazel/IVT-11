#include <stdio.h>
#include <math.h> 

double Formul(double, double, double);

int main ()
{
    double D, Accuracy, C;
    double Start, End; 
    double X1=0.01, X=0;
    int range = 0;
    printf("\n\n Программа ищет пересечение графика с осью абцис функции:\n"
            "\n e^Cx - D = 0 \n\n");
    printf ("Введите С: "); 
    scanf ("%lf", &C);
    printf ("Введите смещение по Y (D): "); 
    scanf ("%lf", &D);
    printf ("Введите точность где Х < 1 (В формате 0.01): ");
    scanf ("%lf", &Accuracy);

    while( Formul(C,D,X)*Formul(C,D,X1) >= 0)
    {
        X=X1;
        X1 += 0.1;
    }

    do
    {
        range++;
        End = Formul(C, D, X);
        Start = Formul(C, D, X1);
        End = End - (double)End/(End - Start)*(End - Start);
    } while( Accuracy < fabs(End) && range < 10000);
    printf("%lf\n", End);
    return 0;
}

double Formul( double C, double D, double X)
{
    return pow(2.71, C*X) - D;
}
