#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct

{
    int cd;
    char nome[50];
    int quantidade;
    char descricao[100];
    float preco;
    struct Produto *prox;
} Produto;

Produto *criarListaVazia()

{
    return NULL;
}
/*função para criar um novo registro */
Produto *criarProduto()
{
    Produto *novoProduto;
    novoProduto = (Produto *)malloc(sizeof(Produto));
    if (novoProduto == NULL)
    {
        printf("Erro de alocacao\n");
        exit(EXIT_FAILURE);
    }
    novoProduto->cd = rand();
    novoProduto->prox = NULL;
    return novoProduto;
}

/*função para cadastrar um novo produto */
void cadastrar(Produto **estoque)
{
    printf("\nCadastro dos Produtos\n");

    Produto *novoProduto = criarProduto();

    printf("Digite o nome do produto: ");
    scanf("%s", novoProduto->nome);

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preco individual do produto: ");
    scanf("%f", &novoProduto->preco);

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("Produto cadastrado com sucesso!\n");
}

/*função para adicionar um novo produto */
void adicionaProduto(Produto **estoque)
{
    printf("\nAdicionar novo produto a lista cadastrar\n");

    Produto *novoProduto = criarProduto();

    printf("Digite o nome do novo produto:");
    scanf("%s", novoProduto->nome);

    printf("Descreva o produto:");
    getchar();
    fgets(novoProduto->descricao, sizeof(novoProduto->descricao), stdin);
    novoProduto->descricao[strcspn(novoProduto->descricao, "\n")] = '\0';

    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->quantidade);

    printf("Informe o preco individual do produto: ");
    scanf("%f", &novoProduto->preco);

    novoProduto->prox = *estoque;
    *estoque = novoProduto;

    printf("Novo produto cadastrado com sucesso!\n");
}

/*função para buscar um produto */
void buscar(Produto *estoque)
{
    int cd;
    printf("Buscar Produto\n");

    printf("\nCodigo do produto: ");
    scanf("%d", &cd);

    Produto *atual = estoque;

    while (atual != NULL)
    {
        if (atual->cd == cd)
        {
            printf("Produto encontrado:\n");
            printf("Codigo: %d\n", atual->cd);
            printf("Nome: %s\n", atual->nome);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Preco: %.2f\n", atual->preco);
            return;
        }
        atual = atual->prox;
    }

    printf("Produto nao encontrado!\n");

}

/*função para imprimir a lista de produtos */
void imprimir(Produto *estoque)
{
    printf("Lista de Produtos:\n");

    Produto *atual = estoque;

    while (atual != NULL)
    {
        printf("Codigo: %d, Nome: %s, Quantidade: %d, Preco: %.2f\n",
               atual->cd, atual->nome, atual->quantidade, atual->preco);
        atual = atual->prox;
    }
}

/*função para excluir um produto */
void excluir(Produto **estoque)
{
    int codigo;
    printf("Excluir Produto\n");

    printf("Codigo do produto: ");
    scanf("%d", &codigo);

    Produto *atual = *estoque;
    Produto *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->cd == codigo)
        {
            if (anterior == NULL)
            {
                *estoque = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }

            free(atual);
            printf("\nProduto removido com sucesso!\n");
            return;
        }

        anterior = atual;
        atual = atual->prox;
    }

    printf("\nProduto nao encontrado.\n");
    
    return;
}

/*função para imprimir o relatório dos produtos */
void imprimirRelatorioProduto(Produto *estoque)
{
    printf("\nRelatorio Dos Produtos\n");

    Produto *atual = estoque;

    while (atual != NULL)
    {
        printf("\nCodigo: %d\n", atual->cd);
        printf("Nome: %s\n", atual->nome);
        printf("Descricao: %s\n", atual->descricao);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Preco: %.2f\n", atual->preco);
        printf("Total do Estoque de Produtos: R$ %.2f\n", atual->quantidade * atual->preco);

        atual = atual->prox;
    }
}

int main()
{
    srand((unsigned int)time(NULL));

    Produto *estoque = criarListaVazia();
    int opcao;

    do
    {

        printf("\nLista de Opcoes!\n");
        printf("\n1: Cadastrar Produto");
        printf("\n2: Buscar Produto");
        printf("\n3: Imprimir Estoque");
        printf("\n4: Excluir Produto");
        printf("\n5: Adicionar Novo Produto");
        printf("\n6: Imprimir Relatorio Dos Produtos");
        printf("\n0: Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch (opcao)
        {
        case 1:
            cadastrar(&estoque);
            break;
        case 2:
            buscar(estoque);
            break;
        case 3:
            imprimir(estoque);
            break;
        case 4:
            excluir(&estoque);
            break;
        case 5:
            adicionaProduto(&estoque);
            break;
        case 6:
            imprimirRelatorioProduto(estoque);
            break;
        case 0:
            printf("\nPrograma encerrado!\n");
            break;
        default:
            printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    Produto *atual = estoque;
    while (atual != NULL)
    {
        Produto *temp = atual;
        atual = atual->prox;
        free(temp);
    }

    return 0;
}
