#include <stdio.h>
#include <stdlib.h>

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