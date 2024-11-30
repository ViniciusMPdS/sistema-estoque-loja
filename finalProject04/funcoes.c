    //
    // Created by Manara on 31/10/2024.
    //
    #include <stdio.h>
    #include <string.h>
    #include "funcoes.h"

    void copy_init(char *cpfint, char *cpfini) {
        char *p_i = cpfint;
        for(int i=0; i<9; i++) {
            cpfini[i] = cpfint[i];
        }
    }

    int primDigito(char *str) {
        int cont = 10;
        int soma = 0;
        for(int i=0; i<9; i++) {
            int digito = str[i] - '0';
            soma+=(digito * cont);
            cont--;
        }
        int dig = soma % 11;
        if(dig < 2) return 0;
        return 11 - dig;
    }
    int segDigito(char *str) {
        int cont = 11;
        int soma = 0;
        for(int i=0; i<10; i++) {
            int digito = str[i] - '0';
            soma+=(digito * cont);
            cont--;
        }
        int dig = soma % 11;
        if(dig < 2) return 0;
        return 11 - dig;
    }

    int ultimaValidacaoCPF(const char* cpf) {
        char ini_cpf[12] = {0};
        copy_init(cpf, ini_cpf);
        int dig1 = primDigito(ini_cpf);
        ini_cpf[9] = dig1 + '0';
        int dig2 = segDigito(ini_cpf);
        ini_cpf[10] = dig2 + '0';
        ini_cpf[11] = '\0';

        // Verifica se o CPF é válido comparando com o original
        if (strcmp(ini_cpf, cpf) == 0) {
            printf("CPF Validado\n");
            return 1;
        } else {
            printf("CPF Invalido\n");
            return 0;
        }
    }

    // Função para validar CPF e senha
    int validarDados(const char* cpf, const char* senha) {
        // Verificação de comprimento
        if (strlen(cpf) != 11 || strlen(senha) != 8) {
            printf("\nCPF deve ter 11 dígitos e senha 8 caracteres.\n");
            return 0;
        }
        // Chama a função para validar o CPF
        if (!ultimaValidacaoCPF(cpf)) {
            printf("CPF invalido\n");
            return 0;
        }
        return 1; // Dados válidos
    }

    // Função para carregar usuários do arquivo
    int carregarUsuarios(Usuario* usuarios) {
        FILE* file = fopen("H:\\ACADEMIC\\CODES\\C\\Gerenciamento_Estoque_C\\finalProject04\\usuarios.txt", "r");
        if (!file) {
            return 0; // Retorna 0 se o arquivo não existir
        }

        int count = 0;
        while (fscanf(file, "%s %s", usuarios[count].cpf, usuarios[count].senha) == 2) {
            count++;
        }
        fclose(file);
        return count; // Retorna o número de usuários carregados
    }

    // Função para salvar usuários no arquivo
    void salvarUsuarios(Usuario* usuarios, int numUsuarios) {
        FILE* file = fopen("H:\\ACADEMIC\\CODES\\C\\Gerenciamento_Estoque_C\\finalProject04\\usuarios.txt", "w");
        if (!file) {
            printf("\nErro ao abrir o arquivo de Usuarios.\n");
            return;
        }

        for (int i = 0; i < numUsuarios; i++) {
            fprintf(file, "%s %s\n", usuarios[i].cpf, usuarios[i].senha);
        }
        fclose(file);
    }



    // Função para realizar o login
    int login(Usuario* usuarios, int numUsuarios) {
        char cpf[TAM_CPF], senha[TAM_SENHA];
        printf("Digite seu CPF (11 digitos): ");
        scanf("%s", cpf);
        printf("Digite sua senha (8 caracteres): ");
        scanf("%s", senha);

        // Validação de dados
        if (!validarDados(cpf, senha)) {
            return 0; // Dados inválidos
        }

        // Verifica se o usuário existe
        for (int i = 0; i < numUsuarios; i++) {
            if (strcmp(usuarios[i].cpf, cpf) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
                printf("Login bem-sucedido. Bem-vindo!\n");
                return 1; // Login bem-sucedido
            }
        }
        printf("Credenciais incorretas.\n");
        return 0; // Login falhou
    }

    // Função para cadastrar novo usuário
    void cadastrarUsuario(Usuario* usuarios, int* numUsuarios) {
        int codAcesso = 3030;
        int codUsuario = 0;

        while (1) { // Loop para permitir repetição até entrada válida
            printf("Digite seu codigo de acesso para cadastro: ");
            scanf("%d", &codUsuario);

            if (codUsuario == codAcesso) {
                if (*numUsuarios >= MAX_USUARIOS) {
                    printf("Limite de usuarios alcançado.\n");
                    return;
                }

                char cpf[TAM_CPF], senha[TAM_SENHA];
                printf("Digite seu CPF (11 digitos): ");
                scanf("%s", cpf);
                printf("Digite sua senha (8 caracteres): ");
                scanf("%s", senha);

                // Validação de dados
                if (!validarDados(cpf, senha)) {
                    printf("Dados invalidos. CPF deve ter 11 dígitos e senha 8 caracteres.\n");
                    return; // Dados inválidos
                }

                // Verifica se o CPF já está cadastrado
                for (int i = 0; i < *numUsuarios; i++) {
                    if (strcmp(usuarios[i].cpf, cpf) == 0) {
                        printf("CPF ja cadastrado.\n");
                        return;
                    }
                }

                // Cadastra novo usuário
                strcpy(usuarios[*numUsuarios].cpf, cpf);
                strcpy(usuarios[*numUsuarios].senha, senha);
                (*numUsuarios)++;
                salvarUsuarios(usuarios, *numUsuarios); // Salva usuários atualizados
                printf("Usuario cadastrado com sucesso!\n");
                break; // Sai do loop após cadastro bem-sucedido
            } else {
                printf("Codigo de acesso incorreto. Tente novamente.\n"); // Mensagem se o código estiver errado
            }
        }
    }


    // Função principal que controla o fluxo do programa
    int controleProduto() {
        Produto produtos[MAX_PRODUTOS];  // Cria um array para armazenar os produtos
        int total_produtos = 0;  // Inicializa o total de produtos no estoque como 0
        carregar_estoque(produtos, &total_produtos);  // Carrega o estoque do arquivo no início do programa
        int opcao;
        do {
            printf("......... MENU .........\n");
            printf("1. Adicionar Produto\n");
            printf("2. Listar Produtos\n");
            printf("3. Editar Produto\n");
            printf("0. Salvar e Sair\n");
            printf("........................\n");
            printf("Escolha uma opcao: ");
            opcao = ler_inteiro();  // Lê a escolha do usuário, garantindo que seja um número inteiro

            switch (opcao) {
                case 1:
                    printf("\n");
                adicionar_produto(produtos, &total_produtos);  // Adiciona um novo produto ao estoque
                printf("\n");
                break;
                case 2:
                    printf("\n");
                listar_produtos(produtos, total_produtos);  // Lista os produtos no estoque
                printf("\n");
                break;
                case 3:
                    printf("\n");
                editar_produto(produtos, total_produtos);  // Edita um produto existente
                printf("\n");
                break;
                case 0:
                    printf("\n");
                salvar_estoque(produtos, total_produtos);  // Salva o estoque e encerra o programa
                printf("\n");
                printf("Estoque salvo. Saindo...\n");
                break;
                default:
                    printf("Opcao invalida. Tente novamente.\n");  // Exibe mensagem para opção inválida
            }
        } while (opcao != 0);  // Repete o loop até que o usuário escolha a opção de sair
        return 0;  // Finaliza o programa
    }


    // Função para ler um número inteiro do usuário, garantindo entrada válida
    int ler_inteiro() {
        int valor;
        while (1) {
            if (scanf("%d", &valor) == 1) {  // Verifica se a entrada foi um inteiro
                return valor;  // Se válido, retorna o valor
            } else {
                printf("Entrada invalida! Por favor, insira um numero inteiro: ");
                while (getchar() != '\n');  // Limpa o buffer do teclado para evitar loops infinitos
            }
        }
    }

    // Função para ler um número decimal (float) do usuário, garantindo entrada válida
    float ler_float() {
        float valor;
        while (1) {
            if (scanf("%f", &valor) == 1) {  // Verifica se a entrada foi um float válido
                return valor;  // Se válido, retorna o valor
            } else {
                printf("Entrada invalida! Por favor, insira um numero decimal: ");
                while (getchar() != '\n');  // Limpa o buffer do teclado
            }
        }
    }

    // Função para adicionar um novo produto ao estoque
    void adicionar_produto(Produto *produtos, int *total_produtos) {
        if (*total_produtos < MAX_PRODUTOS) {  // Verifica se ainda há espaço para adicionar mais produtos
            Produto novo_produto;  // Cria uma nova variável para armazenar o novo produto

            // Leitura do ID do produto
            printf("ID do produto: ");
            novo_produto.id = ler_inteiro();  // Garante que o ID será um número inteiro

            // Leitura do nome do produto
            printf("Nome do produto: ");
            scanf(" %[^\n]s", novo_produto.nome);  // Lê o nome do produto até encontrar uma nova linha

            // Leitura do preço do produto
            printf("Preco do produto: ");
            novo_produto.preco = ler_float();  // Garante que o preço será um número decimal

            // Valida se o preço é positivo
            while (novo_produto.preco < 0) {
                printf("Preco não pode ser negativo. Insira um valor positivo: ");
                novo_produto.preco = ler_float();  // Solicita nova entrada se o valor for inválido
            }

            // Leitura da quantidade no estoque
            printf("Quantidade no estoque: ");
            novo_produto.quantidade = ler_inteiro();  // Garante que a quantidade será um número inteiro

            // Valida se a quantidade é positiva
            while (novo_produto.quantidade < 0) {
                printf("Quantidade não pode ser negativa. Insira um valor positivo: ");
                novo_produto.quantidade = ler_inteiro();  // Solicita nova entrada se o valor for inválido
            }

            // Adiciona o novo produto à lista de produtos
            produtos[*total_produtos] = novo_produto;

            // Incrementa o número total de produtos
            (*total_produtos)++;
        } else {
            printf("Estoque cheio!\n");  // Caso o estoque esteja cheio, exibe uma mensagem de erro
        }
    }

    // Função para listar todos os produtos no estoque
    void listar_produtos(Produto *produtos, int total_produtos) {
        printf("---- Lista de Produtos no Estoque ----\n");
        for (int i = 0; i < total_produtos; i++) {  // Percorre todos os produtos no estoque
            printf("ID: %d\n", produtos[i].id);
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preco: %.2f\n", produtos[i].preco);  // Exibe o preço com 2 casas decimais
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("-----------------------------------\n");
        }
    }

    // Função para editar um produto existente no estoque
    void editar_produto(Produto *produtos, int total_produtos) {
        int id, encontrado = 0;
        printf("Digite o ID do produto que deseja editar: ");
        id = ler_inteiro();  // Lê o ID do produto que será editado

        // Busca o produto pelo ID fornecido
        for (int i = 0; i < total_produtos; i++) {
            if (produtos[i].id == id) {  // Se o ID do produto corresponde ao informado
                encontrado = 1;  // Marca que o produto foi encontrado
                printf("Editando o produto: %s\n", produtos[i].nome);

                // Leitura do novo nome do produto
                printf("Novo nome do produto: ");
                scanf(" %[^\n]s", produtos[i].nome);  // Atualiza o nome do produto

                // Leitura do novo preço do produto
                printf("Novo preco do produto: ");
                produtos[i].preco = ler_float();  // Atualiza o preço do produto

                // Valida se o preço é positivo
                while (produtos[i].preco < 0) {
                    printf("Preco não pode ser negativo. Insira um valor positivo: ");
                    produtos[i].preco = ler_float();  // Solicita nova entrada se o valor for inválido
                }

                // Leitura da nova quantidade no estoque
                printf("Nova quantidade no estoque: ");
                produtos[i].quantidade = ler_inteiro();  // Atualiza a quantidade do produto

                // Valida se a quantidade é positiva
                while (produtos[i].quantidade < 0) {
                    printf("Quantidade não pode ser negativa. Insira um valor positivo: ");
                    produtos[i].quantidade = ler_inteiro();  // Solicita nova entrada se o valor for inválido
                }
                break;  // Sai do loop após editar o produto
            }
        }
        if (!encontrado) {
            printf("Produto com ID %d não encontrado.\n", id);  // Caso não encontre o produto
        }
    }

    // Função para salvar o estoque de produtos em um arquivo
    void salvar_estoque(Produto *produtos, int total_produtos) {
        FILE *arquivo = fopen("H:\\ACADEMIC\\CODES\\C\\Gerenciamento_Estoque_C\\finalProject04\\estoque.txt", "w");  // Abre o arquivo "estoque.txt" para escrita
        if (arquivo == NULL) {  // Verifica se houve erro ao abrir o arquivo
            printf("Erro ao abrir o arquivo para gravacao!\n");
            return;  // Sai da função se o arquivo não pôde ser aberto
        }

        // Grava cada produto no arquivo
        for (int i = 0; i < total_produtos; i++) {
            fprintf(arquivo, "%d %s %.2f %d\n", produtos[i].id, produtos[i].nome, produtos[i].preco, produtos[i].quantidade);
        }

        fclose(arquivo);  // Fecha o arquivo após a gravação
    }

    // Função para carregar o estoque de produtos a partir de um arquivo
    void carregar_estoque(Produto *produtos, int *total_produtos) {
        FILE *arquivo = fopen("H:\\ACADEMIC\\CODES\\C\\Gerenciamento_Estoque_C\\finalProject04\\estoque.txt", "r");  // Abre o arquivo "estoque.txt" para leitura
        if (arquivo == NULL) {  // Verifica se houve erro ao abrir o arquivo
            printf("\nArquivo de Estoque Inexistente!\n");
            return;  // Sai da função se o arquivo não pôde ser aberto
        }

        // Lê cada linha do arquivo e carrega os dados para o array de produtos
        while (fscanf(arquivo, "%d %s %f %d", &produtos[*total_produtos].id, produtos[*total_produtos].nome,
                      &produtos[*total_produtos].preco, &produtos[*total_produtos].quantidade) != EOF) {
            (*total_produtos)++;  // Incrementa o total de produtos para cada linha lida
        }

        fclose(arquivo);  // Fecha o arquivo após a leitura
    }

    // Função para realizar o login e iniciar o controle de produtos
    int telaLogin() {
        Usuario usuarios[MAX_USUARIOS];
        int numUsuarios = carregarUsuarios(usuarios); // Carrega usuários do arquivo

        int opcao;
        do {
            printf("\n--- TELA DE INICIO ---\n");
            printf("1. Login\n");
            printf("2. Cadastrar Usuario\n");
            printf("0. Sair\n");
            printf("----------------------\n");
            printf("Escolha uma opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    if (login(usuarios, numUsuarios)) {
                        return 1;  // Login bem-sucedido, retorna 1 para iniciar o controleProduto()
                    } else {
                        printf("Login inexistente. Tente novamente.\n"); // Mensagem para login inválido
                    }
                break;
                case 2:
                    cadastrarUsuario(usuarios, &numUsuarios);
                break;
                case 0:
                    printf("Saindo do programa...\n");
                return 0;  // Finaliza o programa
                default:
                    printf("Opção inválida. Tente novamente.\n");
            }
        } while (opcao != 0);
        return 0;
    }

