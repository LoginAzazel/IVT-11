#include <stdio.h>
#include <math.h> 

double Formul(double, double, double);

int main ()
{
    double D, Accuracy,C;
    double X=0, X1=0, Fx, dFx; 
    int range = 0;
    printf("\n\n Программа ищет пересечение графика с осью абцис функции:\n"
           "\n e^Cx - D = 0 \n\n");
    printf ("Введите С: "); 
    scanf ("%lf", &C);
    printf ("Введите смещение по Y (D): "); 
    scanf ("%lf", &D);
    printf ("Введите точность где Х < 1 (В формате 0.01): ");
    scanf ("%lf", &Accuracy);

     while( Formul(C,D,X)*Formul(C,D,X1) >= 0 && range < 30)
    {
        X=X1;
        X1 += 0.1;
        range++;
    }
    range = 0;
    while( Formul(C,D,X)*Formul(C,D,X1) >= 0 && range < 30)
    {
        X=X1;
        X1 -= 0.1;
        range++;
    }
    range = 0;

    do
    {
        X = X1;
        range++;
        Fx = Formul(C, D, X1);
        dFx = C * pow(2.71, C*X1);
        X1 -= Fx/dFx;
    } while( Accuracy < fabs(X - X1) && range < 10000);
    printf("%lf\n", X);
    return 0;
}

double Formul( double C, double D, double X)
{
    return pow(2.71, C*X) - D;
}
