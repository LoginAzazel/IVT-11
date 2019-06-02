#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//////////////////////////////////////////////////////////////////
///////////////// Объявление функций.

/*_______________ Комнаты ______________________________________*/
////
// У каждой комнаты имееться своя характеристика, что говорит, с какой стороны нет входа/выхода
// Цифры перед каждой комнатой, обозначают отсутствые входа/выхода в определенной стороне
// 1 - север, 2 - юг, 3 - запад, 4 - восток
void ZeroRoom(char ****, int ****);                   // Начальная комната
void FirstRoom(char ****, int ****, int, int, int);   // 10) Нет исключений
void TunnelRoom(char ****, int ****, int, int, int);  // 1) Кроме 3,4
void TRoom(char ****, int ****, int, int, int);       // 2) Кроме 2
void TunnelDown(char ****, int ****, int, int, int);  // 3) Кроме 2,1
void TreverseRoom(char ****, int ****, int, int, int);// 4) Кроме 1
void LargeRoom(char ****, int ****, int, int, int);   // 5) Нет исключений
void SEPortalRoom(char ****, int ****, int, int, int);// 6) Кроме 2,4
void WPortalRoom(char ****, int ****, int, int, int); // 7) Кроме 1,2,3
void TunelColumnRoom(char ****, int ****, int, int, int); // 8) Кроме 1,2
void ThreepleRoom(char ****, int ****, int, int, int);// 9) Кроме 4,3

/*_______________ Основыные функции ____________________________*/
int**** Preparation_Memory_Allocation_Statistics( int **** );
////
// Выделяет память на статистику выполнения
// Statistics[0][0-11][0-11][0/1] - Первый аргумент ([0]) показывает размерность комнаты, что находится 
                                    // на карте замка под координатами от 0 и до 11. К примеру [5][6]. 
                                    // Последный аргумент являеся самой рамерностью 
                                        // [0] - Количество сток (Линий || дальность по Y)
                                        // [1] - Количество столбцов (Дальность по Х)
// Statistics[2][0][0][0/1/2/3] - Первый аргумент ([2]) содержит позицию игрока в пространстве
                                    // [0] - Дальность по Y на карте замка. Показывает на какой строке находиться комната, в которой находиться игрок 
                                    // [1] - Дальность по Х на карте замка. Показывает в каком столбце находиться комната, в которой находиться игрок 
                                    // [2] - Дальность по Y в комнате. Номер строки, в котором находиться игрок
                                    // [3] - Дальность по Х в комнате. Номер столбца, в котором находиться игрок
// Statistics[1][0-11][0-11][0] - Первый аргумент ([1]) показывает, производилась ли генерация комнаты вообще 
                                    // на карте замка под координатами от 0 и до 11. К примеру [5][6]. 
                                    // Последный аргумент [0] показывает: 
                                        // 0 - генерация в этой области не производилась и требуется данным коорднатам присвоить комнату
                                        // 1 - комната в данных кооринатах существует и нужно просто ее воспроизвести       
///
char**** Preparation_Memory_Allocation_Playground( char**** );
////
// Выделение динамической памяти на карту игры.
// MapCastle[ Номер комнаты по Y ][ Номер комнаты по Х ][ Элемент комнаты по Y ][ Элемент комнаты по Х ]
void ActionList(char ****, int ****, int, int, int);     // Вызвывает на экран список возможных действий игрока 
                                                            // И, если была команда, подсказывает примерное месторасположение выхода
int Action( char ****, int ****, int, int);              // Функция всех возможных действий игрока (Движение или получение подсказки)  
char Main_Menu();                                        // Главное меню игры
int Gameplay(char ****, int****);                        // Основная функция игры. Пока она активна, игра продолжаеться
void GenerationCastle(char ****, int ****, int, int, int);  // Функция, в которой производятся решения по поводу какую комнату сгенерировать
void Loading();                                             // Вызывает небольшую анимацию. Декоротивный элемент
void WallPainter(char ****, int****, int, int, int, int, int, int);  // Создает необходимые стены, дабы игрок не смог переместиться туда, где он 
                                                                // физически оказаться не может
void ExitPainter(char ****, int****, int, int);             // Генерирует выход из лабиринта
void SellectRoom(char ****, int ****, int, int, int, int);          // В комнате находиться список всех комнат. Получая на вход номер комнаты и ее расположение,
                                                                        // печатает комнату в заданной координате

/*_______________ Системные функции ____________________________*/

void Display(char ****, int ****);      // Выводит комнату на экран
void clear();                           // Очищает экран

//////////////////////////////////////////////////////////////////
///////////////// Начало программы.
////
int main()
{
    srand(time(NULL));
    int i,j,k,l;    // Побочные переенные
    char Enter;     // Пременнаяя выбора режима игры
    int End = 1;    // Переменная отвечающая за конец игры (1 - Конец. 0 - Продолжаем, создать новый этаж)

    Enter = Main_Menu();    // Вызов главного меню
    Again:;                 // Ссылка на возрат, если придется переходить на другой этаж
    char ****MapCastle;     // Указатель на область памяти главной карты
    int ****Statistics;     // Указаталь на всю происходящую статистику в игре
    Statistics = Preparation_Memory_Allocation_Statistics(Statistics);     // Выделение памяти на динамический массив для статистики
    MapCastle = Preparation_Memory_Allocation_Playground(MapCastle);       // Выделение памяти на динамический массив для карты игры

    End = Gameplay(MapCastle, Statistics);      // Вызов основной функции игры. Все происходящее в игре описываеться в ней 
                                                    // Возвращает 0 если нужно перегенерировать лабиринт. 1 - при успешном прохождении
    for( i = 0; i < 11; i++)
    {
        free(MapCastle[i]);     // Очищение днамической памяти
    }
    free(MapCastle);

    for( i = 0; i < 3; i++)
    {
        free(Statistics[i]);    // Очищение днамической памяти
    }
    free(Statistics);
    if( End == 0 ) { system("sleep 2"); goto Again; }   // Если функция Gameplay вернула 0 - повторить все действия с генерацией и продолжить игру

    return 0;       // Успешное окончание программы
}
/////////////////////
///////////////////// Основные функции /////////////////////
/////////////////////
void GenerationCastle(char **** MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    int i,j,k;          // Побочные переменные
    int Sellect;        // переменная рандомного выбора комнаты
    switch (Move)
    {
        case 1:         // Игрок пытаеться пройти в верхнюю комнату
            Statistics[2][0][0][0]--;   // Коокдината меняеться на следующую комнату
            if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] == 0)
            {   // Если слудущая комната еще не была сгенерирована (Игрок в нее входит впервые), то происходит ее создание
                do
                {
                    Sellect = rand()%10+1;  // Генерируеться случайное число 
                } while ( Sellect == 3 || Sellect == 4 || Sellect == 7 || Sellect == 8);   // Если оно не проходит проверку по этим критериям, то число генерируеться вновь
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);       // Вызов функции выбора комнаты
                Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] = Sellect;   // Запись в статистику, на карту генерации, номер сгенерированной комнаты
            } else
            {   
                Sellect = Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ];
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
            }
        break;

        case 2:         // Игрок пытаеться пройти в нижнюю комнату
            Statistics[2][0][0][0]++;   // Коокдината меняеться на следующую комнату
            if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] == 0)
            {  // Если слудущая комната еще не была сгенерирована (Игрок в нее входит впервые), то происходит ее создание
                do
                {
                    Sellect = rand()%10+1;
                } while ( Sellect == 3 || Sellect == 2 || Sellect == 7 || Sellect == 8 || Sellect == 6);    // Если оно не проходит проверку по этим критериям, то число генерируеться вновь
                
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
                Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] = Sellect;
            } else
            {
                Sellect = Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ];
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
            }
        break;

        case 3:         // Игрок пытаеться пройти в левую комнату
            Statistics[2][0][0][1]--;   // Коокдината меняеться на следующую комнату
            if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] == 0)
            {   // Если слудущая комната еще не была сгенерирована (Игрок в нее входит впервые), то происходит ее создание
                do
                {
                    Sellect = rand()%10+1;
                } while ( Sellect == 2 || Sellect == 1 || Sellect == 7 || Sellect == 9);    // Если оно не проходит проверку по этим критериям, то число генерируеться вновь
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
                Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] = Sellect;
            } else
            {
                Sellect = Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ];
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
            }
        break;

        case 4:         // Игрок пытаеться пройти в правую комнату
            Statistics[2][0][0][1]++;   // Коокдината меняеться на следующую комнату
            if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] == 0)
            {   // Если слудущая комната еще не была сгенерирована (Игрок в нее входит впервые), то происходит ее создание
                do
                {
                    Sellect = rand()%10+1;
                } while ( Sellect == 2 || Sellect == 1 || Sellect == 6 || Sellect == 9);    // Если оно не проходит проверку по этим критериям, то число генерируеться вновь
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
                Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] = Sellect;
            } else
            {
                Sellect = Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ];
                SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
            }
            
        break;
    
        default:
        break;
    }
}

int Gameplay(char **** MapCastle, int **** Statistics)
{
        Loading();  // Вызов декоративной загрузки
        clear();    // Очистка экрана
    int Compas = rand()%4+1;    // Переменная для записи стороны выхода
    int Position = rand()%11+1; // Переменная для записи позиции выхода
    
    int i,j,k;  //  Обьявление побочных переменных
    int Move;   //  
    ExitPainter(MapCastle, Statistics, Compas, Position);   // Генерация выхода из лабиринта
    Statistics[2][0][0][0] = 5; //
    Statistics[2][0][0][1] = 5; //  Установка начальной позиции игрока
    Statistics[2][0][0][2] = 3; //
    Statistics[2][0][0][3] = 5; //
    
    if(Statistics[1][6][6][0] == 0) // Создаем первую, начальную комнату
    {
        ZeroRoom(MapCastle, Statistics);  
    }
    MapCastle[5][5][3][5] = 'X';    // Выставлям начальную позицию на карте

    while( 1 )  // Приготовления закончены. Начинаем игру
    {
        if(MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] - 1 ][ Statistics[2][0][0][3] ] == '*' ||
           MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] + 1 ][ Statistics[2][0][0][3] ] == '*' ||
           MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] - 1 ] == '*' ||
           MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] + 1 ] == '*' )
           {    // Если рядом оказываеться символ "*", то происходит переход на следующий этаж, а соответственно в новый лабиринт
               clear(); 
               printf("\tВы обнаружили каккой-то проход. \n\tУ вас появилось непреодалимое"
                    "желание воспользоваться данной возможностью.\n\n"
                    " Вы вроде перешли на другой этаж... Однако кажется вновь заблудились\n\n\n");
                break;  // Функция Геймплей перестает передает инициативу main, где проходит перегенерация лабиринта
           }
        clear();                                                    // Каждый проход требует очистку экрана от старой информациии 
        Display(MapCastle, Statistics);                             // Вывод на экран комнты и новой позиции игрока в ней
        ActionList(MapCastle, Statistics, Compas, Position, Move);  // Вывод на экран список возможных действий игрока и, при заначении Move = 5, подсказывает примерное расположеие выхода.
        Move = Action(MapCastle, Statistics, Compas, Position);     // Выбор игроком действия персонажа
        GenerationCastle(MapCastle, Statistics, Move, Compas, Position);    // Создание новой или переход на уже сгенерированную комнату
        //Move = 0;
    }
    return 0;
}



int Action(char ****MapCastle, int****Statistics, int Compas, int Position)
{
    int i,j,k;
    char ENTER;
    ENTER = getchar();

    switch (ENTER)
    {
    case 'w':
        if( (MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] - 1 ][ Statistics[2][0][0][3] ] == ' ') 
                    && (0 < Statistics[2][0][0][2] - 1) )
        { 
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] - 1 ][ Statistics[2][0][0][3] ] = 'X';
            Statistics[2][0][0][2]--;
        }
        else if( 1 == Statistics[2][0][0][2] )
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            return 1;
        }
    break;

    case 's':
        if( (MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] + 1 ][ Statistics[2][0][0][3] ] == ' ') 
                    && (Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] > Statistics[2][0][0][2] + 2) )
        { 
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] + 1 ][ Statistics[2][0][0][3] ] = 'X';
            Statistics[2][0][0][2]++;
        }
        else if( Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ] == Statistics[2][0][0][2] + 2 )
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            return 2;
        }
        
    break;

    case 'a':
       if( (MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] - 1] == ' ') 
                    && (0 < Statistics[2][0][0][3] - 1) )
        { 
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] - 1] = 'X';
            Statistics[2][0][0][3]--;
        }
        else if( 1 == Statistics[2][0][0][3] )
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            return 3;
        }
    break;

    case 'd':
        if( (MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] + 1] == ' ') 
                    && (Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 1 ] > Statistics[2][0][0][3] + 2) )
        { 
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] + 1] = 'X';
            Statistics[2][0][0][3]++;
        }
        else if( Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 1 ] == Statistics[2][0][0][3] + 2 )
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';
            return 4;
        }
    break;

    case 'h':
        return 5;
    break;

    default:
    break;
    }
    return 0;
}


char Main_Menu()
{
    char GameStile;
    clear();
    printf("\t\t_______ Lost in the castle _______"
    "\n\n\n\t\t  Сможете ли вы найти выход из мачного замка?"
    "\n\n\t Звездочка(*) - твой друг, заблудший путник"
    "\n\t\tДостаточно задеть ее, как ты найдешь новый путь.."
    "\n\t\t\tНо это безвозратно..."
    "\n\n\n\n\n\n\t\t\t ~~ Начать забег ~~"
    "\n\t\n");
    scanf("%c", &GameStile);
    clear();

    return GameStile;
}



void ActionList(char ****MapCastle, int****Statistics, int Compas, int Position, int Move)
{
    printf("\n\n\t\t   w \t\t\t h - Прислушаться"
           "\n\t\t a s d \t\t\t e - Оставаться на месте\n\n");
           
    if( Move == 5) 
        {
            clear();
            printf("-- %d -- %d --",Compas, Position);
            if( Statistics[2][0][0][1] > Position && (Compas == 1 || Compas == 2) )
        {
            if( Compas == 1) printf("Северо-запад\n");
            else if( Compas == 2)printf("Юго-запад\n");
        } else if( Statistics[2][0][0][1] < Position && (Compas == 1 || Compas == 2) )
        {
            if( Compas == 1) printf("Северо-Восток\n");
            else if( Compas == 2)printf("Юго-Восток\n");
        } else if( Compas == 1 ) printf("На север");
        else if( Compas == 2)printf("На юг");

        if( Statistics[2][0][0][0] > Position && (Compas == 3 || Compas == 4) )
        {
            if( Compas == 3) printf("Юго-запад\n");
            else if( Compas == 4)printf("Юго-восток\n");
        } else if( Statistics[2][0][0][0] < Position && (Compas == 3 || Compas == 4) )
        {
            if( Compas == 4) printf("Северо-Восток\n");
            else if( Compas == 3)printf("Северо-запад\n");
        } else if( Compas == 3 ) printf("На запад");
        else if( Compas == 4)printf("На восток");

        //if( Statistics[2][0][0][1] == Position || Statistics[2][0][0][0] == Position) printf("На месте");
        system("sleep 2");
        clear();
        }
}



char**** Preparation_Memory_Allocation_Playground(char ****MapCastle)
{
    int i,k,j;
    MapCastle = (char ****) malloc (11 * sizeof(char ***));
    for(i = 0; i < 11; i++)
    {
        MapCastle[i] = (char ***) malloc ( 11 * sizeof(char**)); 
        for(j=0; j<11; j++)
        {
            MapCastle[i][j] = (char **) malloc (11 * sizeof(char *));
            for(k = 0; k<11; k++)
            {
                MapCastle[i][j][k] = (char *) malloc (11 * sizeof(char));
            }
        }
    }
    return MapCastle;
}



int**** Preparation_Memory_Allocation_Statistics(int ****Statistics)
{
    int i,k,j;

    Statistics = (int ****) malloc (3 * sizeof(int ***));
    for(i = 0; i < 3; i++)
    {
        Statistics[i] = (int ***) malloc ( 11 * sizeof(int**)); 
        for(j=0; j<11; j++)
        {
            Statistics[i][j] = (int **) malloc (11 * sizeof(int *));
            for(k = 0; k<11; k++)
            {
                Statistics[i][j][k] = (int *) malloc (5 * sizeof(int));
            }
        }
    }
    return Statistics;
}



void Loading()
{
    int i,j,k;
    char Array[12][18] =
     {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','-','-',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ','-','-',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ','-','-',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','-','-',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','-','-'},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
     };
    int P[2];
    P[0] = 0;
    P[1] = 2;
    Array[ P[0] ][ P[1] ] = 'X';

    for( k = 0; k < 9; k++)
    { 
        system("sleep 0.2");
        clear();
        for( i = 0; i < 11; i++)
        {
            printf("\t\t\t\t\t");
            for( j = 0; j < 15; j++)
            {
                printf("%c", Array[i][j]);
            }
        printf("\n");
        }
        printf("\n\n\n\n");
        Array[ P[0] ][ P[1] ] = ' ';
        if( k%2 == 1 )
        {
            P[0] += 2;
        } else 
        {
            P[1] += 3;
        }
        Array[ P[0] ][ P[1] ] = 'X';
    }
    system("sleep 0.2");
}



void WallPainter(char ****MapCastle, int****Statistics, int Compas, int Position, int N, int S, int W, int E)
{
    int i,k;
    if( Statistics[2][0][0][0] == 0 && (Compas != 1 || Position != Statistics[2][0][0][1]) )
    {
        for(i=0; i < 12; i++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ][ i ] = '/';
        }
    }

    if( Statistics[2][0][0][0] == Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] - 1 && (Compas != 2 || Position != Statistics[2][0][0][1]))
    {
        for(i=0; i < 12; i++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] - 1 ][ i ] = '/';
        }
    }

    if( Statistics[2][0][0][1] == 0 && ( Compas != 3 || Position != Statistics[2][0][0][0] ) )
    {
        for(i=0; i < 12; i++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ i ][ 0 ] = '/';
        }
    }

    if( Statistics[2][0][0][0] == Statistics[0][ Statistics[2][0][0][0] ][  Statistics[2][0][0][1] ][1] - 1 && (Compas != 1 || Position != Statistics[2][0][0][1]))
    {
        for(i=0; i < 12; i++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ i ][ Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] - 1 ] = '/';
        }
    }
}



void ExitPainter(char ****MapCastle, int****Statistics, int Compas, int Position)
{
    int i,k;            // побочные переменные
    int Sellect;        // Переменная, в которую рандомиться номер комнаты
    int Move = Sellect; // Требуеться для успешного вызова прошлых функций

    switch (Compas)     // В зависимости от того, какая сторона света была выбрана (1 - Север. 2 - Юг. 3 - Запад. 4 - Восток), генерируеться 
    {                              // генерируеться выход
    case 1:             // Был рандомизирован Север
    Statistics[2][0][0][0] = 0;             //
    Statistics[2][0][0][1] = Position-1;    //  Установка начальной позиции (Требуеться дабы вызвать уже созданные функции)
    Statistics[2][0][0][2] = 0;             //
    Statistics[2][0][0][3] = 0;             //
    do
    {
        Sellect = rand()%10+1;              // Генерируеться номер комнаты
    } while ( Sellect == 3 || Sellect == 4 || Sellect == 6 || Sellect == 7 || Sellect == 8 || Sellect == 2);    // Номер комнаты не может быть одним из этих
    SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);                                        // Идем в список комнат и рисуем наш выход там
    MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';    // Убираем изменения связанные 
    break;                                                                                                                         // с нашей позицией
    
    case 2:             // Был рандомизирован Юг
    Statistics[2][0][0][0] = 10;            //
    Statistics[2][0][0][1] = Position-1;    // Установка начальной позиции (Требуеться дабы вызвать уже созданные функции)
    Statistics[2][0][0][2] = 0;             //
    Statistics[2][0][0][3] = 0;             //
    do
    {
        Sellect = rand()%10+1;
    } while ( Sellect == 3 || Sellect == 4 || Sellect == 6 || Sellect == 7 || Sellect == 8 || Sellect == 2);    // Номер комнаты не может быть одним из этих
    SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
    MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';    // Убираем изменения связанные 
    break;                                                                                                                         // с нашей позицией

    case 3:             // Был рандомизирован Запад
    Statistics[2][0][0][0] = Position-1;    //
    Statistics[2][0][0][1] = 0;             // Установка начальной позиции (Требуеться дабы вызвать уже созданные функции)
    Statistics[2][0][0][2] = 0;             //
    Statistics[2][0][0][3] = 0;             //
    do
    {
        Sellect = rand()%10+1;
    } while ( Sellect == 2 || Sellect == 1 || Sellect == 6 || Sellect == 7);    // Номер комнаты не может быть одним из этих
    SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
    MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';    // Убираем изменения связанные 
    break;                                                                                                                         // с нашей позицией

    case 4:             // Был рандомизирован Восток
    Statistics[2][0][0][0] = Position-1; //
    Statistics[2][0][0][1] = 10;         // Установка начальной позиции (Требуеться дабы вызвать уже созданные функции)
    Statistics[2][0][0][2] = 0;          //
    Statistics[2][0][0][3] = 0;          // 
    do
    {
        Sellect = rand()%10+1;
    } while ( Sellect == 2 || Sellect == 1 || Sellect == 6 || Sellect == 7);    // Номер комнаты не может быть одним из этих
    SellectRoom(MapCastle, Statistics, Sellect, Move, Compas, Position);
    MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = ' ';    // Убираем изменения связанные 
    break;                                                                                                                         // с нашей позицией
    }
}



void SellectRoom(char ****MapCastle, int****Statistics, int Sellect, int Move, int Compas, int Position)
{
    switch (Sellect)
    {
        case 1:
        TunnelRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 2:
        TRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 3:
        TunnelDown(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 4:
        TreverseRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 5:
        LargeRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 6:
        SEPortalRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 7:
        WPortalRoom(MapCastle, Statistics, Move, Compas, Position);
        break;
        
        case 8:
        TunelColumnRoom(MapCastle, Statistics, Move, Compas, Position);
        break;

        case 9:
        ThreepleRoom(MapCastle, Statistics, Move, Compas, Position);
        break;
    
        default:
        FirstRoom(MapCastle, Statistics, Move, Compas, Position);
        break;
    }
} 



/////////////////////
///////////////////// Комнаты /////////////////////
/////////////////////
void ZeroRoom(char ****MapCastle, int **** Statistics)
{
    int i,j;
    //// Сама комната
    char SelectRoomStatic[8][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 10;
}



void FirstRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    {   
    int i,j;
    //// Сама комната
    char SelectRoomStatic[8][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 10;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 5;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 2:
            Statistics[2][0][0][2] = 1;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 3:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 1,1,1,1);
}



void TunnelRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    { 
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','+','-',' ','+',' ',' ',' ',' '},
        {' ',' ',' ','|',' ',' ','|',' ',' ',' ',' '},
        {' ',' ',' ','|',' ',' ','|',' ',' ',' ',' '},
        {' ',' ',' ','|',' ','-','|',' ',' ',' ',' '},
        {' ',' ',' ','|',' ',' ','|',' ',' ',' ',' '},
        {' ',' ',' ','|',' ',' ','|',' ',' ',' ',' '},
        {' ',' ',' ','+','-',' ','+',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 12; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 1;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 7;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 2:
            Statistics[2][0][0][2] = 1;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 1,1,0,0);
}



void TRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    { 
    int i,j;
    //// Сама комната
    char SelectRoomStatic[8][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-','W','W','W','-','-','+',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','|','\\',' ',' ',' ',' ',' ','/','|',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 2;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 5;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 3:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 0,1,1,1);
}



void TunnelDown(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    { 
    int i,j;
    //// Сама комната
    char SelectRoomStatic[8][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ','+','-',' ','-','-','+',' '},
        {' ','|',' ',' ','|',' ',' ',' ','J','|',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 3;
    }

    switch (Move)
    {
        case 3:
            Statistics[2][0][0][2] = 2;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 0,0,1,1);
}



void TreverseRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    { 
    int i,j;
    //// Сама комната
    char SelectRoomStatic[8][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-',' ',' ',' ','-','-','+',' '},
        {' ','|',' ','|',' ',' ',' ','|',' ','|',' '},
        {' ',' ',' ','+',' ',' ',' ','+',' ',' ',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 4;
    }

    switch (Move)
    {
        case 2:
            Statistics[2][0][0][2] = 1;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 3:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 3;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 0,1,1,1);
}



void LargeRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    {   
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][13] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ','-','-','-',' ','-','-','-',' ',' '},
        {' ','-','+',' ',' ',' ',' ',' ','+','-',' '},
        {' ','|',' ',' ','+','-','+',' ',' ','|',' '},
        {' ',' ',' ',' ','|',' ','|',' ',' ',' ',' '},
        {' ','|',' ',' ','+','-','+',' ',' ','|',' '},
        {' ','-','+',' ',' ',' ',' ',' ','+','-',' '},
        {' ',' ','-','-','-',' ','-','-','-',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 5;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 7;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 2:
            Statistics[2][0][0][2] = 1;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 3:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 1,1,1,1);
}



void SEPortalRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    {   
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ','|','+','+','+',' ',' ',' ',' ','|',' '},
        {' ','|','+','*',' ',' ',' ',' ',' ','|',' '},
        {' ','|','+',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','|',' ',' ',' ',' ',' ','+','-','|',' '},
        {' ','|',' ',' ',' ',' ',' ','|',' ',' ',' '},
        {' ','+','-','-','-',' ','-','+',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 6;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 7;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 3:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 1,0,1,0);
}



void WPortalRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    {   
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-','-','W','-','-','-','+',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ','|',' ',' ',' ',' ',' ',' ',' ','|',' '},
        {' ',' ',' ',' ',' ','W',' ',' ',' ','|',' '},
        {' ','|',' ',' ',' ',' ',' ','+',' ','|',' '},
        {' ','|',' ',' ',' ',' ',' ','|',' ','|',' '},
        {' ','+','-','-','-','W','-','+','*','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 7;
    }

    switch (Move)
    {
        case 4:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 0,0,0,1);
}



void TunelColumnRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    {   
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][12] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ','|',' ',' ',' ','W',' ',' ',' ','|',' '},
        {' ','|',' ','W',' ','W',' ','W',' ','|',' '},
        {' ',' ',' ','W',' ','W',' ','W',' ',' ',' '},
        {' ','|',' ','W',' ','W',' ','W',' ','|',' '},
        {' ','|',' ','W',' ',' ',' ','W',' ','|',' '},
        {' ','+','-','-','-','-','-','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 9; i++)
    {
        for(j = 0; j < 11; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 11;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 8;
    }

    switch (Move)
    {
        case 3:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 9;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 4:
            Statistics[2][0][0][2] = 4;
            Statistics[2][0][0][3] = 1;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 0,0,1,1);
}



void ThreepleRoom(char ****MapCastle, int **** Statistics, int Move, int Compas, int Position)
{
    if( Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] == 0)
    { 
    int i,j;
    //// Сама комната
    char SelectRoomStatic[10][13] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','+','-',' ','-','-','-','-','+',' '},
        {' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',' '},
        {' ','+','-','-','-','-','-','-','+',' ','|',' '},
        {' ','|',' ',' ',' ',' ',' ',' ','|',' ','|',' '},
        {' ','|',' ','-','-','-','|',' ','|',' ','|',' '},
        {' ','|',' ',' ',' ',' ','|',' ','|',' ','|',' '},
        {' ','+','-','-','-',' ','|',' ',' ',' ','|',' '},
        {' ',' ',' ',' ',' ',' ','+','-','-','-','+',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };
    //// Занесение комнаты на поле игры
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 12; j++)
        {
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][i][j]= SelectRoomStatic[i][j];
        }
    }
    //// Заносим на побочную карту размерности характеристику комнаты
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 10;
    Statistics[0][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][1] = 12;
    //// Отмечаем на побочной карте генерации сгенерированый участок
    Statistics[1][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][0] = 9;
    }

    switch (Move)
    {
        case 1:
            Statistics[2][0][0][2] = 7;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        case 2:
            Statistics[2][0][0][2] = 1;
            Statistics[2][0][0][3] = 5;
            MapCastle[ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ Statistics[2][0][0][2] ][ Statistics[2][0][0][3] ] = 'X';
        break;

        default:
        break;
    }
    WallPainter(MapCastle, Statistics, Compas, Position, 1,1,0,0);
}
/////////////////////
///////////////////// Системные функциии /////////////////////
/////////////////////
void Display(char ****MapCastle, int ****Statistics)
{
    int i,j;
    for(i=0; i < Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 0 ]; i++)
    {
        printf("\t\t\t");
        for(j=0; j < Statistics[ 0 ][ Statistics[2][0][0][0] ][ Statistics[2][0][0][1] ][ 1 ]; j++)
        {
            printf("%c", MapCastle[ Statistics[ 2 ][ 0 ][ 0 ][ 0 ] ][ Statistics[ 2 ][ 0 ][ 0 ][ 1 ] ][i][j]);
        }
        printf("\n");
    }
}



void clear()
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
    "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}
/////////////////////
//////////////////////////////////////////////////////////////////
