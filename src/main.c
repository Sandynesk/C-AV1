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

int main(int argc, char *argv[])
{

    // 1. Inicializa a lista de contatos
    Contact *list = NULL;
    size_t count = 0;

    const char *DB_FILE = "data/contacts.bin";

    // 2. Tenta carregar os contatos do arquivo
    if (load_contacts(DB_FILE, &list, &count) != 0)
    {
        fprintf(stderr, "Falha grave ao carregar contatos.\n");
        return 1; // Termina o programa se não conseguir carregar
    }
    printf("Carregados %lu contatos.\n", (unsigned long)count);

    // 3. Analisa os argumentos da linha de comando [cite: 47]
    if (argc >= 2)
    {

        // Comando: ./simcon list [cite: 53]
        if (strcmp(argv[1], "list") == 0)
        {

            int (*cmp)(const void *, const void *) = cmp_by_name;
            qsort(list, count, sizeof(Contact), cmp);
            // ------------------------------------

            printf("--- Lista de Contatos ---\n");
            list_contacts(list, count); // [cite: 58]

            // Comando: ./simcon add [cite: 48]
        }
        else if (strcmp(argv[1], "add") == 0)
        {

            if (argc < 5)
            {
                fprintf(stderr, "Uso incorreto. Necessita: ./simcon add <nome> <email> <idade>\n");
            }
            else
            {
                Contact c = {0};

                const char *input_name = argv[2];
                const char *input_email = argv[3];
                int input_age = atoi(argv[4]);

                if (input_age <= 0 || input_age > 255)
                {
                    fprintf(stderr, "Erro: Idade inválida ou muito grande.\n");
                    return 0;
                }
                c.id = count + 1;
                strncpy(c.name, input_name, NAME_MAX - 1);
                strncpy(c.email, input_email, EMAIL_MAX - 1);
                c.age = (uint8_t)input_age;

                if (add_contact(&list, &count, &c) == 0)
                {
                    printf("Novo contato %s adicionado. Salvando...\n", c.name);
                    if (save_contacts(DB_FILE, list, count) != 0)
                    {
                        fprintf(stderr, "Erro ao salvar contato no arquivo.\n");
                    }
                }
            }
        }
        else if (strcmp(argv[1], "find") == 0)
        {
            if (argc < 3)
            {
                fprintf(stderr, "Uso: ./simcon find <termo_de_busca>\n");
            }
            else
            {
                const char *search_term = argv[2];
                printf("--- Buscando por \"%s\" ---\n", search_term);
                find_contacts(list, count, search_term);
            }
        }
        else
        {

            printf("Bem-vindo ao SIMCON.\n");
            printf("Uso: ./simcon <comando> [opcoes]\n");
            printf("Comandos: add, list, find, remove, export\n");
        }

        free(list);
        return 0;
        }
        else
        {
            printf("Bem-vindo ao SIMCON.\n");
            printf("Uso: ./simcon <comando> [opcoes]\n");
            printf("Comandos: add, list, find, remove, export\n");
        }

        free(list);

        return 0;
    }