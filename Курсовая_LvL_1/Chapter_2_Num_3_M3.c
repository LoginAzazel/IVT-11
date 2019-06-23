#include <stdio.h>
#include <math.h> 

double Formul(double, double, double);

int main ()
{
    double D, Accuracy, C;
    double End, First = 0; 
    double X1=0.01, X=0;
    int range = 0;
    printf("\n\n Программа ищет пересечение графика с осью абцис функции:\n"
            "\n log2(C*X) - D \n\n");
    printf ("Введите С: "); 
    scanf ("%lf", &C);
    printf ("Введите смещение по Y (D): "); 
    scanf ("%lf", &D);
    printf ("Введите точность где Х < 1 (В формате 0.01): ");
    scanf ("%lf", &Accuracy);

    if( C <= 0 ) 
    {
        printf ("Нет точек пересечения\n"); 
        return 0;
    }

     while( Formul(C,D,X)*Formul(C,D,X1) >= 0 && range < 30)
    {
        X=X1;
        X1 += 0.1;
        range++;
    }
range = 0;
    printf("\n-------------\n");
    do
    {
        range++;
        First = X1 - Formul(C,D,X1)*( (X1 - X)/(Formul(C,D,X1) - Formul(C,D,X) ) );
        X = X1;
        X1 = First;
            printf("%.8lf | %d\n", X1, range);
    } while( Accuracy < fabs(X1 - X) && range < 1000);
    return 0;
}

double Formul( double C, double D, double X)
{
     return log2(C*X) - D;
}
