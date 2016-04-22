#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printArray(int * array, int size);
void sort(int list[], int n);

void printArray(int * array, int size)
{
    int i;
    printf("[ ");
    for (i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("]\n");
}

int main(int argc,char * * argv)
{
    //printf("----------------------------------\n");
    int size = 0;
    size = atoi(argv[1]);
    int * list = malloc(size*sizeof(int));
    int i;
    //for (i = 0;i < size;i++) if(i<size-10) list[i] = (int) (rand()%10-5)*(rand()%((i+1)*10))/2; else list[i]=(int) (rand()%10-5)*rand()/5;
    srand((unsigned)time(NULL));
    for (i = 0;i < size;i++) list[i]=(rand()>rand()?1:-1)*rand()/10;
    printf("\nUnsorted List:");
    printArray(&list[0], size);
    
    clock_t st;
    clock_t ed;
    st = clock();
    sort(list, size);
    ed = clock();
    
    printf("Sorted List:");
    printArray(&list[0], size);
    printf("time = %f\n",(double) (ed-st)/CLOCKS_PER_SEC);
    
    return 0;
}