#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "algoritmos.c" // Inclui o arquivo com os algoritmos de ordenação
#include "menu.c" // Inclui o arquivo com as funções de menu

// Definições de tamanhos de array
#define DEZ 10
#define CEM 100
#define MIL 1000
#define DEZ_MIL 10000
#define CEM_MIL 100000
#define UM_MILHAO 1000000

// Nomes dos algoritmos para criação de pastas
#define INSERTION "Insertion-Sort"
#define BUBBLE "Bubble-Sort"
#define SELECTION "Selection-Sort"
#define SHELL "Shell-Sort"
#define MERGE "Merge-Sort"
#define QUICK_V1 "Quick-Sort-V1"
#define QUICK_V2 "Quick-Sort-V2-Media"
#define QUICK_V3 "Quick-Sort-V3-Mediana"
#define QUICK_V4 "Quick-Sort-V4-Random"

// Função para gerar um número aleatório
int geraNumAleatorio() {
  time_t t;
  srand((unsigned) time(&t));
  return rand();
}

// Função para alocar um array dinamicamente
int* alocArray(int tamanho) {
  return (int*) malloc(tamanho * sizeof(int));
}

// Função para excluir resultados anteriores de um algoritmo
void excluiResultados(char *algoritmo) {
    char caminho[50];
    struct stat st = {0};
    strcpy(caminho, algoritmo);

    if (stat(caminho, &st) == 0) {
        char comando[100];
        sprintf(comando, "rmdir /S /Q %s", caminho);
        system(comando);
    }
}

// Função para criar pastas internas
void criaPastasInternas(char *caminho, char *sufix) {
  struct stat st = {0};
  char nomePasta[30];
  strcpy(nomePasta, caminho);
  strcat(nomePasta, sufix);
  if (stat(nomePasta, &st) == -1) {
      if (mkdir(nomePasta, 0700) == -1) {
        exit(1);
      }
    }
}

// Função para criar configuração inicial de pastas
void criaPastas(char *nomePasta) {
  struct stat st = {0};
  int tamanho = DEZ;
  char numEmStr[10];

  if (stat(nomePasta, &st) == -1) {
    mkdir(nomePasta, 0700);
  }

  while (tamanho <= UM_MILHAO) {
    char caminho[30];
    sprintf(numEmStr, "%d", tamanho);
    strcpy(caminho, nomePasta);
    strcat(caminho, "/");
    strcat(caminho, numEmStr);
    if (stat(caminho, &st) == -1) {
      if (mkdir(caminho, 0700) == -1) {
        exit(1);
      }
    }
    criaPastasInternas(caminho,"/crescente");
    criaPastasInternas(caminho,"/decrescente");
    criaPastasInternas(caminho,"/random");
    tamanho *= 10;
  }
  system("cls");
}

// Função para preencher um array em ordem crescente
void preencheArrayOrdemCrescente(int *array, int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  
  for (i = 0; i < tamanhoArray; i++) {
    array[i] = seed + i;
  }
}

// Função para preencher um array em ordem decrescente
void preencheArrayOrdemDecrescente(int *array,int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  
  for (i = 0; i < tamanhoArray; i++) {
    array[i] = seed - i;
  }
}

// Função para preencher um array em ordem aleatória
void preencheArrayOrdemAleatoria(int *array,int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  srand((unsigned) seed);
  for(i=0; i < tamanhoArray; i++) {
    array[i] =  rand();
  }
}

// Função para salvar um array em um arquivo
void salvaArquivo(int *array,int tamanho, char ordem, char *tipoDeArquivo, char *algoritmo) {
  FILE *ponteiroArquivo;
  char caminho[50], nomeArquivo[30], numEmStr[10];
  sprintf(numEmStr, "%d", tamanho); 
  strcpy(caminho,algoritmo);
  strcat(caminho,numEmStr);
  strcpy(nomeArquivo,tipoDeArquivo);
  switch (ordem) {
    case 'c':
      strcat(caminho,"/crescente/");
      break;
    case 'd':
      strcat(caminho,"/decrescente/");
      break;
    case 'r':
      strcat(caminho,"/random/");
      break;
    default:
      break;
  }
  
  strcat(nomeArquivo,".txt");
  strcat(caminho,nomeArquivo);

  ponteiroArquivo = fopen(caminho,"w");
  fprintf(ponteiroArquivo,"%d\n",tamanho);
  int i;
  for(i=0; i<tamanho; i++) {
    fprintf(ponteiroArquivo,"%d\n",array[i]);
  }
  fclose(ponteiroArquivo);
}

// Função para calcular o tempo de execução
double  calcTempExec(int *array, int tamanhoArray) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();

  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  return tempoExec;
}

// Função para salvar o tempo de execução em um arquivo
void salvaTempoExec(double tempo,int tamanho, char ordem, char *algoritmo) {
  FILE *ponteiroArquivo;
  char caminho[50], nomeArquivo[30], numEmStr[10];
  sprintf(numEmStr, "%d", tamanho); 
  strcpy(caminho,algoritmo);
  strcat(caminho,numEmStr);
  strcpy(nomeArquivo,"tempoexecucao");
  switch (ordem) {
    case 'c':
      strcat(caminho,"/crescente/");
      break;
    case 'd':
      strcat(caminho,"/decrescente/");
      break;
    case 'r':
      strcat(caminho,"/random/");
      break;
    default:
      break;
  }

  strcat(nomeArquivo,".txt");
  strcat(caminho,nomeArquivo);

  ponteiroArquivo = fopen(caminho,"w");

  fprintf(ponteiroArquivo,"%lf\n",tempo);

  fclose(ponteiroArquivo);

}

// Função para avaliar o algoritmo Insertion Sort
void avalia_insertionSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Insertion-Sort/");
// Executa o algoritmo
  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Insertion-Sort/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Insertion-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Selection Sort
void avalia_selectionSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Selection-Sort/");
// Executa o algoritmo
  selectionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Selection-Sort/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Selection-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Shell Sort
void avalia_shellSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Shell-Sort/");
// Executa o algoritmo
  shellSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Shell-Sort/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Shell-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
  
}

// Função para avaliar o algoritmo Bubble Sort
void avalia_bubbleSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Bubble-Sort/");
// Executa o algoritmo
  bubbleSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Bubble-Sort/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Bubble-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Merge Sort
void avalia_mergeSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Merge-Sort/");
// Executa o algoritmo
  mergeSort(array,0,tamanhoArray - 1);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Merge-Sort/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Merge-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Quick Sort (versão 1)
void avalia_quickSort_V1(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Quick-Sort-V1/");
// Executa o algoritmo
  quickSortV1(array,0,tamanhoArray - 1);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Quick-Sort-V1/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Quick-Sort-V1/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Quick Sort (versão 2 - Media)
void avalia_quickSort_V2(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Quick-Sort-V2-Media/");
// Executa o algoritmo
  quickSortV2(array,0,tamanhoArray - 1);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Quick-Sort-V2-Media/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Quick-Sort-V2-Media/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Quick Sort (versão 3 - Mediana)
void avalia_quickSort_V3(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Quick-Sort-V3-Mediana/");
// Executa o algoritmo
  quickSortV3(array,0,tamanhoArray - 1);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Quick-Sort-V3-Mediana/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Quick-Sort-V3-Mediana/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

// Função para avaliar o algoritmo Quick Sort (versão 4 - Random)
void avalia_quickSort_V4(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  // Salva o array de entrada em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Quick-Sort-V4-Random/");
// Executa o algoritmo
  quickSortV4(array,0,tamanhoArray - 1);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Salva o array ordenado em um arquivo
  salvaArquivo(array, tamanhoArray, ordem, "saida","Quick-Sort-V4-Random/");
  // Salva o tempo de execução em um arquivo
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Quick-Sort-V4-Random/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

int main () {
  int *array, tamanhoArray;
  char ordem;

// Chama a função para obter a escolha do algoritmo.
  int algoritmo = get_opAlgoritmo();

// Se a escolha do algoritmo for 0, retorna 0 e encerra o programa.
  if(algoritmo == 0) {
    return 0;
  }

// Se a escolha do algoritmo for 10, exclui os resultados anteriores de todos os algoritmos.
  if(algoritmo==10){
      excluiResultados(INSERTION);
      excluiResultados(SELECTION);
      excluiResultados(SHELL);
      excluiResultados(BUBBLE);
      excluiResultados(MERGE);
      excluiResultados(QUICK_V1);
      excluiResultados(QUICK_V2);
      excluiResultados(QUICK_V3);
      excluiResultados(QUICK_V4);
      printf("Resultados excluidos com sucesso.\n");
      return 0;
  }
  
  // Obtém o tamanho da entrada para teste.
  tamanhoArray = get_tamanhoArray();
  if(tamanhoArray == 0) {
    printf("Saindo...");
    return 0;
  }
  system("cls");

  // Obtém a escolha da ordem de ordenação.
  ordem = get_ordem();
  if(ordem == 's') {
    printf("Saindo...");
    return 0;
  }
  array = alocArray(tamanhoArray);
  if(array == NULL) {
    printf("Erro ao alocar array...");
    return 0;
  }
  // Preenche o array de acordo com a escolha de ordem.
  switch (ordem) { 
    case 'c':
      preencheArrayOrdemCrescente(array, tamanhoArray);
      break;
    case 'd':
      preencheArrayOrdemDecrescente(array, tamanhoArray);
      break;
    case 'r':
      preencheArrayOrdemAleatoria(array, tamanhoArray);
      break;
    default:
      break;
  }

// Avalia o algoritmo escolhido.
  switch(algoritmo){ 
    case 1:
      criaPastas(INSERTION);
      avalia_insertionSort(array,tamanhoArray,ordem);
      break;
    case 2:
      criaPastas(SELECTION);
      avalia_selectionSort(array,tamanhoArray,ordem);
      break;
    case 3:
      criaPastas(SHELL);
      avalia_shellSort(array,tamanhoArray,ordem);
      break;
    case 4:
      criaPastas(BUBBLE);
      avalia_bubbleSort(array,tamanhoArray,ordem);
      break;
    case 5:
      criaPastas(MERGE);
      avalia_mergeSort(array,tamanhoArray,ordem);
      break;
    case 6:
      criaPastas(QUICK_V1);
      avalia_quickSort_V1(array,tamanhoArray,ordem);
      break;
    case 7:
      criaPastas(QUICK_V2);
      avalia_quickSort_V2(array,tamanhoArray,ordem);
      break;
    case 8:
      criaPastas(QUICK_V3);
      avalia_quickSort_V3(array,tamanhoArray,ordem);
      break;
    case 9:
      criaPastas(QUICK_V4);
      avalia_quickSort_V4(array,tamanhoArray,ordem);
      break;
    default:
      break;
  }

  free(array);
  fflush(stdin);
  printf("\n");
  getchar();
  return 0;
}