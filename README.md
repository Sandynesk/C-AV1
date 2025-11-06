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
    char name[50];
    char phone[15];
    char email[50];
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



## Storage.c