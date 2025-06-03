#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct Node {
    int val;
    struct Node* next;
} Node;
 
typedef struct {
    Node* top;
} Stack;
 
void push(Stack* stack, int val) {
    Node* newNode = malloc(sizeof(Node));
    newNode->val = val;
    newNode->next = stack->top;
    stack->top = newNode;
}
 
int pop(Stack* stack, int* out) {
    if (!stack->top) return 0;
    Node* temp = stack->top;
    *out = temp->val;
    stack->top = temp->next;
    free(temp);
    return 1;
}
 
int peek(Stack* stack, int* out) {
    if (!stack->top) return 0;
    *out = stack->top->val;
    return 1;
}
 
int size(Stack* stack) {
    int count = 0;
    Node* curr = stack->top;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}
 
void clear(Stack* stack) {
    int x;
    while (pop(stack, &x));
}
 
void print(Stack* stack) {
    int n = size(stack);
    int* temp = malloc(n * sizeof(int));
    Node* curr = stack->top;
    for (int i = 0; i < n; i++) {
        temp[i] = curr->val;
        curr = curr->next;
    }
    for (int i = 0; i < n; i++) {
        printf("%d", temp[i]);
        if (i < n - 1) printf(" ");
    }
    printf("\n");
    free(temp);
}
 
void error_and_exit(const char* msg) {
    printf("%s\n", msg);
    exit(0);
}
 
void roll(Stack* stack, int n) {
    int sz = size(stack);
    if (n < 1 || n > sz) {
        error_and_exit("Erro: Posicao invalida!");
    }
 
    int* temp = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        if (!pop(stack, &temp[i])) {
            free(temp);
            error_and_exit("Erro: Posicao invalida!");
        }
    }
 
    int target = temp[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        push(stack, temp[i]);
    }
    push(stack, target);
 
    free(temp);
}
 
int main() {
    int N;
    scanf("%d\n", &N);
    Stack stack = {NULL};
    int printed = 0;
 
    for (int i = 0; i < N; i++) {
        char line[100], cmd[10];
        int arg;
        fgets(line, sizeof(line), stdin);
        line[strcspn(line, "\n")] = 0;
 
        if (sscanf(line, "%s %d", cmd, &arg) == 2) {
            if (strcmp(cmd, "PUSH") == 0) {
                push(&stack, arg);
            } else if (strcmp(cmd, "ROLL") == 0) {
                roll(&stack, arg);
            }
        } else {
            if (strcmp(line, "POP") == 0) {
                int x;
                if (!pop(&stack, &x)) {
                    error_and_exit("Erro: Pilha vazia!");
                }
            } else if (strcmp(line, "ADD") == 0) {
                int a, b;
                if (!pop(&stack, &a) || !pop(&stack, &b)) {
                    error_and_exit("Erro: Elementos insuficiente para operacao!");
                }
                push(&stack, b + a);
            } else if (strcmp(line, "SUB") == 0) {
                int a, b;
                if (!pop(&stack, &a) || !pop(&stack, &b)) {
                    error_and_exit("Erro: Elementos insuficiente para operacao!");
                }
                push(&stack, b - a);
            } else if (strcmp(line, "MUL") == 0) {
                int a, b;
                if (!pop(&stack, &a) || !pop(&stack, &b)) {
                    error_and_exit("Erro: Elementos insuficiente para operacao!");
                }
                push(&stack, b * a);
            } else if (strcmp(line, "DIV") == 0) {
                int a, b;
                if (!pop(&stack, &a) || !pop(&stack, &b)) {
                    error_and_exit("Erro: Elementos insuficiente para operacao!");
                }
                if (a == 0) {
                    error_and_exit("Erro: Divisao por zero!");
                }
                push(&stack, b / a);
            } else if (strcmp(line, "DUP") == 0) {
                int top;
                if (!peek(&stack, &top)) {
                    error_and_exit("Erro: Pilha vazia para DUP!");
                }
                push(&stack, top);
            } else if (strcmp(line, "SWAP") == 0) {
                int a, b;
                if (!pop(&stack, &a) || !pop(&stack, &b)) {
                    error_and_exit("Erro: Pilha insuficiente para SWAP!");
                }
                push(&stack, a);
                push(&stack, b);
            } else if (strcmp(line, "CLEAR") == 0) {
                clear(&stack);
            } else if (strcmp(line, "PRINT") == 0) {
                print(&stack);
                printed = 1;
            }
        }
    }
 
    if (!printed) {
        print(&stack);
    }
 
    return 0;
}