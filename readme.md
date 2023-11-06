# Projeto de Algoritmos

Estas são instruções para recompilar o código, caso necessário. O arquivo `main.exe` já está configurado com as opções apropriadas.

## Compilar e Executar

Para compilar o programa no Windows e evitar problemas com os algoritmos QuickSort V1 e V4 para entradas acima de 100000, siga os passos abaixo:

1. Abra um terminal no diretório do projeto.

2. Utilize o GCC com o seguinte comando:

```bash
gcc -o main main.c -Wl,--stack,67108864
```

Isso irá compilar o arquivo `main.c` e gerar um executável chamado `main`.

3. Para executar o programa, utilize o seguinte comando:

```bash
./main
```

Essas instruções garantirão o funcionamento correto dos algoritmos, mesmo para entradas maiores.
