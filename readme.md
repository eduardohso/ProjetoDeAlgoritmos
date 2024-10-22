# Projeto de Algoritmos

Este projeto foi desenvolvido como parte da disciplina SIN213 - Projeto de Algoritmos na Universidade Federal de Viçosa, Campus Rio Paranaíba.

## Descrição do Projeto

O objetivo deste projeto é a implementação e análise de diferentes algoritmos de ordenação, uma área fundamental na ciência da computação. O projeto explora algoritmos clássicos, como Insertion Sort, Bubble Sort, e Selection Sort, além de algoritmos mais avançados, como QuickSort, Merge Sort e Heap Sort.

Cada algoritmo foi implementado em linguagem C e testado com diferentes tamanhos de entradas, variando de 10 a 1.000.000 de elementos. As entradas foram ordenadas em três cenários: ordem crescente, decrescente e aleatória. Os resultados de tempo de execução foram analisados para determinar a eficiência de cada algoritmo em diferentes situações.

## Instruções para Compilar e Executar

Para compilar o programa no Windows e evitar problemas com os algoritmos QuickSort V1 e V4 para entradas acima de 100000, siga os passos abaixo:

1. Abra um terminal no diretório do projeto.

2. Utilize o GCC com o seguinte comando para compilar o código:

```bash
gcc -o main main.c -Wl,--stack,67108864
```

Isso irá compilar o arquivo `main.c` e gerar um executável chamado `main`.

3. Para executar o programa, utilize o seguinte comando:

```bash
./main
```

Essas instruções garantirão o funcionamento correto dos algoritmos, mesmo para entradas maiores.
