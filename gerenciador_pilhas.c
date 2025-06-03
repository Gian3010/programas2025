#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct No {
    int valor;
    struct No* prox;
} No;
 
typedef struct Pilha {
    char nome[21];
    No* topo;
    struct Pilha* prox;
} Pilha;
 
Pilha* lista = NULL;
 
Pilha* encontrarPilha(const char* nome) {
    Pilha* p = lista;
    while (p) {
        if (strcmp(p->nome, nome) == 0)
            return p;
        p = p->prox;
    }
    return NULL;
}
 
void removerPilha(const char* nome) {
    Pilha *atual = lista, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior) anterior->prox = atual->prox;
            else lista = atual->prox;
            No* n = atual->topo;
            while (n) {
                No* tmp = n;
                n = n->prox;
                free(tmp);
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}
 
void INIT(char* nome) {
    if (encontrarPilha(nome)) return; // não recria pilha se já existe
    Pilha* nova = (Pilha*)malloc(sizeof(Pilha));
    strcpy(nova->nome, nome);
    nova->topo = NULL;
    nova->prox = lista;
    lista = nova;
}
 
void PUSH(char* nome, int valor) {
    Pilha* p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    No* novo = (No*)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = p->topo;
    p->topo = novo;
}
 
void POP(char* nome) {
    Pilha* p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        exit(0);
    }
    No* tmp = p->topo;
    p->topo = tmp->prox;
    free(tmp);
    if (!p->topo) removerPilha(nome);
}
 
void TOP(char* nome) {
    Pilha* p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    if (!p->topo) {
        printf("Pilha %s vazia!\n", nome);
        exit(0);
    }
    printf("%d\n", p->topo->valor);
}
 
void PRINT(char* nome) {
    Pilha* p = encontrarPilha(nome);
    if (!p) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    printf("[");
    No* n = p->topo;
    while (n) {
        printf("%d", n->valor);
        if (n->prox) printf(", ");
        n = n->prox;
    }
    printf("]\n");
}
 
void SHOW() {
    Pilha* p = lista;
    while (p) {
        printf("%s: [", p->nome);
        No* n = p->topo;
        while (n) {
            printf("%d", n->valor);
            if (n->prox) printf(", ");
            n = n->prox;
        }
        printf("]\n");
        p = p->prox;
    }
}
 
void MERGE(char* nomeA, char* nomeB) {
    Pilha *a = encontrarPilha(nomeA), *b = encontrarPilha(nomeB);
    if (!a || !b) {
        printf("Erro: pilhas nao encontradas!\n");
        exit(0);
    }
    // Inverter a pilha B para manter a ordem correta na A
    No* rev = NULL;
    while (b->topo) {
        No* tmp = b->topo;
        b->topo = tmp->prox;
        tmp->prox = rev;
        rev = tmp;
    }
    while (rev) {
        No* tmp = rev;
        rev = rev->prox;
        tmp->prox = a->topo;
        a->topo = tmp;
    }
    removerPilha(nomeB); // mesmo se vazia
}
 
void SPLIT(char* nome, char* novoNome, int k) {
    Pilha* origem = encontrarPilha(nome);
    if (!origem) {
        printf("Pilha %s nao encontrada!\n", nome);
        exit(0);
    }
    INIT(novoNome);
    Pilha* nova = encontrarPilha(novoNome);
 
    for (int i = 0; i < k; i++) {
        if (!origem->topo) break;
        No* tmp = origem->topo;
        origem->topo = tmp->prox;
        tmp->prox = nova->topo;
        nova->topo = tmp;
    }
 
    if (!origem->topo) removerPilha(nome);
}
 
void liberarTudo() {
    while (lista) {
        Pilha* tmp = lista;
        lista = lista->prox;
        No* n = tmp->topo;
        while (n) {
            No* x = n;
            n = n->prox;
            free(x);
        }
        free(tmp);
    }
}
 
int main() {
    int N;
    scanf("%d\n", &N);
    char linha[100];
    for (int i = 0; i < N; i++) {
        fgets(linha, sizeof(linha), stdin);
        linha[strcspn(linha, "\n")] = 0;
 
        if (strncmp(linha, "SHOW", 4) == 0) {
            SHOW();
            continue;
        }
        if (strncmp(linha, "MERGE", 5) == 0) {
            char a[21], b[21];
            sscanf(linha, "MERGE %20s %20s", a, b);
            MERGE(a, b);
            continue;
        }
        if (strncmp(linha, "SPLIT", 5) == 0) {
            char a[21], b[21];
            int k;
            sscanf(linha, "SPLIT %20s %20s %d", a, b, &k);
            SPLIT(a, b, k);
            continue;
        }
 
        char nome[21];
        sscanf(linha, "%20[^:]", nome);
 
        if (strstr(linha, ":INIT")) {
            INIT(nome);
        } else if (strstr(linha, ":PUSH")) {
            int x;
            sscanf(linha, "%*[^:]:PUSH %d", &x);
            PUSH(nome, x);
        } else if (strstr(linha, ":POP")) {
            POP(nome);
        } else if (strstr(linha, ":TOP")) {
            TOP(nome);
        } else if (strstr(linha, ":PRINT")) {
            PRINT(nome);
        }
    }
 
    liberarTudo();
    return 0;
}