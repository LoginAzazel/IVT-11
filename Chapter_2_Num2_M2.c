#include <stdio.h>
#include <math.h> 

double Formul(double, double, double);

int main ()
{
    double ConstD, Accuracy, ConstC;
    double X=0, X1=0, Fx, dFx; 
    int range = 0;
    printf("\n\n Программа ищет пересечение графика с осью абцис функции:\n"
           "\n e^Cx - D = 0 \n\n");
    printf ("Введите С: "); 
    scanf ("%lf", &ConstC);
    printf ("Введите смещение по Y (D): "); 
    scanf ("%lf", &ConstD);
    printf ("Введите точность где Х < 1 (В формате 0.01): ");
    scanf ("%lf", &Accuracy);

    do
    {
        range++;
        Fx = Formul(ConstC, ConstD, X);
        dFx = ConstC * pow(2.71, ConstC*X);
        X -= Fx/dFx;
    } while( Accuracy < dFx && range < 10000);
    printf("%lf\n", X);
    return 0;
}

double Formul( double C, double D, double X)
{
    return pow(2.71, C*X) - D;
}
