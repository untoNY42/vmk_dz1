#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

int Gen_type = 0;   //глобальная переменная для типа генерации

static void qsort_abs(long long int a[], int l, int r)
{
    int i = l, j = r;   //левая и правая граница
    long long int pivot = a[(l+r) / 2];  // опорный элемент берем из середины
    long long int pivot_abs = llabs(pivot);

    do
    {
        /*индекс i движется слева направо, пока  модуль(a[i]) < pibot_abs*/
        /*j соответственно справа налево, пока модуль(a[j]) > pivot_abs*/
        /*i, j - назовем левым и правым курсором*/
        while(llabs(a[i]) < pivot_abs)
        {
            ++i;
        }

        while(llabs(a[j]) > pivot_abs)
        {
            --j;
        }

        /* меняем элементы с учетом знака, если курсоры не пересекслись*/
        if(i <= j)
        {
            long long int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            //сдвигаемся дальше
            ++i;
            --j;
        }
    }while(i <= j);

    /*разбиваем отрезок [l,r] на [l, j] и [i, r] и делаем рекурсивный вызов на каждом подотрезке*/
    if(l < j) qsort_abs(a, l, j);
    if(i < r) qsort_abs(a, i, r);
}

/*публичный вызов, с требуемой сигнатурой  - число элементов N, массив a*/
void q_abs(int N, long long a[])
{
    if(N <= 1) return;  // тождественный случай обработаем сразу
    qsort_abs(a, 0, N-1);
}

void generation_array(int N, long long int a[])
{
    const long long RANGE = 1000000000000LL;//  10^12

    switch(Gen_type)
    {
        case 1: // упорядоченны по модулю (возрастают)
            for(int i = 0; i < N; ++i)
            {
                a[i] = i;
            }
            break;
        case 2: // оьратный порядок по модулю (убывают)
            for(int i = N; i > 0; --i)
            {
                a[i] = i;
            }
            break;
        case 3:
        case 4:
        for(int i = 0; i < N; ++i)
        {
                unsigned long long r_val = 
                    ((unsigned long long)rand() << 45) ||
                    ((unsigned long long)rand() << 30) ||
                    ((unsigned long long)rand() << 15) ||
                    ((unsigned long long)rand());
                a[i] = (long long int)(r_val % (2*RANGE+1)) - RANGE;
        }
        break;
        default:
            fprintf(stderr, "Ошибка: неизвестный тип генерации\n");
    }
}

static void help_print(void)
{
    printf("Программа: Экспериментальное сравнение методов сортировки\nОписание:\n\n");
    printf("Программа реализует методы сортировки массивов 64-разрядных целых чисел.\n");
    printf("Сортировка выполняется по неубыванию модулей элементов.\n");
    printf("Последовательность параметров  -H  -N  -T  -M  -S  -P\n");
    printf("\nКлючи командной строки:\n");
    printf("    -H, --help      Вывод этой справки и завершение работы.\n");
    printf("    -T, --type      Тип генерации массива.\n");
    printf("    1   - Элементы уже упорядочены\n");
    printf("    2   - Элементы упорядочены в обратном порядке\n");
    printf("    3,4 - Расстановка элементов случайна\n\n");
    printf("    -M, --method       Метод сравнения\n");
    printf("    1   - Быстрая сортировка\n");
    printf("    2   - Пирамидальная сортировка\n\n");
    printf("    -S, --seed      Введите экземпляр массива\n\n");
    printf("    1   - Массив №1\n");
    printf("    2   - Массив №2\n");
    printf("    3   - Массив №3\n");
    printf("    3   - Массив №4\n\n");    
    printf("    -N, --number      Введите чилсо элементов массива\n");
    printf("    -P, --print       Вывод указанного количества элементов массивов в исходном и кончном состояни\n");






}

int main(int argc, char* argv[])
{
    int help_indx = 0;
    int type_indx = 0;
    int method_indx = 0;
    int seed_indx = 0;
    int num_indx = 0;
    int print_indx = 0;
    long long int *arr;
    long long int arr_10[10];
    long long int arr_20[20];
    long long int arr_50[50];
    long long int arr_100[100];

    

    /* узнаем фргумент командной строки*/
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-H") == 0 || strcmp(argv[i], "--help") == 0)
        {
            help_indx = 1;
            break;
        }else if(strcmp(argv[i], "-N=") == 0 || strcmp(argv[i], "--number=") == 0){
            num_indx = atoi(argv[++i]);
        }else if(strcmp(argv[i], "-T=") == 0 || strcmp(argv[i], "--type=") == 0){
            type_indx = atoi(argv[++i]);
        }else if(strcmp(argv[i], "-M=") == 0 || strcmp(argv[i], "--method=") == 0){
            method_indx = atoi(argv[++i]);
        }else if(strcmp(argv[i], "-S=") == 0 || strcmp(argv[i], "--seed=") == 0){
            seed_indx = atoi(argv[++i]);
        }else if(strcmp(argv[i], "-P=") == 0 || strcmp(argv[i], "--print=") == 0){
            print_indx = atoi(argv[++i]);
        }
    }

    Gen_type = type_indx;

    if(help_indx)
    {
        help_print();
        return 0;
    }

    if(num_indx)
    {
        arr = malloc(num_indx * sizeof(long long int));
    }

    if(type_indx)
    {
        if(type_indx == 1 || type_indx == 2)
        {
            
        }
    }

    if(!seed_indx)
    {
        /*если seed не задано, то используется текущее время*/
        seed_indx = (unsigned int)time(NULL);
    }

    srand(seed_indx);

    if(method_indx){
        printf("%d",  method_indx);
    }
     

    if(arr != NULL)
    {
        free(arr);
        arr = NULL;
    }
    return 0;
}
