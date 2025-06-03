#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int contador(int vetor[], int tamanho, int n) {
    int cont = 0;
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == n) {
            cont++;
        }
    }
    return cont;
}

int main() {
    int vetor[1000];
    int n, qtd;

    
    for (int i = 0; i < 1000; i++) {
        vetor[i] = rand() % 101;
        printf("%d\n", vetor[i]);
    }

   
    scanf("%d", &n);

    
    qtd = contador(vetor, 1000, n);

    
    printf("QTD: %d\n", qtd);

    return 0;
}