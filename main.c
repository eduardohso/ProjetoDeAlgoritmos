#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "algoritmos.c"
#include "menu.c"

#define DEZ 10
#define CEM 100
#define MIL 1000
#define DEZ_MIL 10000
#define CEM_MIL 100000
#define UM_MILHAO 1000000

#define INSERTION "Insertion-Sort"
#define BUBBLE "Bubble-Sort"
#define SELECTION "Selection-Sort"
#define SHELL "Shell-Sort"

int geraNumAleatorio() {
  time_t t;
  srand((unsigned) time(&t));
  return rand();
}

int* alocArray(int tamanho) {
  return (int*) malloc(tamanho * sizeof(int));
}

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

// cria pastas internas
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

// cria configuração inicial de pastas
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

// preenche array em ordem crescente
void preencheArrayOrdemCrescente(int *array, int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  
  for (i = 0; i < tamanhoArray; i++) {
    array[i] = seed + i;
  }
}

//preenche array em ordem descrescente
void preencheArrayOrdemDecrescente(int *array,int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  
  for (i = 0; i < tamanhoArray; i++) {
    array[i] = seed - i;
  }
}

//preenche array em ordem randomica
void preencheArrayOrdemAleatoria(int *array,int tamanhoArray) {
  int i;
  int seed = geraNumAleatorio();
  srand((unsigned) seed);
  for(i=0; i < tamanhoArray; i++) {
    array[i] =  rand();
  }
}

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

// calculo do tempo de execucção
double  calcTempExec(int *array, int tamanhoArray) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();

  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  return tempoExec;
}

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

void avalia_insertionSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Insertion-Sort/");

  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  salvaArquivo(array, tamanhoArray, ordem, "saida","Insertion-Sort/");
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Insertion-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

void avalia_selectionSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Selection-Sort/");

  selection_sort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  salvaArquivo(array, tamanhoArray, ordem, "saida","Selection-Sort/");
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Selection-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}

void avalia_shellSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Shell-Sort/");

  shellSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  salvaArquivo(array, tamanhoArray, ordem, "saida","Shell-Sort/");
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Shell-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
  
}

void avalia_bubbleSort(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Bubble-Sort/");

  bubbleSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  salvaArquivo(array, tamanhoArray, ordem, "saida","Bubble-Sort/");
  salvaTempoExec(tempoExec, tamanhoArray, ordem,"Bubble-Sort/");

  printf("Tempo de execucao: %f\n",tempoExec);
}


int main () {
  int *array, tamanhoArray;
  char ordem;

  int algoritmo = get_opAlgoritmo();

  if(algoritmo == 0) {
    return 0;
  }

  if(algoritmo==5){
      excluiResultados(INSERTION);
      excluiResultados(SELECTION);
      excluiResultados(SHELL);
      excluiResultados(BUBBLE);
      printf("Resultados excluidos com sucesso.\n");
      return 0;
  }
  
  tamanhoArray = get_tamanhoArray();
  if(tamanhoArray == 0) {
    printf("Saindo...");
    return 0;
  }
  system("cls");
  ordem = get_ordem();
  if(ordem == 's') {
    printf("Saindo...");
  }
  array = alocArray(tamanhoArray);
  if(array == NULL) {
    printf("Erro ao alocar array...");
    return 0;
  }
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
    default:
      break;
  }

  free(array);
  fflush(stdin);
  printf("\n");
  getchar();
  return 0;
}