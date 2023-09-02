
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
    printf("<-- Escolha um algoritmo -->\n");
    printf("-> [1] - Insertion-sort     \n");
    printf("-> [0] - Sair               \n");
    printf("<-------------------------->\n");
    printf("-> ");
    scanf("%d",&opcao);
    if(opcao < 0 || opcao > 1) {
      system("cls");
      printf("#*# Escolha uma opcao valida! #*#\n\n");
    }
  } while(opcao < 0 || opcao > 1); // checa se opção escolhida é valida para sair do loop
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
    case 0:
      return 0;
      break;
    default:
      break;
  }
}

char get_ordem() {
  char opcao;
  system("cls");
  do {
    fflush(stdin);
    printf("<-- Escolha um tipo de ordenacao -->\n");
    printf("-> [c] - Crescente   \n");
    printf("-> [d] - Decrescente \n");
    printf("-> [r] - Aleatoria   \n");
    printf("-> [s] - Sair        \n");
    printf("<---------------------------------->\n");
    printf("-> ");
    opcao = getchar();
    if(opcao != 'c' && opcao != 'd'  && opcao != 'r'  && opcao != 's') {
      system("cls");
      printf("#*# Escolha uma opcao valida! #*#\n\n");
    }
  } while( opcao != 'c' && opcao != 'd'  && opcao != 'r'  && opcao != 's' ); // checa se opção escolhida é valida para sair do loop
  return opcao;
}