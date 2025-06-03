// Gerenciador Avançado de Pilhas Nomeadas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *prox;
} No;

typedef struct Pilha {
    char nome[51];
    No *topo;
    struct Pilha *prox;
} Pilha;

Pilha *lista = NULL;

// Função para encontrar uma pilha pelo nome
Pilha* encontrarPilha(char *nome) {
    Pilha *p = lista;
    while (p != NULL) {
        if (strcmp(p->nome, nome) == 0) {
            return p;
        }
        p = p->prox;
    }
    return NULL;
}

// Remove uma pilha da lista e libera memória
void removerPilha(char *nome) {
    Pilha *anterior = NULL, *atual = lista;
    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }
    if (atual != NULL) {
        if (anterior == NULL) lista = atual->prox;
        else anterior->prox = atual->prox;

        No *temp = atual->topo;
        while (temp != NULL) {
            No *del = temp;
            temp = temp->prox;
            free(del);
        }
        free(atual);
    }
}

// Comando NOME:INIT
void comandoInit(char *nome) {
    if (encontrarPilha(nome)) return; // já existe, não faz nada
    Pilha *nova = malloc(sizeof(Pilha));
    strcpy(nova->nome, nome);
    nova->topo = NULL;
    nova->prox = lista;
    lista = nova;
}

// Comando NOME:PUSH x
void comandoPush(char *nome, int x) {
    Pilha *p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    No *novo = malloc(sizeof(No));
    novo->valor = x;
    novo->prox = p->topo;
    p->topo = novo;
}

// Comando NOME:POP
void comandoPop(char *nome) {
    Pilha *p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    if (p->topo == NULL) {
        printf("Pilha %s vazia!\n", nome);
        exit(0);
    }
    No *temp = p->topo;
    p->topo = temp->prox;
    free(temp);

    if (p->topo == NULL)
        removerPilha(nome);
}

// Comando NOME:TOP
void comandoTop(char *nome) {
    Pilha *p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    if (p->topo == NULL) {
        printf("Pilha %s vazia!\n", nome);
        exit(0);
    }
    printf("%d\n", p->topo->valor);
}

// Comando NOME:PRINT
void comandoPrint(char *nome) {
    Pilha *p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }

    printf("[");
    No *n = p->topo;
    while (n != NULL) {
        printf("%d", n->valor);
        if (n->prox) printf(", ");
        n = n->prox;
    }
    printf("]\n");
}

// Comando SHOW
void comandoShow() {
    Pilha *p = lista;
    while (p != NULL) {
        printf("%s: [", p->nome);
        No *n = p->topo;
        while (n != NULL) {
            printf("%d", n->valor);
            if (n->prox) printf(", ");
            n = n->prox;
        }
        printf("]\n");
        p = p->prox;
    }
}

// Comando MERGE nomeA nomeB
void comandoMerge(char *a, char *b) {
    Pilha *pa = encontrarPilha(a);
    Pilha *pb = encontrarPilha(b);
    if (!pa || !pb) {
        printf("Erro: pilhas nao encontradas!\n");
        exit(0);
    }

    // Inverter pilha B antes de empilhar em A para manter ordem
    No *nova = NULL;
    No *n = pb->topo;
    while (n != NULL) {
        No *temp = malloc(sizeof(No));
        temp->valor = n->valor;
        temp->prox = nova;
        nova = temp;
        n = n->prox;
    }

    // Push em A
    while (nova != NULL) {
        comandoPush(a, nova->valor);
        No *del = nova;
        nova = nova->prox;
        free(del);
    }

    removerPilha(b);
}

// Comando SPLIT nome novoNome k
void comandoSplit(char *orig, char *novo, int k) {
    Pilha *p = encontrarPilha(orig);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", orig);
        exit(0);
    }

    Pilha *nova = malloc(sizeof(Pilha));
    strcpy(nova->nome, novo);
    nova->topo = NULL;
    nova->prox = lista;
    lista = nova;

    for (int i = 0; i < k; i++) {
        if (p->topo == NULL) break;
        No *top = p->topo;
        p->topo = top->prox;

        top->prox = nova->topo;
        nova->topo = top;
    }

    if (p->topo == NULL)
        removerPilha(orig);
}

// Função principal
int main() {
    int N;
    scanf("%d\n", &N);
    char linha[100];

    for (int i = 0; i < N; i++) {
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = 0; // tira o \n

        if (strstr(linha, ":INIT")) {
            char nome[51];
            sscanf(linha, "%[^:]:INIT", nome);
            comandoInit(nome);
        } else if (strstr(linha, ":PUSH")) {
            char nome[51];
            int x;
            sscanf(linha, "%[^:]:PUSH %d", nome, &x);
            comandoPush(nome, x);
        } else if (strstr(linha, ":POP")) {
            char nome[51];
            sscanf(linha, "%[^:]:POP", nome);
            comandoPop(nome);
        } else if (strstr(linha, ":TOP")) {
            char nome[51];
            sscanf(linha, "%[^:]:TOP", nome);
            comandoTop(nome);
        } else if (strstr(linha, ":PRINT")) {
            char nome[51];
            sscanf(linha, "%[^:]:PRINT", nome);
            comandoPrint(nome);
        } else if (strncmp(linha, "MERGE", 5) == 0) {
            char a[51], b[51];
            sscanf(linha, "MERGE %s %s", a, b);
            comandoMerge(a, b);
        } else if (strncmp(linha, "SPLIT", 5) == 0) {
            char orig[51], novo[51];
            int k;
            sscanf(linha, "SPLIT %s %s %d", orig, novo, &k);
            comandoSplit(orig, novo, k);
        } else if (strcmp(linha, "SHOW") == 0) {
            comandoShow();
        }
    }

    // Libera memória no final
    while (lista != NULL) {
        removerPilha(lista->nome);
    }

    return 0;
}
