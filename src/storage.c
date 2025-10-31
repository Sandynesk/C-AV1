#include "storage.h"  
#include <stdio.h>      // Para fopen, fwrite, fclose, perror
#include <stdlib.h>     // Para malloc, free, NULL

int save_contacts(const char *filename, const Contact *list, size_t count) {
    
    // 1. Abrir o arquivo no modo "write binary" (escrita binária)
    // "wb" cria um arquivo novo ou apaga o conteúdo de um existente.
    // Use fopen com modos binários ( "rb" , "wb" , "ab" ) em plataformas portáveis.
    FILE *file = fopen(filename, "wb"); 
    
    // 2. Tratar erro de abertura (ex: permissão negada)
    if (file == NULL) {
        perror("Erro ao abrir arquivo para escrita");
        return -1; // Retorna código de erro
    }

    // 3. Escrever o vetor inteiro de uma só vez
    // 
    // A mágica acontece aqui:
    // list = ponteiro para o primeiro item
    // sizeof(Contact) = tamanho de CADA item
    // count = NÚMERO de itens
    // file = onde escrever
    // size_t é o tipo de dado padrão em C para qualquer coisa que
    // represente um tamanho, uma contagem ou um índice de vetor.
    size_t items_written = fwrite(list, sizeof(Contact), count, file);

    // 4. Fechar o arquivo (muito importante!)
    fclose(file);

    // 5. Verificar se tudo foi escrito corretamente
    if (items_written != count) {
        fprintf(stderr, "Erro: nem todos os contatos foram salvos.\n");
        return -1;
    }

    return 0; // Sucesso!
}



int load_contacts(const char *filename, Contact **list_ptr, size_t *count_ptr) {
    
    // 1. Abrir o arquivo em modo "read binary" (leitura binária)
    FILE *file = fopen(filename, "rb");

    // 2. Tratar erro (ex: arquivo não existe na primeira execução)
    if (file == NULL) {
        // Isso não é um erro fatal, pode ser a primeira vez rodando.
        // Apenas informamos que nada foi carregado.
        *list_ptr = NULL;
        *count_ptr = 0;
        return 0; // Retorna sucesso, mas com 0 contatos.
    }

    // 3. Descobrir o tamanho do arquivo 
    fseek(file, 0, SEEK_END);    // Vai para o final do arquivo
    long file_size = ftell(file); // Pega a posição atual (tamanho em bytes)
    rewind(file);                // Volta para o início do arquivo

    // 4. Calcular o número de contatos 
    if (file_size == 0) {
        // Arquivo existe, mas está vazio
        *list_ptr = NULL;
        *count_ptr = 0;
        fclose(file);
        return 0;
    }
    
    // Validação opcional: verifica se o tamanho é múltiplo da struct
    if (file_size % sizeof(Contact) != 0) {
        fprintf(stderr, "Erro: Arquivo de dados corrompido.\n");
        fclose(file);
        return -1;
    }

    size_t num_contacts = file_size / sizeof(Contact);

    // 5. Alocar memória para todos os contatos 
    // Usamos malloc pois o documento sugere
    Contact *temp_list = (Contact *)malloc(file_size);

    // 6. Tratar falha na alocação de memória [cite: 69]
    if (temp_list == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para carregar contatos.\n");
        fclose(file);
        return -1;
    }

    // 7. Ler todos os contatos do arquivo para a memória [cite: 8]
    size_t items_read = fread(temp_list, sizeof(Contact), num_contacts, file);

    // 8. Tratar erro de leitura [cite: 69]
    if (items_read != num_contacts) {
        fprintf(stderr, "Erro: Falha ao ler dados do arquivo.\n");
        fclose(file);
        free(temp_list); // Libera memória alocada antes de sair
        return -1;
    }

    // 9. Fechar o arquivo
    fclose(file);

    // 10. Atualizar os ponteiros originais na 'main'
    *list_ptr = temp_list;
    *count_ptr = num_contacts;

    return 0; // Sucesso!
}