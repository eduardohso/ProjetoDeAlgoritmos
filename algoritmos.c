#include <stdio.h>
#include <stdlib.h>

int geraNumAleatorioComRange(int range) {
  srand(rand() * time(0));
  return rand() % range;
}

void insertionSort(int *array, int array_size) {
    int i, key, j;
    for (i = 1; i < array_size; i++) {
        key = array[i];
        j = i - 1;
        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}