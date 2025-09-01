

// ============================================================================
// Sistema de Inventário - Mochila de Loot Inicial
// Autor: [Seu Nome]
// Descrição: Simula o gerenciamento de uma mochila de loot em um jogo de sobrevivência.
// Permite cadastrar, remover, listar e buscar itens usando struct e vetor.
// ============================================================================

#include <stdio.h>      // Biblioteca para entrada e saída padrão
#include <string.h>     // Biblioteca para manipulação de strings
#include <stdlib.h>     // Biblioteca para funções utilitárias (não usada diretamente aqui)

// ===============================
// Sistema de Inventário - Mochila
// ===============================


// -----------------------------------------------------------------------------
// Definição da struct Item
// Cada item possui nome, tipo e quantidade.
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura", "ferramenta")
    int quantidade;     // Quantidade do item
} Item;


// -----------------------------------------------------------------------------
// Protótipos das funções principais do sistema
// -----------------------------------------------------------------------------
void inserirItem(Item* mochila, int* numItens);           // Cadastra novo item
void removerItem(Item* mochila, int* numItens);           // Remove item pelo nome
void listarItens(const Item* mochila, int numItens);      // Lista todos os itens
void buscarItem(const Item* mochila, int numItens);       // Busca item pelo nome

// -----------------------------------------------------------------------------
// Função utilitária para limpar o buffer de entrada
// Remove caracteres remanescentes do buffer após uso de scanf
// -----------------------------------------------------------------------------
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.



// -----------------------------------------------------------------------------
// Função principal: exibe o menu e gerencia o fluxo do programa
// -----------------------------------------------------------------------------
int main() {
    Item mochila[10]; // Vetor de até 10 itens na mochila
    int numItens = 0; // Quantidade atual de itens cadastrados
    int opcao;        // Opção escolhida pelo usuário

    printf("\n=== MOCHILA DE LOOT INICIAL ===\n");
    do {
        // Exibe o menu de opções
        printf("\nEscolha uma opção:\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item pelo nome\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        // Executa a ação de acordo com a opção escolhida
        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens); // Cadastrar novo item
                break;
            case 2:
                removerItem(mochila, &numItens); // Remover item
                break;
            case 3:
                listarItens(mochila, numItens);  // Listar itens
                break;
            case 4:
                buscarItem(mochila, numItens);   // Buscar item
                break;
            case 0:
                printf("Saindo do inventário. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0); // Repete até o usuário escolher sair
    return 0;
}



// -----------------------------------------------------------------------------
// Função: inserirItem
// Descrição: Cadastra um novo item na mochila, se houver espaço.
// Parâmetros:
//   - mochila: vetor de itens
//   - numItens: ponteiro para a quantidade atual de itens
// -----------------------------------------------------------------------------
void inserirItem(Item* mochila, int* numItens) {
    if (*numItens >= 10) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    printf("\nCadastro de novo item:\n");
    printf("Nome do item: ");
    fgets(mochila[*numItens].nome, 30, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = '\0'; // Remove o \n
    printf("Tipo do item (arma, munição, cura, ferramenta): ");
    fgets(mochila[*numItens].tipo, 20, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    limparBufferEntrada();
    (*numItens)++;
    printf("Item cadastrado com sucesso!\n");
    listarItens(mochila, *numItens); // Exibe a lista após cadastro
}


// -----------------------------------------------------------------------------
// Função: removerItem
// Descrição: Remove um item da mochila pelo nome, se existir.
// Parâmetros:
//   - mochila: vetor de itens
//   - numItens: ponteiro para a quantidade atual de itens
// -----------------------------------------------------------------------------
void removerItem(Item* mochila, int* numItens) {
    if (*numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("\nDigite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    int encontrado = -1;
    // Busca sequencial pelo nome
    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    if (encontrado == -1) {
        printf("Item não encontrado na mochila!\n");
        return;
    }
    // Remove o item deslocando os seguintes
    for (int i = encontrado; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*numItens)--;
    printf("Item removido com sucesso!\n");
    listarItens(mochila, *numItens); // Exibe a lista após remoção
}


// -----------------------------------------------------------------------------
// Função: listarItens
// Descrição: Exibe todos os itens cadastrados na mochila em formato de tabela.
// Parâmetros:
//   - mochila: vetor de itens
//   - numItens: quantidade de itens cadastrados
// -----------------------------------------------------------------------------
void listarItens(const Item* mochila, int numItens) {
    printf("\nItens na mochila:\n");
    if (numItens == 0) {
        printf("(Mochila vazia)\n");
        return;
    }
    printf("%-25s %-15s %-10s\n", "Nome", "Tipo", "Quantidade");
    for (int i = 0; i < numItens; i++) {
        printf("%-25s %-15s %-10d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
    }
}


// -----------------------------------------------------------------------------
// Função: buscarItem
// Descrição: Busca um item pelo nome usando busca sequencial e exibe seus dados.
// Parâmetros:
//   - mochila: vetor de itens
//   - numItens: quantidade de itens cadastrados
// -----------------------------------------------------------------------------
void buscarItem(const Item* mochila, int numItens) {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    // Busca sequencial pelo nome
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado na mochila!\n");
}
