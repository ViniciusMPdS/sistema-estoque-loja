#include <stdio.h>
#include "funcoes.h"
#include <string.h>

void cadastrarUsuario(Usuario* usuarios, int* numUsuarios); // Funcao para cadastrar usuarios
int validarDados(const char* cpf, const char* senha); // Função para validar CPF e senha
int carregarUsuarios(Usuario* usuarios); // Função para carregar usuários do arquivo
void salvarUsuarios(Usuario* usuarios, int numUsuarios); // Função para salvar usuários no arquivo
int login(Usuario* usuarios, int numUsuarios); // Função para realizar o login
int ler_inteiro();
float ler_float();
void adicionar_produto(Produto *produtos, int *total_produtos);
void listar_produtos(Produto *produtos, int total_produtos);
void editar_produto(Produto *produtos, int total_produtos);
void salvar_estoque(Produto *produtos, int total_produtos);
void carregar_estoque(Produto *produtos, int *total_produtos);
void copy_init(char *str1, char *str2);
int primDigito(char *str);
int segDigito(char *str);
int controleProduto();
int telaLogin();

// Função principal
int main() {
    if (telaLogin()) {
        printf("\n");
        controleProduto();  // Inicia o controle de produtos
    } else {
        printf("Encerrando o programa.\n");
    }
    return 0;
}




