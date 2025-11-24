# SIMCON
## Compilação e Execução
Para compilar o projeto, utilize o seguinte comando no terminal:
```bash
.\simcon.exe  
```
Ou em sistemas Unix/Linux:
```bash
gcc -o simcon main.c contacts.c storage.c utils.c
```
Para executar o programa, utilize o comando:
```bash
./simcon
```
## Dependências
O projeto não possui dependências externas e utiliza apenas a biblioteca padrão do C.

## Estrutura do projeto
### Main
O arquivo `main` contém o código-fonte principal do projeto SIMCON. Ele é organizado da seguinte forma:
- Incialmente ela chama as funções iniciais para a interação do usuário, funcionando como um cerebro do sistema.
- Storage.c para carregar os dadios com a função load_contacts.
- Lê os comandos do usuário e chama as funções apropriadas para cada comando(add, list, find, remove, export).
### Contacts
O arquivo `contacts.c` contém as funções relacionadas à manipulação dos contatos, como adicionar, listar, encontrar, remover e exportar contatos.
- Define a struct Contact, que representa um contato com campos como nome, telefone e email.
- Implementa as funções para adicionar, listar, encontrar, remover e exportar contatos.
- Apenas manipula os dados que estão dentro da memória ram.
### Storage
O arquivo `storage.c` é responsável pelo armazenamento persistente dos contatos em um arquivo no disco rigido.
- Recebe a lista de contatos da memoria(save_contacts), utiliza fopen("wb") e fwrite para salvar os contatos em um arquivo binário(contacts.bin).
- Utiliza fopen("rb") e fread para carregar os contatos do arquivo binário para a memória(load_contacts).
### Utils
O arquivo `utils.c` contém funções utilitárias que são usadas em todo o projeto.
- Funções para manipulação de strings, validação de dados e outras operações auxiliares.

## Conctact.c
### Estrutura Contact
A struct Contact é definida da seguinte forma:
```c
typedef struct {
    uint32_t id;      
    char name[NAME_MAX];    
    char email[EMAIL_MAX];  
    uint8_t age;      
} Contact;
```
### Funções Principais
- `void add_contact(Contact *contacts, int *count, Contact new_contact);`
    - Adiciona um novo contato à lista de contatos, realocando memória conforme necessário.
    - Calcula o novo tamanho da lista e atualiza o contador de contatos utilizando o realloc.
    - Trata erros de alocação de memória.
    - Copia o novo contato para a ultima posição da lista, utilizando memcpy para copiar a struct Contact.
    - Atualiza os ponteiros originais no arquivo main.c.
        ```c       
        Contact *new_list = realloc(*list_ptr, new_count * sizeof(Contact));
        if (new_list == NULL) {
            printf("Erro ao alocar memória para novo contato.\n");
            return;
        }

        memcpy(&new_list[new_count - 1], new_contact, sizeof(Contact));
        *list_ptr = new_list;
        *list_ptr = new_list;
        *count_ptr = new_count;
        ```

    


- `void list_contacts(Contact *contacts, int count);`
    - Lista todos os contatos na lista de contatos.
    - Trata o caso em que a lista está vazia.
    - itera sobre a lista de contatos e imprime os detalhes de cada contato.
        
    ```c
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
    ```

- `cmp_by_name(const void *a, const void *b);`
    - Converte os ponteiros genéricos (void*) de volta para ponteiros de Contact
    - Usa strcmp (da string.h) para comparar os nomes
    - Retorna o resultado da comparação
    ```c
    int cmp_by_name(const void *a, const void *b) {
        const Contact *contact_a = (const Contact *)a;
        const Contact *contact_b = (const Contact *)b;

        return strcmp(contact_a->name, contact_b->name);
    }
    ```

- `void find_contacts(const Contact *list, size_t count, const char *term);`
    - Busca contatos na lista cujos nomes contenham o termo de busca fornecido.
    - Itera sobre a lista de contatos e utiliza strstr (da string.h) para encontrar correspondências dentro do campo name.  
    - Imprime os detalhes dos contatos encontrados ou uma mensagem se nenhum for localizado.
    ```c
    void find_contacts(const Contact *list, size_t count, const char *term)
    {
        int found = 0;
        for (size_t i = 0; i < count; i++)
        {
            if (strstr(list[i].name, term) != NULL)
            {
                printf("  ID: %u\n", list[i].id);
                printf("  Nome: %s\n", list[i].name);
                printf("  Email: %s\n", list[i].email);
                printf("  Idade: %u\n", list[i].age);
                printf("  --------------------\n");
                found = 1;
            }
        }

        if (found == 0)
        {
            printf("Nenhum contato encontrado.\n");
        }
    }
    ```
-   `int remover_contato(Contact **list_ptr, size_t *count_ptr, uint32_t id_to_remove);`
    - Remove um contato da lista com base no seu id.
    - Após encontrar o ID, utiliza memmove para deslocar os elementos subsequentes, preenchendo o espaço do contato removido.
    - Decrementa a contagem de contatos e usa realloc para diminuir o bloco de memória alocado. 
    - Retorna 0 em caso de sucesso e -1 se o ID não for encontrado ou se houver falha na realocação de memória.
     ```c
        int remover_contato(Contact **list_ptr, size_t *count_ptr, uint32_t id_to_remove)
        {
            Contact *list = *list_ptr;
            
            for (size_t i = 0; i < *count_ptr; i++)
            {
                if ((*list_ptr)[i].id == id_to_remove )
                {
                    size_t elementos_mover = (*count_ptr - 1) - i;
                    size_t bytes_mover = elementos_mover * sizeof(Contact);
                    memmove(&(*list_ptr)[i], &(*list_ptr)[i + 1], bytes_mover);

                    *count_ptr -= 1;
                    Contact *new_list = (Contact *)realloc(*list_ptr, (*count_ptr) * sizeof(Contact));

                    if (new_list == NULL)
                    {
                        fprintf(stderr, "Erro: Falha ao reduzir memória.\n");
                        return -1; 
                    }
                    *list_ptr = new_list;
                    return 0;
                }
            }
            printf("Erro: ID não encontrado.");
            return -1;
        }
     ```
## Storage.c
### Funções Principais
- `int save_contacts(const char *filename, Contact *contacts, int count);`
    - Salva a lista de contatos em um arquivo binário.
    - Abre o arquivo em modo de escrita binária ("wb").
    - Escreve o número de contatos seguido pelos dados dos contatos no arquivo.
    - Fecha o arquivo e retorna 0 em caso de sucesso ou -1 em caso de erro.
    ```c
    int save_contacts(const char *filename, const Contact *list, size_t count) {
        FILE *file = fopen(filename, "wb"); 
        if (file == NULL) {
            perror("Erro ao abrir arquivo para escrita");
            return -1; 
        }

        size_t items_written = fwrite(list, sizeof(Contact), count, file);
        fclose(file);

        if (items_written != count) {
            fprintf(stderr, "Erro: nem todos os contatos foram salvos.\n");
            return -1;
        }

        return 0; 
    }
    ```
- `int load_contacts(const char *filename, Contact **contacts, int *count);`
    - Carrega a lista de contatos de um arquivo binário.
    - Trata o caso em que o arquivo não existe, retornando uma lista vazia.
    - Abre o arquivo em modo de leitura binária ("rb").
    - Lê o número de contatos e aloca memória para armazená-los.
    - Trata erros de leitura do arquivo.
    - Verifica se o arquivo está corrompido.
    - Aloca memoria utilizando malloc.
    - Trata erros de alocação de memória.
    - Atualiza os ponteiros originais da main.c.
    ```c
    int load_contacts(const char *filename, Contact **list_ptr, size_t *count_ptr) {
        FILE *file = fopen(filename, "rb");

        if (file == NULL) {
            *list_ptr = NULL;
            *count_ptr = 0;
            return 0;
        }

        fseek(file, 0, SEEK_END);
        long file_size = ftell(file);
        rewind(file);

        if (file_size == 0) {
            *list_ptr = NULL;
            *count_ptr = 0;
            fclose(file);
            return 0;
        }
        
        if (file_size % sizeof(Contact) != 0) {
            fprintf(stderr, "Erro: Arquivo de dados corrompido.\n");
            fclose(file);
            return -1;
        }

        size_t num_contacts = file_size / sizeof(Contact);

        Contact *temp_list = (Contact *)malloc(file_size);

        if (temp_list == NULL) {
            fprintf(stderr, "Erro: Falha ao alocar memória para carregar contatos.\n");
            fclose(file);
            return -1;
        }

        size_t items_read = fread(temp_list, sizeof(Contact), num_contacts, file);

        if (items_read != num_contacts) {
            fprintf(stderr, "Erro: Falha ao ler dados do arquivo.\n");
            fclose(file);
            free(temp_list);
            return -1;
        }

        fclose(file);

        *list_ptr = temp_list;
        *count_ptr = num_contacts;

        return 0;
    }
    ```
-    `int export_contacts(const char *filename, const Contact *list, size_t count);`
    - Exporta a lista de contatos para um arquivo de texto no formato CSV.
    - Abre o arquivo no modo de escrita de texto ("w").
    - Escreve um cabeçalho CSV (ID,Nome,Email,Idade).
    - Itera sobre a lista e usa fprintf para escrever os dados de cada contato no formato separado por vírgula.
    - Retorna 0 em caso de sucesso ou -1 em caso de erro ao abrir o arquivo.
     ```c
        int export_contacts(const char *filename, const Contact *list, size_t count) 
        {
            // 1. Abrir o arquivo no modo "w" (escrita de texto)
            FILE *file = fopen(filename, "w"); 
            
            if (file == NULL) {
                perror("Erro ao abrir arquivo para exportação");
                return -1;
            }

            // 2. Escrever o cabeçalho CSV (opcional, mas recomendado)
            fprintf(file, "ID,Nome,Email,Idade\n");

            // 3. Iterar sobre todos os contatos
            for (size_t i = 0; i < count; i++) {
                // 4. Escrever cada contato no formato CSV
                // Os dados são separados por vírgulas
                fprintf(
                    file, 
                    "%u,%s,%s,%u\n", 
                    list[i].id, 
                    list[i].name, 
                    list[i].email, 
                    list[i].age
                );
            }

            // 5. Fechar o arquivo
            fclose(file); 

            return 0;
        }
     ```

## Utils.c
### Funções Principais
- `int validate_email(const char *email);`
    - Utiliza fgets para ler a entrada do usuário, limitando o número de caracteres lidos para evitar estouro de buffer.
    ```c
    int read_safe_string(char *buffer, int size) {
    
        if (fgets(buffer, size, stdin) != NULL) {
            // Remove o '\n' (quebra de linha) do final, se fgets o capturou
            buffer[strcspn(buffer, "\n")] = '\0';
            return 0; // Sucesso
        }
        return -1; // Erro ou EOF
    }
    ```

# Bibliotecas utilizadas:
- `stdio.h`: Para operações de entrada e saída, como printf, scanf, fopen, fread, fwrite, fclose.
- `stdint.h`: Para tipos de dados inteiros com tamanhos específicos, como uint8_t.
- `string.h`: Para manipulação de strings, como strcmp, strcpy, strlen, strcspn.
- `stdlib.h`: Para funções de alocação de memória dinâmica, como malloc, realloc

### Libs locais
- `contacts.h`: Declarações das funções e estruturas relacionadas aos contatos.
- `storage.h`: Declarações das funções relacionadas ao armazenamento de contatos.
- `utils.h`: Declarações das funções utilitárias usadas em todo o projeto.

## Autor
- Emanuel Sales
- Ryan França
- Gabriel Victor

