//
// Created by Manara on 31/10/2024.
//

#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_USUARIOS 100
#define TAM_CPF 12  // 11 dígitos + 1 para '\0'
#define TAM_SENHA 9 // 8 dígitos + 1 para '\0'
#define MAX_PRODUTOS 100  // Define o número máximo de produtos no estoque
#define TAMANHO_NOME 50   // Define o tamanho máximo do nome do produto

// Estrutura para armazenar informações sobre o produto
typedef struct {
 int id;                  // ID do produto
 char nome[TAMANHO_NOME];  // Nome do produto
 float preco;              // Preço do produto
 int quantidade;           // Quantidade em estoque
} Produto;

// Estrutura para armazenar informações do usuário
typedef struct {
    char cpf[TAM_CPF];
    char senha[TAM_SENHA];
} Usuario;

/**
 * 
 * @param usuarios 
 * @param numUsuarios 
 */
void cadastrarUsuario(Usuario* usuarios, int* numUsuarios); // Funcao para cadastrar usuarios
/**
 * 
 * @param cpf 
 * @param senha 
 * @return 
 */
int validarDados(const char* cpf, const char* senha); // Função para validar CPF e senha
/**
 * 
 * @param usuarios 
 * @return 
 */
int carregarUsuarios(Usuario* usuarios); // Função para carregar usuários do arquivo
/**
 * 
 * @param usuarios 
 * @param numUsuarios 
 */
void salvarUsuarios(Usuario* usuarios, int numUsuarios); // Função para salvar usuários no arquivo
/**
 * 
 * @param usuarios 
 * @param numUsuarios 
 * @return 
 */
int login(Usuario* usuarios, int numUsuarios); // Função para realizar o login
int ler_inteiro();
float ler_float();
void adicionar_produto(Produto *produtos, int *total_produtos);
void listar_produtos(Produto *produtos, int total_produtos);
void editar_produto(Produto *produtos, int total_produtos);
void salvar_estoque(Produto *produtos, int total_produtos);
void carregar_estoque(Produto *produtos, int *total_produtos);

#endif //FUNCOES_H
