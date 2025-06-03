#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
struct Node {
    int id;
    char message[51];
    struct Node *next;
};
 
struct Node *front = NULL;
struct Node *rear = NULL;
 
void enqueue(int id, const char *message) {
    struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->id = id;
    strncpy(newNode->message, message, 50);
    newNode->message[50] = '\0';
    newNode->next = NULL;
 
    if (rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}
 
void dequeue() {
    if (front == NULL) {
        printf("Fila vazia!\n");
        return;
    }
    struct Node *temp = front;
    front = front->next;
    if (front == NULL) {
        rear = NULL;
    }
    free(temp);
}
 
void print_queue() {
    if (front == NULL) {
        printf("\n");
        return;
    }
    struct Node *current = front;
    while (current != NULL) {
        printf("ID: %d - %s\n", current->id, current->message);
        current = current->next;
    }
}
 
void clear_queue() {
    while (front != NULL) {
        struct Node *temp = front;
        front = front->next;
        free(temp);
    }
    rear = NULL;
}
 
int main() {
    int N;
    scanf("%d", &N);
    while (getchar() != '\n');
 
    for (int i = 0; i < N; i++) {
        char buffer[1000];
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            break;
        }
 
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
 
        char *cmd_end = strchr(buffer, ' ');
        if (cmd_end != NULL) {
            *cmd_end = '\0';
            char *cmd = buffer;
            char *rest = cmd_end + 1;
 
            if (strcmp(cmd, "ENQUEUE") == 0) {
                char *id_end = strchr(rest, ' ');
                if (id_end != NULL) {
                    *id_end = '\0';
                    int id = atoi(rest);
                    char *message = id_end + 1;
                    enqueue(id, message);
                }
            }
        } else {
            char *cmd = buffer;
            if (strcmp(cmd, "DEQUEUE") == 0) {
                dequeue();
            } else if (strcmp(cmd, "PRINT") == 0) {
                print_queue();
            } else if (strcmp(cmd, "CLEAR") == 0) {
                clear_queue();
            }
        }
    }
 
    return 0;
}