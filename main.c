#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

int* alocArray(int tamanho) {
  return (int*) malloc(tamanho * sizeof(int));
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
void criaPastasDeConfig(char *nomePasta) {
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


// função que calcula tempo de execucção
double  CalcTempExec(int *array, int tamanhoArray) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();

  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  return tempoExec;
}

int geraNumAleatorio() {
  time_t t;
  srand((unsigned) time(&t));
  return rand();
}

// popula array em ordem crescente
void populaArrayOrdemCrescente(int *array,int tamanhoArray) {
  int seed = geraNumAleatorio();
  int i;
  for(i = 0; i < tamanhoArray; i++) {
    array[i] = seed + i;
  }
}

//popula array em ordem descrescente
void populaArrayOrdemDecrescente(int *array,int tamanhoArray) {
  int seed = geraNumAleatorio();
  int i;
  int quantElementos = tamanhoArray - 1 ; 
  for(i =0 ; i <= quantElementos; i++) {
    array[i] = seed + (quantElementos - i);
  }
}

// ordem randomica
void populaArrayOrdemAleatoria(int *array,int tamanhoArray) {
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

void salvaTempoExecArquivo(double tempo,int tamanho, char ordem, char *algoritmo) {
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

  fprintf(ponteiroArquivo,"%d\n",tamanho);
  fprintf(ponteiroArquivo,"%lf\n",tempo);

  fclose(ponteiroArquivo);

}

void avalia_insertionSOrt(int *array, int tamanhoArray, char ordem) {
  clock_t inicio, fim;
  double tempoExec;
  inicio = clock();
  salvaArquivo(array, tamanhoArray, ordem, "entrada","Insertion-Sort/");

  insertionSort(array,tamanhoArray);

  fim = clock();
  tempoExec = (double)(fim - inicio) / CLOCKS_PER_SEC;
  salvaArquivo(array, tamanhoArray, ordem, "saida","Insertion-Sort/");
  salvaTempoExecArquivo(tempoExec, tamanhoArray, ordem,"Insertion-Sort/");
}

int main () {
  criaPastasDeConfig(INSERTION);

  int *array, tamanhoArray;
  char ordem;

  int algoritmo = get_opAlgoritmo();
  if(algoritmo == 0) {
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
      populaArrayOrdemCrescente(array, tamanhoArray);
      break;
    case 'd':
      populaArrayOrdemDecrescente(array, tamanhoArray);
      break;
    case 'r':
      populaArrayOrdemAleatoria(array, tamanhoArray);
      break;
    default:
      break;
  }

  avalia_insertionSOrt(array,tamanhoArray,ordem);

  free(array);
  return 0;
}