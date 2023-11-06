#include <stdio.h>
#include <stdlib.h>

// ! INSERTION SORT----------------------------------------------
void insertionSort(int *array, int tamanhoArray) {
    int i, j, chave;
    for (i = 1; i < tamanhoArray; i++) {
        chave = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > chave)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = chave;
    }
}

// ! SELECTION SORT----------------------------------------------

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void selectionSort(int *array, int tamanho)
{
    int i, j, min_idx;
 
    for (i = 0; i < tamanho-1; i++)
    {
        min_idx = i;
        for (j = i+1; j < tamanho; j++)
        if (array[j] < array[min_idx])
            min_idx = j;

        if(min_idx!=i)
            swap(&array[min_idx], &array[i]);
    }
}

// ! SHELL SORT----------------------------------------------

int shellSort(int *array, int tamanho)
{
    int gap;
    for (gap = tamanho/2; gap > 0; gap /= 2)
    {
		int i;
        for (i = gap; i < tamanho; i += 1)
        {
            int temp = array[i];
            int j;            
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
                array[j] = array[j - gap];
            array[j] = temp;
        }
    }
    return 0;
}

// ! BUBBLE SORT----------------------------------------------

void bubbleSort(int *array, int tamanho) 
{
  int i, j;
  for (i = 0; i < tamanho - 1; i++) {
    for (j = 0; j < tamanho - i - 1; j++) {
      if (array[j] > array[j + 1]) {
        swap(&array[j], &array[j + 1]);
      }
    }
  }
}

int* alloc_array(int size) {
  return (int*) malloc(size * sizeof(int));
}

// ! MERGE SORT---------------------------------------------

void merge(int *array, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = alloc_array(n1);
    if(L == NULL) {
        printf("Erro ao alocar memoria...\n");
        exit(1);
    }

    int *R = alloc_array(n2);
    if(R == NULL) {
        printf("Erro ao alocar memoria...\n");
        exit(1);
    }
    
    for (i = 0; i < n1; i++)
        L[i] = array[l + i];
    for (j = 0; j < n2; j++)
        R[j] = array[m + 1 + j];
 
   
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            array[k] = L[i];
            i++;
        }
        else {
            array[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        array[k] = L[i];
        i++;
        k++;
    }
 
    while (j < n2) {
        array[k] = R[j];
        j++;
        k++;
    }
}
 
void mergeSort(int *array, int l, int r)
{
    if (l < r) {

        int m = l + (r - l) / 2;
 
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
 
        merge(array, l, m, r);
    }
}

// ! QUICK SORT_V1-----------------------------------------------------------------

int particaoV1(int *array, int low, int high)
{
    int pivot = array[low];
    int i = low - 1;
    int j;

    for (j = low; j <= high - 1; j++) {
        if (array[j] < pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSortV1(int *array, int low, int high)
{
    if (low < high) {
        int pi = particaoV1(array, low, high);
        quickSortV1(array, low, pi - 1);
        quickSortV1(array, pi + 1, high);
    }
}


// ! QUICK SORT_V2-----------------------------------------------------------------

int particaoV2(int *array, int low, int high)
{
    int media = (low + high)/2; 
    int temp = array[media];
    array[media] = array[low];
    array[low] = temp;

    int pivot = array[low];
    int i = low - 1, j = high + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivot);
  
        do {
            j--;
        } while (array[j] > pivot);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV2(int *array, int low, int high)
{
    if (low < high) {
        int pi = particaoV2(array, low, high);
        quickSortV2(array, low, pi - 1);
        quickSortV2(array, pi + 1, high);
    }
}

// ! QUICK SORT_V3-----------------------------------------------------------------

int particaoV3(int *array, int low, int high)
{   
    int size = sizeof(array) / sizeof(int);
    int mediana = ((size/2) + (size/2-1)) / 2 ;
    int temp = array[mediana];
    array[mediana] = array[low];
    array[low] = temp;

    int pivot = array[low];
    int i = low - 1, j = high + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivot);
  
        do {
            j--;
        } while (array[j] > pivot);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV3(int *array, int low, int high)
{
    if (low < high) {
        int pi = particaoV3(array, low, high);
        quickSortV3(array, low, pi - 1);
        quickSortV3(array, pi + 1, high);
    }
}


// ! QUICK SORT_V4-----------------------------------------------------------------

int geraNumRandomRange(int range) { 
  srand(rand() * time(0));
  return rand() % range;
}

int particaoV4(int *array, int low, int high)
{
    int random = geraNumRandomRange(high);
    int temp = array[random];
    array[random] = array[low];
    array[low] = temp;

    int pivot = array[low];
    int i = low - 1, j = high + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivot);
  
        do {
            j--;
        } while (array[j] > pivot);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV4(int *array, int low, int high)
{
    if (low < high) {
        int pi = particaoV4(array, low, high);
        quickSortV4(array, low, pi - 1);
        quickSortV4(array, pi + 1, high);
    }
}