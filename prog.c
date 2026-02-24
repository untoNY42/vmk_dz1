/*
Ходорыч Антон Сергеевич, 105
Вариант: 2, 3, 4, 5.
Программа:
Программа реализует методы сортировки массивов 64-разрядных целых чисел.
Сортировка выполняется по неубыванию модулей элементов.
Реализованны быстрая(рекурсивный метод) и пирамидальная сортировка.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long long int cmp1 = 0, cmp2 = 0; //счетчик сравнения 
long long int swap1 = 0, swap2 = 0; //счетчик обменов

/*вспомогательная функци для быстрой сортировки*/
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
            ++cmp1; // сравнение с истиной
            ++i;
        }
        ++cmp1; // последние сравнение, которое прервало цикл

        while(llabs(a[j]) > pivot_abs)
        {
            ++cmp1; // сравнение с истиной
            --j;
        }
        ++cmp1; // последние сравнение, которое прервало цикл


        /* меняем элементы с учетом знака, если курсоры не пересекслись*/
        if(i <= j)
        {
            long long int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            ++swap1; //1 обмен = 1 перемещение
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
void q_abs(int N, long long int a[])
{
    if(N <= 1) return;  // тождественный случай обработаем сразу
    qsort_abs(a, 0, N-1);
}

/*вспомогательная функция для пирамидальной сортировки*/
/*i - индекс узла, для которого нужно восстановить свойство кучи*/
/*heap_size - текущий размер кучи*/
static void heapify(long long int arr[], int heap_size, int i)
{
    int left = 2*i + 1;   // левый потомок
    int largest = i;        // индекс наибольшего элемента
    int right = 2 * i + 2;  // правый потомок
    
    //Сравнение с левым потомком
    if(left < heap_size)
    {
        ++cmp2;  // учитываем сравнение модулей: |arr[left]| > |arr[largest]|
        if(llabs(arr[left]) > llabs(arr[largest]))
        {
            largest = left;
        }
    }

    /*Сравнение с правым потомком*/
    if(right < heap_size)
    {
        ++cmp2;  // Учитываем сравнение модулей: |arr[right]| > |arr[largest]|
        if(llabs(arr[right]) > llabs(arr[largest]))
        {
            largest = right;
        }
    }

    if(largest != i) 
    {
        long long int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        ++swap2;  // один обмен = одно перемещение
        
        heapify(arr, heap_size, largest);
    }
}

/*построение максимальной кучи*/
static void build_max_heap(long long int arr[], int N) {
    //начинаем с последнего узла, имеющего потомков (середина массива)
    for(int i = N/2 - 1; i >= 0; --i)
    {
        heapify(arr, N, i);
    }
}

/*основня функция пирамидальной сортировки*/
void heapsort(int N, long long int arr[])
{
    if(N <= 1) return; //базовый случай
    
    //Построить максимальную кучу
    build_max_heap(arr, N);

    //Повторять, пока размер кучи > 1
    for(int heap_size = N; heap_size > 1; --heap_size)
    {
        //Извлечь максимальный элемент и поместить в конец
        long long int temp = arr[0];
        arr[0] = arr[heap_size - 1];
        arr[heap_size-1] = temp;
        ++swap2;// один обмен = одно перемещение

        //Восстановить свойство кучи для оставшегося массива
        heapify(arr, heap_size - 1, 0);
    }
}


/*вспомогательная функция для генерации массива с случайными числами*/
long long int rand_ll(void)
{
    const long long int RANGE = 1000000000000LL;//  10^12
    unsigned long long r_val = 
                    ((unsigned long long)rand() << 45) |
                    ((unsigned long long)rand() << 30) |
                    ((unsigned long long)rand() << 15) |
                    ((unsigned long long)rand());
    return (long long int)(r_val % (2*RANGE+1)) - RANGE;
}

/*генерация массива с случайными числами*/
void generation_array(int N, long long int a[], int type)
{
    for(int i = 0; i < N; ++i)
    {
        a[i] = rand_ll();
    }

    switch(type)
    {
        case 1: // упорядоченны по модулю (возрастают)
        /*сортируем*/
            for(int i = 0; i < N - 1; i++)
                for(int j = 0; j < N - i - 1; j++)
                    if(llabs(a[j]) > llabs(a[j + 1]))
                    {
                        long long int t = a[j]; 
                        a[j] = a[j + 1]; 
                        a[j + 1] = t;
                    }
            break;
        case 2: // обратный порядок по модулю (убывают)
        /*сортируем*/
            for(int i = 0; i < N - 1; i++)
                for(int j = 0; j < N - i - 1; j++)
                    if(llabs(a[j]) < llabs(a[j + 1]))
                    {
                        long long int t = a[j]; 
                        a[j] = a[j + 1]; 
                        a[j + 1] = t;
                    }
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            //printf("%d" , type);
            fprintf(stderr, "Ошибка: неизвестный тип генерации\n");
            exit(1);
    }
}

/*справочная информация*/
static void help_print(void)
{
    printf("Программа: Экспериментальное сравнение методов сортировки\nОписание:\n\n");
    printf("Программу написал студент 105 группы Ходорыч Антон Сергеевич.\n");
    printf("Программа реализует методы сортировки массивов 64-разрядных целых чисел.\n");
    printf("Сортировка выполняется по неубыванию модулей элементов.\n");
    printf("Два метода сортировки: пирамидальная и быстрая(рекурсивный метод).\n");
    printf("\nКлючи командной строки:\n");
    printf("Для успешного запуска программы необходимо указать значения для каждого ключа, кроме ключа, отвечающего за вывод справочной информации.\n");
    printf("Для вывода справочной информации укажите только один ключ -H или --help\n");
    printf("Примеры корректного использования ключей:\n\n");
    printf("перед вводом ключей выполните: gcc prog.c -o a\n");
    printf("./a -N 5 -T 2 -P 5 -C 1 -W 1\n");
    printf("./a -N 1000 -T 3 -P 0 -C 0 -W 1\n");
    printf("./a -N 3 -T 4 -P 0 -C 0 -W 0\n");
    printf("./a -H\n");
    printf("./a --help\n");
    printf("./a --number 7 -T 1 -P 4 -C 0 -W 0\n");
    printf("./a -T 1 -P 4 -C 0 -W 0 -N 5\n");
    printf("./a -P 1 -T 4 -W 0 -C 0 -N 5\n");
    printf("\n\n");
    printf("    -H, --help      Вывод данной информации и завершение работы.\n");
    printf("    -N, --number      Введите чилсо элементов массива.\n");
    printf("    -T, --type      Тип генерации массива.\n");
    printf("        1   - Элементы уже упорядочены.\n");
    printf("        2   - Элементы упорядочены в обратном порядке.\n");
    printf("        3,4 - Расстановка элементов случайна.\n\n");
    printf("    -P, --print       Вывод указанного количества элементов массивов в исходном и конечном состояни.\n");
    printf("                      Если вывод не трубуеться, укажите значение 0.\n");
    printf("    -C, --counter     Вывод числа сравнений.\n");
    printf("        1  - Вывод нужен.\n");
    printf("        0  - Вывод не нужен.\n\n");
    printf("    -W, --swap        Вывод числа перемещений.\n");
    printf("        1  - Вывод нужен.\n");
    printf("        0  - Вывод не нужен.\n\n");


}

int main(int argc, char* argv[])
{
    int type_indx = 0;
    int num_indx = 0;
    int print_indx = 0;
    int cnt_indx = 0;
    int swp_indx = 0;
    long long int *arr;
    long long int* copy_arr;

    if(argc == 1)
    {
        fprintf(stderr, "\nОшибка: нельзя запусить программу без дополнительных ключей. Для вывода справочной информации укажите ключ -H или --help.\n");
        exit(1);
    }

    if(argc > 1 && (strcmp(argv[1], "-H") == 0 || strcmp(argv[1], "--help") == 0))
    {
        help_print();
        exit(0);
    }
    
    if(argc!= 11)
    {
        fprintf(stderr, "\nОшибка: неверноое количество параметров. Для вывода справочной информации укажите ключ -H или --help.\n");
        //help_print();
        exit(1);
    }
    /* узнаем ключ из командной строки*/
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-N") == 0 || strcmp(argv[i], "--number") == 0){
            num_indx = atoi(argv[++i]);
            if(num_indx < 1)
            {
                fprintf(stderr, "\nОшибка: неверное значание параметра -N.\n");
                //help_print();
                exit(1);
            }
        }else if(strcmp(argv[i], "-T") == 0 || strcmp(argv[i], "--type") == 0){
            type_indx = atoi(argv[++i]);
            if(type_indx < 1 || type_indx > 4)
            {
                fprintf(stderr, "\nОшибка: неверный диапазон значений параметра -T.\n");
                //help_print();
                exit(1);
            }
        }else if(strcmp(argv[i], "-P") == 0 || strcmp(argv[i], "--print") == 0){
            print_indx = atoi(argv[++i]);
            if(print_indx < 0)
            {
                fprintf(stderr, "\nОшибка: неверное значение параметра -P.\n");
                //help_print();
                exit(1);
            }
        }else if(strcmp(argv[i], "-C") == 0 || strcmp(argv[i], "--counter") == 0){
            cnt_indx = atoi(argv[++i]);
            if(cnt_indx < 0 || cnt_indx > 1)
            {
                fprintf(stderr, "\nОшибка: неверное значение параметра -C.\n");
                //help_print();
                exit(1);
            }
        }else if(strcmp(argv[i], "-W") == 0 || strcmp(argv[i], "--swap") == 0){
            swp_indx = atoi(argv[++i]);
            if(swp_indx < 0 || swp_indx > 1)
            {
                fprintf(stderr, "\nОшибка: неверное значение параметра -W.\n");
                //help_print();
                exit(1);
            } 
        }
    }

    if(print_indx > num_indx)
    {
        fprintf(stderr, "\nОшибка: в массиве содержиться только %d элементов\n", num_indx);
        //help_print();
        exit(1);
    }
    


    /*инициализация генератора случайных чисел*/
    srand(time(NULL));

    /*выделение памяти*/
    arr = malloc(num_indx * sizeof(long long int));
    if(arr == NULL)
    {
        fprintf(stderr, "\nОшибка выделения памяти для массива arr\n");
        exit(1);
    }

    copy_arr = malloc(num_indx*sizeof(long long int));
    if(copy_arr == NULL)
    {
        fprintf(stderr, "\nОшибка выделения памяти для массива copy_arr\n");
        exit(1);
    }

    

    /*создаем массив*/
    generation_array(num_indx, arr, type_indx);

    /*копируем массив*/
    for(int  i = 0; i < num_indx; ++i)
    {
        copy_arr[i] = arr[i];
    }

    if(print_indx)
        printf("\n\nПервые %d элемента(ов) исходного массива: \n\n", print_indx); 

    for(int i = 0; i < print_indx; ++i)
    {
        printf("%lld ", arr[i]);
        if((i != 0) && (i % 10 == 0))
            printf("\n\n");
        if(i == print_indx - 1)
                printf("\n");
    }

    /*сбрасываем счетчики*/
    cmp1 = 0; cmp2 = 0;
    swap1 = 0; swap2 = 0;

    /*быстрая сортировка*/
    q_abs(num_indx, arr);

    /*пирамидальная*/
    heapsort(num_indx, copy_arr);

    if(print_indx)
        printf("\n\nПервые %d элемента(ов) отсортированного массива: \n\n", print_indx); 

    for(int i = 0; i < print_indx; ++i)
    {
        printf("%lld ", arr[i]);
        if((i != 0) && (i % 10 == 0))
            printf("\n\n");
        if(i == print_indx - 1)
            printf("\n");
    }

    if(cnt_indx)
    {
        printf("\nчисло сравнений в быстрой сортировке: %lld\n", cmp1);
        printf("\nчисло сравнений в пирамидальной сортировке: %lld\n", cmp2);
    }

    if(swp_indx)
    {
        printf("\nчисло обменов в быстрой сортировке: %lld\n", swap1);
        printf("\nчисло обменов в пирамидальной сортировке: %lld\n", swap2);
    }

    

    free(arr);
    arr = NULL;

    free(copy_arr);
    copy_arr = NULL;

    return 0;
}
