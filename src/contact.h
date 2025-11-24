#ifndef CONTACT_H
#define CONTACT_H

#include <stdint.h> 
#include <stdlib.h> // Para size_t

#define NAME_MAX 64   
#define EMAIL_MAX 64  

typedef struct {
    uint32_t id;      
    char name[NAME_MAX];    
    char email[EMAIL_MAX];  
    uint8_t age;      
} Contact;

/* --- NOVOS PROTÓTIPOS --- */

/**
 * @brief Lista todos os contatos no console.
 */
void list_contacts(Contact *list, size_t count);

/**
 * @brief Adiciona um novo contato à lista, realocando memória.
 * Cumpre o requisito de alocação dinâmica[cite: 9].
 * @return 0 em sucesso, -1 em falha de alocação.
 */
int add_contact(Contact **list_ptr, size_t *count_ptr, Contact *new_contact);

/**
 * @brief Função de comparação para qsort, ordena por nome.
 * Cumpre o requisito de ponteiro para função[cite: 12].
 */
int cmp_by_name(const void *a, const void *b);

void find_contacts(const Contact *list, size_t count, const char *term);


#endif // CONTACT_H