 
#include "contact.h"
#include <stdio.h>
#include <stdlib.h> // Para realloc
#include <string.h> // Para strcmp e memcpy

/**
 * @brief Implementação de list_contacts
 */
void list_contacts(Contact *list, size_t count) {
    if (count == 0 || list == NULL) {
        printf("Nenhum contato na lista.\n");
        return;
    }
    
    printf("Exibindo %lu contato(s):\n", (unsigned long)count);
    for (size_t i = 0; i < count; i++) {
        // Imprime os dados de cada contato
        printf("  ID: %u\n", list[i].id);
        printf("  Nome: %s\n", list[i].name);
        printf("  Email: %s\n", list[i].email);
        printf("  Idade: %u\n", list[i].age);
        printf("  --------------------\n");
    }
}

/**
 * @brief Implementação de add_contact (com realloc)
 */
int add_contact(Contact **list_ptr, size_t *count_ptr, Contact *new_contact) {
    
    // 1. Calcula o novo tamanho da lista
    size_t new_count = *count_ptr + 1;
    
    // 2. Tenta realocar a memória para o novo tamanho [cite: 9]
    // realloc lida com o caso de *list_ptr ser NULL (se for o 1º contato)
    Contact *new_list = (Contact *)realloc(*list_ptr, new_count * sizeof(Contact));

    // 3. Trata erro de alocação
    if (new_list == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para novo contato.\n");
        return -1; // Falha
    }

    // 4. Copia o novo contato para a última posição da lista
    // Usamos memcpy para copiar a struct inteira
    memcpy(&new_list[new_count - 1], new_contact, sizeof(Contact));

    // 5. Atualiza os ponteiros originais na 'main'
    *list_ptr = new_list;
    *count_ptr = new_count;
    
    return 0; // Sucesso
}

/**
 * @brief Implementação de cmp_by_name (para qsort)
 */
int cmp_by_name(const void *a, const void *b) {
    // Converte os ponteiros genéricos (void*) de volta para ponteiros de Contact
    Contact *contact_a = (Contact *)a;
    Contact *contact_b = (Contact *)b;
    
    // Usa strcmp (da string.h) para comparar os nomes
    return strcmp(contact_a->name, contact_b->name);
}