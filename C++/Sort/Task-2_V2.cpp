#include <iostream>
#include <string>
using namespace std;

class Furniture {
private:
    int ID;
    string nFurniture;
    int Cost;
public:
    Furniture() : ID(0), nFurniture(""), Cost(0) {};
    Furniture(int ID, string nFurniture, int Cost): ID(ID),  nFurniture(nFurniture), Cost(Cost) {};

    string toString() 
    {
        return to_string(ID) + '\t' + nFurniture + '\t' + to_string(Cost);
    }

    int operator <( Furniture& other ) 
    {
        return ( Cost > other.Cost ) || ( Cost == other.Cost ) && ( nFurniture < other.nFurniture );
    }
    
    int operator <=( Furniture& other ) 
    {
        return ( Cost > other.Cost ) || ( Cost == other.Cost ) && ( nFurniture <= other.nFurniture );
    }
};

template <typename T>
void Shell(T data[], int lenD) {
    int i;
    T key;
    int step = lenD/2;
    while (step > 0) 
    {
        for (int j = step; j < lenD; j++) 
        {
            key = data[j];
            for (i = j; i >= step;i -= step) 
            {
                if (data[i - step] <= key) 
                {
                    break;
                }
                data[i] = data[i - step];
            }
            data[i] = key;
        }
        step /= 2;
    }
}

int main ()
{
    //setlocale(LC_ALL, "Russian");

    const int n = 6;
    Furniture Array[n] 
    {
        Furniture( 101, "Стол компьютерный", 3500),
        Furniture( 102, "Доска ученическая", 5000),
        Furniture( 103, "Горшок с цветком", 700),
        Furniture( 104, "Стул", 1200),
        Furniture( 107, "Компьютер", 21000),
        Furniture( 108, "Настольная лампа", 800)
    };

    Shell(Array, n);

    for (int i = 0; i < n; i++)
        cout << Array[i].toString() << endl;
    cout<< '\n';
    return 0;
}
