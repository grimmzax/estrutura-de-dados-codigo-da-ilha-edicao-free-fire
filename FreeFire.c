// ============================================================================
// Módulo Avançado: Organização dos Componentes da Torre de Fuga
// Permite cadastrar, ordenar e buscar componentes essenciais para a missão final.
// O jogador pode escolher o algoritmo de ordenação e visualizar o desempenho.
// ============================================================================

#include <time.h> // Biblioteca para medir tempo de execução

// -----------------------------------------------------------------------------
// Definição da struct Componente
// Cada componente possui nome, tipo e prioridade (1 a 10)
// -----------------------------------------------------------------------------
typedef struct {
    char nome[30];      // Nome do componente (ex: "chip central")
    char tipo[20];      // Tipo do componente (ex: "controle", "suporte", "propulsão")
    int prioridade;     // Prioridade do componente (1 a 10)
} Componente;

// -----------------------------------------------------------------------------
// Protótipos das funções do módulo torre de fuga
// -----------------------------------------------------------------------------
void cadastrarComponentes(Componente* torre, int* n);
void mostrarComponentes(const Componente* torre, int n);
void bubbleSortNome(Componente* torre, int n, int* comparacoes);
void insertionSortTipo(Componente* torre, int n, int* comparacoes);
void selectionSortPrioridade(Componente* torre, int n, int* comparacoes);
int buscaBinariaPorNome(const Componente* torre, int n, const char* chave, int* comparacoes);
void medirTempo(void (*algoritmo)(Componente*, int, int*), Componente* torre, int n, int* comparacoes, double* tempo);

// -----------------------------------------------------------------------------
// Função para cadastrar até 20 componentes da torre de fuga
// -----------------------------------------------------------------------------
void cadastrarComponentes(Componente* torre, int* n) {
    printf("\nCadastro dos componentes da torre de fuga:\n");
    int qtd;
    do {
        printf("Quantos componentes deseja cadastrar (1 a 20)? ");
        scanf("%d", &qtd);
        limparBufferEntrada();
    } while (qtd < 1 || qtd > 20);
    *n = qtd;
    for (int i = 0; i < *n; i++) {
        printf("\nComponente %d:\n", i+1);
        printf("  Nome: ");
        fgets(torre[i].nome, 30, stdin);
        torre[i].nome[strcspn(torre[i].nome, "\n")] = '\0';
        printf("  Tipo: ");
        fgets(torre[i].tipo, 20, stdin);
        torre[i].tipo[strcspn(torre[i].tipo, "\n")] = '\0';
        do {
            printf("  Prioridade (1 a 10): ");
            scanf("%d", &torre[i].prioridade);
            limparBufferEntrada();
        } while (torre[i].prioridade < 1 || torre[i].prioridade > 10);
    }
}

// -----------------------------------------------------------------------------
// Função para exibir todos os componentes cadastrados
// -----------------------------------------------------------------------------
void mostrarComponentes(const Componente* torre, int n) {
    printf("\nComponentes da torre de fuga:\n");
    printf("%-25s %-15s %-10s\n", "Nome", "Tipo", "Prioridade");
    for (int i = 0; i < n; i++) {
        printf("%-25s %-15s %-10d\n", torre[i].nome, torre[i].tipo, torre[i].prioridade);
    }
}

// -----------------------------------------------------------------------------
// Bubble Sort: ordena os componentes por nome (string)
// -----------------------------------------------------------------------------
void bubbleSortNome(Componente* torre, int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            (*comparacoes)++;
            if (strcmp(torre[j].nome, torre[j+1].nome) > 0) {
                Componente temp = torre[j];
                torre[j] = torre[j+1];
                torre[j+1] = temp;
            }
        }
    }
}

// -----------------------------------------------------------------------------
// Insertion Sort: ordena os componentes por tipo (string)
// -----------------------------------------------------------------------------
void insertionSortTipo(Componente* torre, int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = torre[i];
        int j = i - 1;
        while (j >= 0 && (++(*comparacoes), strcmp(chave.tipo, torre[j].tipo) < 0)) {
            torre[j+1] = torre[j];
            j--;
        }
        torre[j+1] = chave;
    }
}

// -----------------------------------------------------------------------------
// Selection Sort: ordena os componentes por prioridade (int)
// -----------------------------------------------------------------------------
void selectionSortPrioridade(Componente* torre, int n, int* comparacoes) {
    *comparacoes = 0;
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++) {
            (*comparacoes)++;
            if (torre[j].prioridade < torre[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            Componente temp = torre[i];
            torre[i] = torre[min];
            torre[min] = temp;
        }
    }
}

// -----------------------------------------------------------------------------
// Busca binária por nome (apenas após ordenação por nome)
// Retorna o índice do componente ou -1 se não encontrado
// -----------------------------------------------------------------------------
int buscaBinariaPorNome(const Componente* torre, int n, const char* chave, int* comparacoes) {
    int ini = 0, fim = n-1, meio;
    *comparacoes = 0;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        (*comparacoes)++;
        int cmp = strcmp(chave, torre[meio].nome);
        if (cmp == 0) return meio;
        else if (cmp < 0) fim = meio - 1;
        else ini = meio + 1;
    }
    return -1;
}

// -----------------------------------------------------------------------------
// Função para medir o tempo de execução de um algoritmo de ordenação
// -----------------------------------------------------------------------------
void medirTempo(void (*algoritmo)(Componente*, int, int*), Componente* torre, int n, int* comparacoes, double* tempo) {
    clock_t ini = clock();
    algoritmo(torre, n, comparacoes);
    clock_t fim = clock();
    *tempo = (double)(fim - ini) / CLOCKS_PER_SEC;
}

// -----------------------------------------------------------------------------
// Menu do módulo torre de fuga: cadastro, ordenação, busca e análise de desempenho
// -----------------------------------------------------------------------------
void moduloTorreFuga() {
    Componente torre[20];
    int n = 0;
    int comparacoes = 0;
    double tempo = 0.0;
    int ordenadoPor = 0; // 1-nome, 2-tipo, 3-prioridade
    char chaveBusca[30];
    int idx;
    int op;
    do {
        printf("\n=== MÓDULO TORRE DE FUGA ===\n");
        printf("1. Cadastrar componentes\n");
        printf("2. Ordenar por nome (Bubble Sort)\n");
        printf("3. Ordenar por tipo (Insertion Sort)\n");
        printf("4. Ordenar por prioridade (Selection Sort)\n");
        printf("5. Buscar componente-chave por nome (binária)\n");
        printf("6. Mostrar componentes\n");
        printf("0. Sair do módulo torre\n");
        printf("Opção: ");
        scanf("%d", &op);
        limparBufferEntrada();
        switch (op) {
            case 1:
                cadastrarComponentes(torre, &n);
                break;
            case 2:
                medirTempo(bubbleSortNome, torre, n, &comparacoes, &tempo);
                ordenadoPor = 1;
                printf("Componentes ordenados por nome (Bubble Sort). Comparações: %d | Tempo: %.6fs\n", comparacoes, tempo);
                break;
            case 3:
                medirTempo(insertionSortTipo, torre, n, &comparacoes, &tempo);
                ordenadoPor = 2;
                printf("Componentes ordenados por tipo (Insertion Sort). Comparações: %d | Tempo: %.6fs\n", comparacoes, tempo);
                break;
            case 4:
                medirTempo(selectionSortPrioridade, torre, n, &comparacoes, &tempo);
                ordenadoPor = 3;
                printf("Componentes ordenados por prioridade (Selection Sort). Comparações: %d | Tempo: %.6fs\n", comparacoes, tempo);
                break;
            case 5:
                if (ordenadoPor != 1) {
                    printf("É necessário ordenar por nome antes da busca binária!\n");
                    break;
                }
                printf("Nome do componente-chave para busca: ");
                fgets(chaveBusca, 30, stdin);
                chaveBusca[strcspn(chaveBusca, "\n")] = '\0';
                comparacoes = 0;
                idx = buscaBinariaPorNome(torre, n, chaveBusca, &comparacoes);
                if (idx != -1) {
                    printf("Componente encontrado! Comparações: %d\n", comparacoes);
                    printf("Nome: %s | Tipo: %s | Prioridade: %d\n", torre[idx].nome, torre[idx].tipo, torre[idx].prioridade);
                } else {
                    printf("Componente não encontrado. Comparações: %d\n", comparacoes);
                }
                break;
            case 6:
                mostrarComponentes(torre, n);
                break;
            case 0:
                printf("Saindo do módulo torre de fuga.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (op != 0);
}


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
// Função principal: menu para escolher estrutura e operações
// -----------------------------------------------------------------------------
int main() {
    int estrutura; // 1 = Vetor, 2 = Lista Encadeada, 3 = Torre de Fuga
    int sair = 0;

    printf("\n=== MOCHILA DE LOOT: Vetor vs Lista Encadeada ===\n");
    printf("Escolha o módulo:\n");
    printf("1. Mochila com Vetor (lista sequencial)\n");
    printf("2. Mochila com Lista encadeada\n");
    printf("3. Torre de Fuga (componentes, ordenação, busca)\n");
    printf("Opção: ");
    scanf("%d", &estrutura);
    limparBufferEntrada();

    if (estrutura == 1) {
        // ...código do menu do vetor...
        // ...existing code...
    } else if (estrutura == 2) {
        // ...código do menu da lista encadeada...
        // ...existing code...
    } else if (estrutura == 3) {
        moduloTorreFuga();
    } else {
        printf("Opção inválida!\n");
    }
    return 0;
}
                // ...código do menu do vetor...
                // ...existing code...
            } else if (estrutura == 2) {
                // ...código do menu da lista encadeada...
                // ...existing code...
            } else if (estrutura == 3) {
                moduloTorreFuga();
            } else {
                printf("Opção inválida!\n");
            }
            return 0;
        }
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
