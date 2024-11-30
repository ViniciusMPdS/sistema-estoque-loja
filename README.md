# Sistema de Gerenciamento de Estoque

Este projeto implementa um sistema simples de gerenciamento de estoque para uma loja. O sistema permite o cadastro e login de usuários, além de possibilitar a manipulação de produtos no estoque (adicionar, editar e listar). Ele é desenvolvido em C e utiliza arquivos de texto para persistir dados de usuários e produtos.

## Funcionalidades

O sistema oferece as seguintes funcionalidades:

- **Cadastro de Usuários**: Permite cadastrar usuários fornecendo CPF e senha.
- **Login de Usuários**: O usuário pode fazer login com CPF e senha previamente cadastrados.
- **Gestão de Estoque**: Permite adicionar novos produtos ao estoque, listar os produtos existentes e editar os produtos já cadastrados.
- **Persistência de Dados**: O sistema salva os dados dos usuários e do estoque em arquivos de texto para garantir a persistência entre execuções do programa.

## Tecnologias Utilizadas

- **Linguagem de Programação**: C
- **IDE**: Clion
- **Arquivos de Texto**: Utilizados para armazenar os dados dos usuários e do estoque.

## Estrutura do Projeto

O código está organizado da seguinte forma:

- **`funcoes.c`**: Contém as definições das funções utilizadas no programa, como cadastro, login e manipulação de estoque.
- **`main.c`**: Implementação da lógica principal do sistema, que interage com o usuário e realiza as operações no sistema.
- **`usuarios.txt`**: Arquivo que armazena os dados de usuários cadastrados (CPF e senha).
- **`estoque.txt`**: Arquivo que armazena os produtos no estoque (ID, nome, preço e quantidade).

## Dependências

- **Compilador C**: Computador com ambiente configurado para compilar e executar programas em C.

## Como Compilar e Rodar

### 1. Clonar o Repositório

Clone o repositório em sua máquina local:

```bash
git clone https://github.com/ViniciusMPdS/sistema-estoque-loja
cd sistema-estoque-loja/finalProject04
```
Antes de iniciar a compilação, mude o local de armazenamento das listas usuarios.txt e estoqeu.txt dentro das funções 'carregarUsuarios', 'salvarUsuarios', 'salvar_estoque' e 'carregar_estoque', para um local de armazenamento dentro de sua máquina.

Para compilar o código, execute o seguinte comando:
```bash
gcc main.c funcoes.c -o sistema
```

Após compilar o código, execute o programa com o seguinte comando:
```bash
./sistema

