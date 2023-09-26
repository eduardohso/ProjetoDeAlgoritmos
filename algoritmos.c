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