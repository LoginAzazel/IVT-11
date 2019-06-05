#include <stdio.h>
#include <math.h> 

double Formul(double, double, double);

int main ()
{
    double D, Accuracy, C;
    double X=0, X1=0, Fx, dFx; 
    int range = 0;
    printf("\n\n Программа ищет пересечение графика с осью абцис функции:\n"
           "\n Sin(X*C) - D = 0 \n\n");
    printf ("Введите коофициент наклона (С): "); 
    scanf ("%lf", &C);
    printf ("Введите смещение по Y (D): "); 
    scanf ("%lf", &D);
    printf ("Введите точность где Х < 1 (В формате 0.01): ");
    scanf ("%lf", &Accuracy);

    if( D > 1 || D < - 1) 
    { 
        printf ("Нет точек пересечения\n"); 
        return 0;
    }
    
    while( Formul(C,D,X)*Formul(C,D,X1) >= 0 && range < 30)
    {
        X=X1;
        X1 += 0.5;
        range++;
    }
    range = 0;
    while( Formul(C,D,X)*Formul(C,D,X1) >= 0 && range < 30)
    {
        X=X1;
        X1 -= 0.5;
        range++;
    }
    range = 0;

    do
    {
        range++;
        Fx = Formul(C, D, X);
        dFx = C * cos(X*C);
        X -= Fx/dFx;
    } while( Accuracy < dFx && range < 10000);
    printf("%lf\n", X);
    return 0;
}

double Formul( double C, double D, double X)
{
    return sin(X*C) - D;
}
