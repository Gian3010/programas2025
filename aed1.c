#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int codigo;
    char descricao[51];
    struct No* prox;
    struct No* ant;
} No;

No* inicio = NULL;

No* buscar(int codigo) {
    No* atual;
    if (!inicio) return NULL;
    atual = inicio;
    do {
        if (atual->codigo == codigo) return atual;
        atual = atual->prox;
    } while (atual != inicio);
    return NULL;
}

void adicionar(int codigo, char descricao[]) {
    No *novo, *ultimo;
    if (buscar(codigo)) {
        printf("Codigo ja existente!\n");
        return;
    }
    novo = (No*)malloc(sizeof(No));
    novo->codigo = codigo;
    strcpy(novo->descricao, descricao);
    if (!inicio) {
        novo->prox = novo;
        novo->ant = novo;
        inicio = novo;
    } else {
        ultimo = inicio->ant;
        ultimo->prox = novo;
        novo->ant = ultimo;
        novo->prox = inicio;
        inicio->ant = novo;
    }
}

void remover(int codigo) {
    No *alvo;
    if (!inicio) {
        printf("Codigo nao encontrado!\n");
        return;
    }
    alvo = buscar(codigo);
    if (!alvo) {
        printf("Codigo nao encontrado!\n");
        return;
    }
    if (alvo->prox == alvo) {
        free(alvo);
        inicio = NULL;
    } else {
        alvo->ant->prox = alvo->prox;
        alvo->prox->ant = alvo->ant;
        if (alvo == inicio) inicio = alvo->prox;
        free(alvo);
    }
}

void print_forward() {
    No *atual;
    if (!inicio) {
        printf("Lista vazia!\n");
        return;
    }
    atual = inicio;
    do {
        printf("Codigo: %d - %s\n", atual->codigo, atual->descricao);
        atual = atual->prox;
    } while (atual != inicio);
}

void print_reverse() {
    No *atual;
    if (!inicio) {
        printf("Lista vazia!\n");
        return;
    }
    atual = inicio->ant;
    do {
        printf("Codigo: %d - %s\n", atual->codigo, atual->descricao);
        atual = atual->ant;
    } while (atual != inicio->ant);
}

void search(int codigo) {
    No *encontrado;
    encontrado = buscar(codigo);
    if (encontrado) {
        printf("Codigo: %d - %s\n", encontrado->codigo, encontrado->descricao);
    } else {
        printf("Codigo nao encontrado!\n");
    }
}

void liberar_tudo() {
    No *atual, *prox;
    if (!inicio) return;
    atual = inicio->prox;
    while (atual != inicio) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    free(inicio);
    inicio = NULL;
}

int main() {
    int N, i, codigo, lidos;
    char linha[120], comando[20], descricao[51];
    i = 0;
    lidos = 0;
    scanf("%d\n", &N);
    if (N < 1 || N > 100) {
        printf("N nao e valido!\n");
        return 0;
    }
    while (fgets(linha, sizeof(linha), stdin)) {
        if (i >= N) break;
        i++;
        sscanf(linha, "%s", comando);
        if (strcmp(comando, "ADD") == 0) {
            sscanf(linha, "ADD %d %[^\n]", &codigo, descricao);
            adicionar(codigo, descricao);
        } else if (strcmp(comando, "REMOVE") == 0) {
            sscanf(linha, "REMOVE %d", &codigo);
            remover(codigo);
        } else if (strcmp(comando, "PRINT_FORWARD") == 0) {
            print_forward();
        } else if (strcmp(comando, "PRINT_REVERSE") == 0) {
            print_reverse();
        } else if (strcmp(comando, "SEARCH") == 0) {
            sscanf(linha, "SEARCH %d", &codigo);
            search(codigo);
        }
        lidos++;
    }
    if (lidos < N) {
        printf("N superior ao numero de comandos!\n");
    }
    liberar_tudo();
    return 0;
}
