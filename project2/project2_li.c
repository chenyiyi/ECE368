//
//  project2.c
//  project2
//
//  Created by Lee Chrison Moon on 15/3/13.
//  Copyright (c) 2015年 Lee Chrison Moon. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>

void radix_sort(int list[], int n, int max, int min, int count_n, int count_p);
void counting_sort(int *list, int n, int max, int min,int count_n, int count_p);

void sort(int list[], int n){
    
    int i;
    int min;
    int max;
    int count_n = 0;
    int count_p = 0;

    
    min = list[0];
    max = list[0];
    for(i = 0; i < n; i++){
        if(min > list[i])
            min = list[i];
        if(max < list[i])
            max = list[i];
        if(list[i] < 0 )
            count_n++;
        if(list[i] >= 0 )
            count_p++;
    }
    long int range = (long int)max - (long int)min;
    if(range / n >= 50){
        radix_sort(list,n,max,min,count_n,count_p);
    }
    else{
        counting_sort(list,n,max,min,count_n,count_p);
    }
}
void radix_sort(int list[], int n, int max, int min,int count_n, int count_p){
    int i;
    int *a;
    int *b;
    int ii = 0;
    a = (int *)malloc(sizeof(int)* (count_p+1));
    b = (int *)malloc(sizeof(int)* (count_n+1));
    int significantDigit = 1;
    
    int *arr_p;
    int *arr_n;
    arr_n = (int*) malloc(sizeof(int)* (count_n+1));
    arr_p = (int*) malloc(sizeof(int)* (count_p+1));
    
    int j = 0;
    int k = 0;
    
    for(i = 0; i < n; i++){
        if(list[i] < 0){
            arr_n[j] = list[i] - min;
            j++;
        }
        if(list[i] >= 0){
            arr_p[k] = list[i];
            k++;
        }
    }
    
    while ((-min) / significantDigit > 0){
        
        int bucket1[10] = {0};
        
        for (i = 0; i < count_n; i++)
            bucket1[arr_n[i] / significantDigit % 10]++;
        
        for (i = 1; i < 10; i++)
            bucket1[i] += bucket1[i - 1];
        
        for (i = count_n - 1; i >= 0; i--)
            b[--bucket1[(arr_n[i] / significantDigit) % 10]] = arr_n[i];
        
        for (i = 0; i < count_n; i++){
            arr_n[i] = b[i];
        }
        
        significantDigit *= 10;
        
    }
    for(i = 0; i < count_n;i++){
        list[ii] = arr_n[i] + min;
        ii++;
    }
    
    while (max / significantDigit > 0){
        
        int bucket2[10] = {0};
        
        for (i = 0; i < count_p; i++)
            bucket2[arr_p[i] / significantDigit % 10]++;
        
        for (i = 1; i < 10; i++)
            bucket2[i] += bucket2[i - 1];
        
        for (i = count_p - 1; i >= 0; i--)
            a[--bucket2[(arr_p[i] / significantDigit) % 10]] = arr_p[i];
        
        for (i = 0; i < count_p; i++){
            arr_p[i] = a[i];
        }
        
        significantDigit *= 10;

    }
    for(i = 0; i < count_p;i++){
        list[ii] = arr_p[i];
        ii++;
    }
    
    free(a);
    free(b);
    free(arr_p);
    free(arr_n);
}
    
void counting_sort(int *list, int n, int max, int min, int count_n, int count_p){
    int *arr_p;
    int *arr_n;
    int i;
    arr_n = (int*) malloc(sizeof(int)* (count_n+1));
    arr_p = (int*) malloc(sizeof(int)* (count_p+1));
    
    int j = 0;
    int k = 0;

    for(i = 0; i < n; i++){
        if(list[i] < 0){
            arr_n[j] = list[i] - min;
            j++;
        }
        if(list[i] >= 0){
            arr_p[k] = list[i];
            k++;
        }
    }
    int *sort_n = calloc( - min + 1, sizeof(int));
    int *sort_p = calloc(max+1, sizeof(int));

    for(i = 0; i < j; i++){
        sort_n[arr_n[i]]++;
    }
    for(i = 0; i < k; i++){
        sort_p[arr_p[i]]++;
    }
    int ii = 0;
    for(i = 0; i <= (- min); i++){
        if(sort_n[i] > 0){
            list[ii] = i + min;
            ii++;
        }
    }
    for(i = 0; i <= max; i++){
        if(sort_p[i] > 0){
            list[ii] = i;
            ii++;
        }
    }
    free(arr_n);
    free(arr_p);
    free(sort_n);
    free(sort_p);
}
