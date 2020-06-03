#include <iostream>
#include <string>
using namespace std;

class flat {
private:
    int nHouse;
    int nFlat;
    string FIO;
    int VolumeWater;
public:
    flat() : nHouse(0), nFlat(0), FIO(""), VolumeWater(0) {};
    flat(int nHouse, int nFlat, string FIO, int VolumeWater): nHouse(nHouse), nFlat(nFlat), FIO(FIO), VolumeWater(VolumeWater) {};

    string toString() 
    {
        return to_string(nHouse) + '\t' + to_string(nFlat)+ '\t' + FIO + '\t' + to_string(VolumeWater);
    }

    int operator <( flat& other ) 
    {
        return ( nHouse< other.nHouse ) || ( nHouse == other.nHouse ) && ( nFlat < other.nFlat );
    }
};

template <typename T>
void bubbleSort(T data[], int lenD) 
{
    T tmp;
    for (int i = 0; i < lenD - 1; i++) {
        for (int j = lenD - 1; j > i; j--) {
            if (data[j] < data[j - 1]) {
                tmp = data[j];
                data[j] = data[j - 1];
                data[j - 1] = tmp;
            }
        }
    }
}

int main ()
{
    //setlocale(LC_ALL, "Russian");

    const int n = 6;
    flat Array[n] 
    {
        flat( 10, 1, "Иванов Иван Степанович", 80),
        flat( 10, 2, "Кузнецова Елена Семенова", 120),
        flat( 11, 8, "Фридман Владимир Григорьевич", 214),
        flat( 11, 9, "Петрова Анно Федоровна", 267),
        flat( 12, 1, "Баринов петр Васильевич", 86),
        flat( 12, 3, "Воронов Антон Петрович", 123)
    };

    bubbleSort(Array, n);

    for (int i = 0;i < n;i++)
        cout << Array[i].toString() << endl;
    cout<< '\n';
    return 0;
}
