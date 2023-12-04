
#include <stdio.h>
#include <stdlib.h>
#define DEZ 10
#define CEM 100
#define MIL 1000
#define DEZ_MIL 10000
#define CEM_MIL 100000
#define UM_MILHAO 1000000

int get_opAlgoritmo() {
  int opcao;
  system("cls");
  do {
    fflush(stdin);
    printf("<-- Escolha um Algoritmo -->\n");
    printf("-> [1] - Insertion Sort\n");
    printf("-> [2] - Selection Sort\n");
    printf("-> [3] - Shell Sort\n");
    printf("-> [4] - Bubble Sort\n");
    printf("-> [5] - Merge Sort\n");
    printf("-> [6] - Quick Sort V1\n");
    printf("-> [7] - Quick Sort V2-Media\n");
    printf("-> [8] - Quick Sort V3-Mediana\n");
    printf("-> [9] - Quick Sort V4-Random\n");
    printf("-> [10] - Heap Sort\n");
    printf("-> [11] - Excluir TODOS os resultados anteriores\n");
    printf("-> [0] - Sair\n");
    printf("<-------------------------->\n");
    printf("-> ");
    scanf("%d",&opcao);
    if(opcao < 0 || opcao > 11) {
      system("cls");
      printf("#*# Escolha uma opcao valida! #*#\n\n");
    }
  } while(opcao < 0 || opcao > 11);
  return opcao;
}

int get_tamanhoArray() {
  int opcao;
  system("cls");
    do {
      fflush(stdin);
      printf("<-- Escolha o tamanho da amostra para testar -->\n");
      printf("-> [1] - 10\n");
      printf("-> [2] - 100\n");
      printf("-> [3] - 1000\n");
      printf("-> [4] - 10000\n");
      printf("-> [5] - 100000\n");
      printf("-> [6] - 1000000\n");
      printf("-> [0] - Sair\n");
      printf("<---------------------------------------------->\n");
      printf("-> ");
      scanf("%d",&opcao);
      if(opcao < 0 || opcao > 6) {
        system("cls");
        printf("#*# Escolha uma opcao valida! #*#\n\n");
      }
    } while( opcao < 0 || opcao > 6 );
  switch (opcao) {
    case 1:
      return DEZ;
      break;
    case 2:
      return CEM;
      break;
    case 3:
      return MIL;
      break;
    case 4:
      return DEZ_MIL;
      break;
    case 5:
      return CEM_MIL;
      break;
    case 6:
      return UM_MILHAO;
      break;
    default:
      break;
  }
  return 0;
}

char get_ordem() {
  char opcao;
  system("cls");
  do {
    fflush(stdin);
    printf("<-- Escolha um tipo de ordenacao -->\n");
    printf("-> [c] - Crescente\n");
    printf("-> [d] - Decrescente\n");
    printf("-> [r] - Random\n");
    printf("-> [s] - Sair\n");
    printf("<---------------------------------->\n");
    printf("-> ");
    opcao = getchar();
    if(opcao != 'c' && opcao != 'd'  && opcao != 'r'  && opcao != 's') {
      system("cls");
      printf("#*# Escolha uma opcao valida! #*#\n\n");
    }
  } while( opcao != 'c' && opcao != 'd'  && opcao != 'r'  && opcao != 's' );
  return opcao;
}

int get_opcoesHeap() {
  system("cls || clear");
  int opcao;
    do {
      printf("                                 HEAP-SORT                                \n");
      printf("<----------------------------------------------------------------------->\n");
      printf("Escolha a funcao do heap-sort que deseja testar: \n");
      printf("-> [1] - Heap Minimo\n");
      printf("-> [2] - Heap Extract Min\n");
      printf("-> [3] - Heap Increase Key\n");
      printf("-> [4] - Heap Max Insert\n");
      printf("-> [0] - Nenhum\n");
      printf("<----------------------------------------------------------------------->\n");
      printf("-> ");
      scanf("%d",&opcao);
      if(opcao < 0 && opcao > 4) {
        printf("Escolha uma opcao valida!\n");
      }
    } while( opcao < 0 && opcao > 4 );
  return opcao;
}