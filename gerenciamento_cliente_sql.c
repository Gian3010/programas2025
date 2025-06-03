/*
 * Projeto: Sistema de Gerenciamento de Clientes em C com SQLite
 * Requisitos: libsqlite3-dev
 * Compilação: gcc main.c -lsqlite3 -o cliente_manager
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define DB_NAME "clientes.db"

void criar_tabela(sqlite3 *db) {
    const char *sql = "CREATE TABLE IF NOT EXISTS clientes ("
                     "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                     "nome TEXT NOT NULL,"
                     "email TEXT UNIQUE NOT NULL);");
    char *err_msg = 0;
    if (sqlite3_exec(db, sql, 0, 0, &err_msg) != SQLITE_OK) {
        fprintf(stderr, "Erro ao criar tabela: %s\n", err_msg);
        sqlite3_free(err_msg);
        exit(1);
    }
}

void adicionar_cliente(sqlite3 *db) {
    char nome[100], email[100];
    printf("Nome: "); fgets(nome, 100, stdin); strtok(nome, "\n");
    printf("Email: "); fgets(email, 100, stdin); strtok(email, "\n");

    const char *sql = "INSERT INTO clientes (nome, email) VALUES (?, ?);";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, nome, -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email, -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao inserir cliente.\n");
    } else {
        printf("Cliente adicionado com sucesso.\n");
    }
    sqlite3_finalize(stmt);
}

void listar_clientes(sqlite3 *db) {
    const char *sql = "SELECT id, nome, email FROM clientes;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);

    printf("\n-- Lista de Clientes --\n");
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char *nome = (const char *)sqlite3_column_text(stmt, 1);
        const char *email = (const char *)sqlite3_column_text(stmt, 2);
        printf("ID: %d | Nome: %s | Email: %s\n", id, nome, email);
    }
    sqlite3_finalize(stmt);
}

void deletar_cliente(sqlite3 *db) {
    int id;
    printf("ID do cliente a deletar: ");
    scanf("%d", &id); getchar();

    const char *sql = "DELETE FROM clientes WHERE id = ?;";
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, id);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        printf("Erro ao deletar cliente.\n");
    } else {
        printf("Cliente removido.\n");
    }
    sqlite3_finalize(stmt);
}

int main() {
    sqlite3 *db;
    if (sqlite3_open(DB_NAME, &db)) {
        fprintf(stderr, "Erro ao abrir banco de dados: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    criar_tabela(db);

    int opcao;
    do {
        printf("\n1. Adicionar Cliente\n2. Listar Clientes\n3. Remover Cliente\n0. Sair\nEscolha: ");
        scanf("%d", &opcao); getchar();

        switch (opcao) {
            case 1: adicionar_cliente(db); break;
            case 2: listar_clientes(db); break;
            case 3: deletar_cliente(db); break;
            case 0: break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    sqlite3_close(db);
    return 0;
}
