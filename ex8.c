#include <stdio.h>

#define MAX 100

void leituraMatriz(int M1[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &M1[i][j]);
        }
    }
}

void quadradoElementosMatriz(int M1[MAX][MAX], int M2[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            M2[i][j] = M1[i][j] * M1[i][j];
        }
    }
}

void imprimeMatriz(int matriz[MAX][MAX], int n) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

void multiplicaMatriz(int M1[MAX][MAX], int M2[MAX][MAX], int M3[MAX][MAX], int n) {
    int i, j, k;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            M3[i][j] = 0;
            for (k = 0; k < n; k++) {
                M3[i][j] += M1[i][j] * M2[k][j];
            }
        }
    }
}

void tracoMatriz(int M3[MAX][MAX], int n) {
    int i, traco = 0;
    for (i = 0; i < n; i++) {
        traco += M3[i][i];
    }
    printf("Traco: %d\n", traco);
}

int main() {
    int M1[MAX][MAX], M2[MAX][MAX], M3[MAX][MAX];
    int n;

    printf("Digite a dimensao da matriz: ");
    scanf("%d", &n);

    printf("Digite os elementos da matriz M1 (%dx%d):\n", n, n);
    leituraMatriz(M1, n);

    quadradoElementosMatriz(M1, M2, n);

    printf("Matriz M2:\n");
    imprimeMatriz(M2, n);

    multiplicaMatriz(M1, M2, M3, n);

    printf("Matriz M3:\n");
    imprimeMatriz(M3, n);

    tracoMatriz(M3, n);

    return 0;
}