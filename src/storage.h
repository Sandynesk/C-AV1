#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>      
#include <stdlib.h>     
#include "contact.h"  

/**
 * Salva a lista de contatos em um arquivo binário.
 * * @param filename O nome do arquivo onde salvar (ex: "data/contacts.bin").
 * @param list O ponteiro para o início do vetor de contatos.
 * @param count O número de contatos no vetor.
 * @return 0 se sucesso, -1 se ocorrer algum erro.
 */
int save_contacts(const char *filename, const Contact *list, size_t count);

/**
 * Carrega contatos de um arquivo binário para a memória.
 * Aloca memória para a lista e atualiza o ponteiro 'list' e 'count'.
 *
 * @param filename O nome do arquivo de onde carregar.
 * @param list_ptr Um ponteiro para o ponteiro da lista (será modificado).
 * @param count_ptr Um ponteiro para a variável de contagem (será modificada).
 * @return 0 se sucesso, -1 se ocorrer algum erro (ex: arquivo não existe).
 */
int load_contacts(const char *filename, Contact **list_ptr, size_t *count_ptr);
int export_contacts(const char *filename, const Contact *list, size_t count);


#endif // STORAGE_H