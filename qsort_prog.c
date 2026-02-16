#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static void help_print(void)
{
    printf("Программа: Экспериментальное сравнение методов сортировки\nОписание:\n\n");
    printf("Программа реализует методы сортировки массивов 64-разрядных целых чисел.\n");
    printf("Сортировка выполняется по неубыванию модулей элементов.\n");
    printf("\nКлючи командной строки:\n");
    printf("    -H, --help        Вывод этой справки и завершение работы.\n");
    printf("    -T, --type        Тип генерации массива.\n");
    printf("    1   - Элементы уже упорядочены\n");
    printf("    2   - Элементы упорядочены в обратном порядке\n");
    printf("    3,4 - Расстановка элементов случайна\n\n");
    printf("    -M, --method       Метод сравнения\n");
    printf("    1   - Быстрая сортировка\n");
    printf("    2   - Пирамидальная сортировка\n\n");




}

int main(int argc, char* argv[])
{
    int help_indx = 0;
    int type_indx = 0;
    int method_indx = 0;
    

    /* узнаем фргумент командной строки*/
    for(int i = 1; i < argc; ++i){
        if(strcmp(argv[i], "-H") == 0 || strcmp(argv[i], "--help") == 0)
        {
            help_indx = 1;
            break;
        }else if(strcmp(argv[i], "-T=") == 0 || strcmp(argv[i], "--type=") == 0){
            type_indx = atoi(argv[++i]);
        }else if(strcmp(argv[i], "-M=") == 0 || strcmp(argv[i], "--method=") == 0){
            method_indx = atoi(argv[++i]);
        }
    }

    if(help_indx)
    {
        help_print();
        return 0;
    }

    if(method_indx){
        printf("%d",  method_indx);
    }
     
    if(type_indx){
        printf("%d", type_indx);
    }
    return 0;
}
