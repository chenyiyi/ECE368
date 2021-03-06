//
//  main.c
//  sort
//
//  Created by Yi on 15/3/13.
//  Copyright (c) 2015年 Yi. All rights reserved.
//
// Chen Yiyi Id:0026406971
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void sort(int list[], int n);
void RadixCountingSort(long int* npIndex, int nMax, int nLen, long int* pnCount, long int* pnSort, long int list[]);
void RadixSort(int nLen,long int list[]);
void CountingSort(long int list[], int nLen, long int range, long int min);

void sort(int list[], int n)
{
  long int smallest = (long int)list[0];
  long int biggest = (long int)list[0];
  long int range = 0;
  int i;
  long int* list2 = (long int*)malloc(sizeof(long int) * n); 
  memcpy(list2, list, sizeof(long int)*(n+1));
  long int diff;
  long int smallestsecond;
  //  int h;
  for (i =0; i<n; i++) {
    if(list2[i] < smallest){
      smallest = list2[i];
    }else if(list2[i] > biggest){
      biggest = list2[i];
    }
  }
  for(i =0; i<n; i++){
    if(smallest<0){
      list2[i] = list2[i] - smallest;
    }
    else{
      list2[i] = list2[i] + smallest;
    }
  }
  range = biggest - smallest;
  if(smallest<0){
    smallestsecond = list2[0] - smallest;
  }
  else{
    smallestsecond = list2[0] + smallest;
  }
  diff = range/n;
  for (i =0; i<n; i++) {
    if(list2[i] < smallestsecond){
      smallestsecond = list2[i];
    }
  }
  //printf("smallest:%d\n biggest:%d\n", smallestsecond, biggest);
  if(diff > 70){
    RadixSort(n, &list2[0]);
  }
  else{
    CountingSort(&list2[0], n, range, smallestsecond);
  }
  for(i =0; i<n; i++){
   if(smallest<0){
      list2[i] = list2[i] + smallest;
    }
    else{
      list2[i] = list2[i] - smallest;
    }
  }
  memcpy(&list[0], &list2[0], sizeof(int)*(n+1));
  free(list2);
}

void RadixCountingSort(long int* arrDataRadix, int nRadix, int nLen, long int* pnCount, long int* pnSort, long int list[])
{
    int i;
    memset(pnCount, 0, sizeof(long int) * nRadix);
    for (i = 0; i < nLen; ++i)
      {
        ++pnCount[arrDataRadix[i]];
      }
    for (i = 1; i < nRadix; ++i)
      {
        pnCount[i] += pnCount[i - 1];
      }
    for (i = nLen - 1; i >= 0; --i)
      {
	--pnCount[arrDataRadix[i]];
	pnSort[pnCount[arrDataRadix[i]]] = list[i];
      }
    // Copy the array to sorted array.
    memcpy( &list[0], &pnSort[0], sizeof(long int) * nLen );
}

//Counting sort.
void CountingSort(long int* list, int nLen, long int range, long int min)
{
    int i =0 ;
    int h = 0;
    int f = 0;
    long int* pnCount = (long int*)calloc(range+1, sizeof(long int));   
    //int * pnSort = (int*)calloc(nLen, sizeof(int));
    for (i = 0; i < nLen; i++)
    {
      pnCount[list[i]-min] ++;
    }
    for (i = 0; i < (range+1); i++)
      {
	for (h = 0; h < pnCount[i]; h++)
	  {
	    list[f++] = i + min;
	  }
      }
    free(pnCount);
    //free(pnSort);
    
}

// Radix sort.
void RadixSort(int nLen, long int list[])
{
    int nRadix = 256;   
    long int* arrDataRadix = (long int*)malloc(sizeof(long int) * nLen);    
    long int* pnCount = (long int*)malloc(sizeof(long int) * nRadix);   
    long int* pnSort = (long int*)malloc(sizeof(long int) * nLen);
    int nIsOk = 0;
    //int shiftLoc = 0;
    int i;
    int factor = 1;
    while (!nIsOk)
    {
        nIsOk = 1;
        for (i = 0; i < nLen; ++i)
        {
            arrDataRadix[i] = list[i]/factor %10;
            if ( arrDataRadix[i] > 0 )
            {
                nIsOk = 0;
            }
        }
        if (nIsOk)
        {
            break;
        }
        factor = factor *10;
        RadixCountingSort( arrDataRadix, nRadix, nLen, pnCount, pnSort, list );
    }
    free(arrDataRadix);
    free(pnCount);
    free(pnSort);
}

