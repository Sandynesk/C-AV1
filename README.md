# SIMCON

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
