/*COP 3502C Assignment 4 
This program is witten by Jose Urrea */

#include <stdio.h>
#include <stdlib.h> 
#include "leak_detector_c.h"

FILE *inFile, *outFile;

void mergeSort(int *arr, int left, int right);
void merge(int arr[], int left, int mid, int right);

int main(void) {
  atexit(report_mem_leak);
  
  inFile = fopen("in.txt", "r");
  outFile = fopen("out.txt", "w");
  int c;
  long long maxPages;
  fscanf(inFile,"%d", &c);

  for(int i=0; i<c; i++)
  {
    int j;
    int n=0;
    long long count=0;
    int totalBooks=0;

    fscanf(inFile, "%d %lld", &n, &maxPages);

    int *array = (int*)malloc(sizeof(int)*n);
    //printf("%d\n", n);
    for(int j=0; j<n; j++)
    {
      
      fscanf(inFile, "%d", &array[j]);
    }
    //printf("scanned\n");
    
    mergeSort(array, 0, n-1);
    
    for(int j=0; j<n; j++)
    {
      if(count+array[j] > maxPages)
        break;
      count +=array[j];
      totalBooks++;
    }
    

    printf("%d\n", totalBooks);
    fprintf(outFile, "%d\n", totalBooks);

    free(array);
  }
  
  return 0;
}

void merge(int arr[], int left, int mid, int right)
{
  int leftsize = mid - left +1;
  int rightsize = right-mid;

  int *L = malloc(leftsize *sizeof(int));

  int *R = malloc(rightsize *sizeof(int));

  for (int i=0; i<leftsize; i++)
  {
      L[i] = arr[left+i];
  }

  for(int j=0; j<rightsize; j++)
  {
    R[j] = arr[mid+1+j];
  }

  int i =0;
  int j =0;
  int k = left;

  while(i<leftsize && j<rightsize)
  {
    if(L[i]<=R[j])
    {
      arr[k] = L[i];
      k++;
      i++;
    }
    else
    {
      arr[k] = R[j];
      k++;
      j++;
    }
  }
  while(i<leftsize)
  {
    arr[k] = L[i];
    k++;
    i++;
  }
  while(j<rightsize)
  {
    arr[k] = R[j];
    k++;
    j++;
  }

  free(L);
  free(R);
}

void mergeSort(int *arr, int left, int right)
{
  if(right>left)
  {
    int mid = (left+right)/2;

    mergeSort(arr, left, mid);

    mergeSort(arr, mid+1, right);

    merge (arr, left, mid, right);
  }
}