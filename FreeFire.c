
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ===============================
// Sistema de Inventário - Mochila
// ===============================

// Struct que representa um item do inventário
typedef struct {
    char nome[30];      // Nome do item (ex: "AK-47", "Kit Médico")
    char tipo[20];      // Tipo do item (ex: "arma", "munição", "cura", "ferramenta")
    int quantidade;     // Quantidade do item
} Item;

// Funções obrigatórias
void inserirItem(Item* mochila, int* numItens);
void removerItem(Item* mochila, int* numItens);
void listarItens(const Item* mochila, int numItens);
void buscarItem(const Item* mochila, int numItens);

// Função utilitária para limpar o buffer de entrada
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Código da Ilha – Edição Free Fire
// Nível: Mestre
// Este programa simula o gerenciamento avançado de uma mochila com componentes coletados durante a fuga de uma ilha.
// Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.


int main() {
    Item mochila[10]; // Vetor de até 10 itens
    int numItens = 0; // Quantidade atual de itens na mochila
    int opcao;

    printf("\n=== MOCHILA DE LOOT INICIAL ===\n");
    do {
        printf("\nEscolha uma opção:\n");
        printf("1. Cadastrar novo item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item pelo nome\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limparBufferEntrada();

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo do inventário. Até a próxima!\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);
    return 0;
}


// Função para cadastrar um novo item na mochila
void inserirItem(Item* mochila, int* numItens) {
    if (*numItens >= 10) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }
    printf("\nCadastro de novo item:\n");
    printf("Nome do item: ");
    fgets(mochila[*numItens].nome, 30, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = '\0';
    printf("Tipo do item (arma, munição, cura, ferramenta): ");
    fgets(mochila[*numItens].tipo, 20, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = '\0';
    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    limparBufferEntrada();
    (*numItens)++;
    printf("Item cadastrado com sucesso!\n");
    listarItens(mochila, *numItens);
}

// Função para remover um item da mochila pelo nome
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
    for (int i = encontrado; i < *numItens - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*numItens)--;
    printf("Item removido com sucesso!\n");
    listarItens(mochila, *numItens);
}

// Função para listar todos os itens da mochila
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

// Função para buscar um item pelo nome (busca sequencial)
void buscarItem(const Item* mochila, int numItens) {
    if (numItens == 0) {
        printf("A mochila está vazia!\n");
        return;
    }
    char nomeBusca[30];
    printf("\nDigite o nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("Item encontrado:\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n", mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
            return;
        }
    }
    printf("Item não encontrado na mochila!\n");
}