#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Inclui nossos próprios módulos
#include "contact.h"
#include "storage.h"
// #include "utils.h" // (Vamos precisar quando tiver o read_contact_interactive)

// --- Funções de contact.c (que ainda vamos criar) ---
// Precisamos declarar "stubs" ou protótipos aqui por enquanto
// para o main.c saber que elas existem.
void list_contacts(Contact *list, size_t count);
int add_contact(Contact **list_ptr, size_t *count_ptr, Contact *new_contact);
int cmp_by_name(const void *a, const void *b);
// ---------------------------------------------------

int main(int argc, char *argv[]) {
    
    // 1. Inicializa a lista de contatos
    Contact *list = NULL;
    size_t count = 0;

    const char* DB_FILE = "data/contacts.bin";

    // 2. Tenta carregar os contatos do arquivo 
    if (load_contacts(DB_FILE, &list, &count) != 0) {
        fprintf(stderr, "Falha grave ao carregar contatos.\n");
        return 1; // Termina o programa se não conseguir carregar
    }
    printf("Carregados %lu contatos.\n", (unsigned long)count);


    // 3. Analisa os argumentos da linha de comando [cite: 47]
    if (argc >= 2) {
        
        // Comando: ./simcon list [cite: 53]
        if (strcmp(argv[1], "list") == 0) {
            
            // --- Lógica de Ordenação (exemplo) --- [cite: 54-57]
            // (Vamos implementar a opção --sort depois)
            int (*cmp)(const void*, const void*) = cmp_by_name;
            qsort(list, count, sizeof(Contact), cmp);
            // ------------------------------------

            printf("--- Lista de Contatos ---\n");
            list_contacts(list, count); // [cite: 58]

        // Comando: ./simcon add [cite: 48]
        } else if (strcmp(argv[1], "add") == 0) {
            
            printf("--- Adicionar Novo Contato ---\n");
            // (Aqui virá a lógica do read_contact_interactive)
            
            // Exemplo simples de como adicionar um contato "fake"
            Contact c = {0}; // Zera a struct
            c.id = count + 1; // (Isso é um ID simples, pode ser melhorado)
            strncpy(c.name, "Usuario Teste", NAME_MAX);
            strncpy(c.email, "teste@email.com", EMAIL_MAX);
            c.age = 30;

            if (add_contact(&list, &count, &c) == 0) {
                printf("Novo contato adicionado. Salvando...\n");
                // Salva imediatamente no arquivo [cite: 52]
                if (save_contacts(DB_FILE, list, count) != 0) {
                    fprintf(stderr, "Erro ao salvar contato no arquivo.\n");
                }
            }
            
        // (Outros comandos virão aqui: find, remove, export)
        } else {
            fprintf(stderr, "Comando desconhecido: %s\n", argv[1]);
        }

    } else {
        // Sem argumentos, podemos mostrar uma ajuda
        printf("Bem-vindo ao SIMCON.\n");
        printf("Uso: ./simcon <comando> [opcoes]\n");
        printf("Comandos: add, list, find, remove, export\n");
    }


    // 4. Libera a memória alocada por load_contacts (ou add_contact)
    free(list); // 
    
    return 0; // [cite: 65]
}