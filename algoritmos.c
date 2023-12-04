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

int* alloc_array(int tamanho) {
  return (int*) malloc(tamanho * sizeof(int));
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

int particaoV1(int *array, int baixo, int alto)
{
    int pivo = array[baixo];
    int i = baixo - 1;
    int j;

    for (j = baixo; j <= alto - 1; j++) {
        if (array[j] < pivo) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[alto]);
    return (i + 1);
}

void quickSortV1(int *array, int baixo, int alto)
{
    if (baixo < alto) {
        int pi = particaoV1(array, baixo, alto);
        quickSortV1(array, baixo, pi - 1);
        quickSortV1(array, pi + 1, alto);
    }
}


// ! QUICK SORT_V2-----------------------------------------------------------------

int particaoV2(int *array, int baixo, int alto)
{
    int media = (baixo + alto)/2; 
    int temp = array[media];
    array[media] = array[baixo];
    array[baixo] = temp;

    int pivo = array[baixo];
    int i = baixo - 1, j = alto + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivo);
  
        do {
            j--;
        } while (array[j] > pivo);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV2(int *array, int baixo, int alto)
{
    if (baixo < alto) {
        int pi = particaoV2(array, baixo, alto);
        quickSortV2(array, baixo, pi - 1);
        quickSortV2(array, pi + 1, alto);
    }
}

// ! QUICK SORT_V3-----------------------------------------------------------------

int particaoV3(int *array, int baixo, int alto)
{   
    int tamanho = sizeof(array) / sizeof(int);
    int mediana = ((tamanho/2) + (tamanho/2-1)) / 2 ;
    int temp = array[mediana];
    array[mediana] = array[baixo];
    array[baixo] = temp;

    int pivo = array[baixo];
    int i = baixo - 1, j = alto + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivo);
  
        do {
            j--;
        } while (array[j] > pivo);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV3(int *array, int baixo, int alto)
{
    if (baixo < alto) {
        int pi = particaoV3(array, baixo, alto);
        quickSortV3(array, baixo, pi - 1);
        quickSortV3(array, pi + 1, alto);
    }
}


// ! QUICK SORT_V4-----------------------------------------------------------------

int geraNumRandomRange(int range) { 
  srand(rand() * time(0));
  return rand() % range;
}

int particaoV4(int *array, int baixo, int alto)
{
    int random = geraNumRandomRange(alto);
    int temp = array[random];
    array[random] = array[baixo];
    array[baixo] = temp;

    int pivo = array[baixo];
    int i = baixo - 1, j = alto + 1;
  
    while (1) {
  
        do {
            i++;
        } while (array[i] < pivo);
  
        do {
            j--;
        } while (array[j] > pivo);
  
        if (i >= j)
            return j;
  
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}

void quickSortV4(int *array, int baixo, int alto)
{
    if (baixo < alto) {
        int pi = particaoV4(array, baixo, alto);
        quickSortV4(array, baixo, pi - 1);
        quickSortV4(array, pi + 1, alto);
    }
}

// ! HEAP SORT------------------------------------------------------------------------------
void printArray(int *arr, int n) {
    fflush(stdin);
    if (n > 1000) {
        char op;
        do {
            printf("Este vetor possui muitos elementos para imprimir na tela!!!\nDeseja exibir mesmo assim? (s/n) \n");
            scanf(" %c", &op);
            op = tolower(op);

            if (op != 'n' && op != 's') {
                printf("Escolha uma opcao valida!\n");
            }
        } while (op != 'n' && op != 's');

        if (op == 'n') return 0;
    }
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void heapfy(int *array, int tamanho, int i) {

  int menor = i;

  int esquerda = 2 * i + 1;

  int direita = 2 * i + 2;
  
  if (esquerda < tamanho && array[esquerda] < array[menor]) {
    menor = esquerda;
  }

  if (direita < tamanho && array[direita] < array[menor]) {
    menor = direita;
  }

  if (menor != i) {
    swap(&array[i], &array[menor]);
    heapfy(array, tamanho, menor);
  }
}

void constroi_heapMin(int *array, int tamanho) {
  int i;
  for (i = tamanho / 2 - 1; i >= 0; i--) {
    heapfy(array, tamanho, i);
  } 
}

void heapSort(int *array, int tamanho) {
  
  constroi_heapMin(array,tamanho);
  printf("Chamando a build: \n");
  printArray(array,tamanho);
  printf("\n");

  int i;
  for (i = tamanho - 1; i >= 0; i--) {
    swap(&array[0], &array[i]);
    heapfy(array, i, 0);
  }
}