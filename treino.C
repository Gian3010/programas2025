#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float din;    
    int qtd;      
    float *P;   
} Cliente;

void leituraClientes(Cliente *clientes, int N) {
    for (int i = 0; i < N; i++) {
        do {
            scanf("%f", &clientes[i].din);
        } while (clientes[i].din < 0);

        do {
            scanf("%d", &clientes[i].qtd);
        } while (clientes[i].qtd < 0 || clientes[i].qtd > 100);

        if (clientes[i].qtd > 0) {
            clientes[i].P = (float *)malloc(clientes[i].qtd * sizeof(float));
            for (int j = 0; j < clientes[i].qtd; j++) {
                do {
                    scanf("%f", &clientes[i].P[j]);
                } while (clientes[i].P[j] < 0);
            }
        } else {
            clientes[i].P = NULL;
        }
    }
}

void calcularCompra(Cliente *clientes, int N) {
    for (int i = 0; i < N; i++) {
        float dinheiro = clientes[i].din;
        int livrosComprados = 0;

        for (int j = 0; j < clientes[i].qtd; j++) {
            if (dinheiro >= clientes[i].P[j]) {
                dinheiro -= clientes[i].P[j];
                livrosComprados++;
            }
        }

        printf("%d %.2f\n", livrosComprados, dinheiro);
    }
}

int main() {
    int N;

    do {
        scanf("%d", &N);
    } while (N < 1 || N > 100);

    Cliente *clientes = (Cliente *)malloc(N * sizeof(Cliente));

    leituraClientes(clientes, N);
    calcularCompra(clientes, N);

    for (int i = 0; i < N; i++) {
        if (clientes[i].P != NULL) {
            free(clientes[i].P);
        }
    }
    free(clientes);

    return 0;
}
