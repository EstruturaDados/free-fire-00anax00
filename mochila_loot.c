#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 * Tema: Sistema de Inventário (Mochila Virtual)
 * Autora: Ana Carolina de Abreu Domingues
 *
 * Descrição:
 *   Este programa simula o inventário inicial de um jogador em um jogo de sobrevivência.
 *   O jogador pode cadastrar, remover, listar e buscar itens em uma mochila virtual.
 *   Cada item é representado por uma struct chamada Item e armazenado em um vetor.
 *
 *   Conceitos aplicados: struct, vetor de structs, busca sequencial, modularização com funções.
 */

#define MAX_ITENS 10
#define MAX_NOME 30
#define MAX_TIPO 20

typedef struct {
    char nome[MAX_NOME];
    char tipo[MAX_TIPO];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *tamanho);
void removerItem(Item mochila[], int *tamanho);
void listarItens(Item mochila[], int tamanho);
void buscarItem(Item mochila[], int tamanho);
int buscarPosicao(Item mochila[], int tamanho, const char *nome);

// Função principal
int main() {
    Item mochila[MAX_ITENS];
    int tamanho = 0;
    int opcao;

    printf("==============================\n");
    printf("  SISTEMA DE INVENTÁRIO - LOOT INICIAL\n");
    printf("==============================\n");

    do {
        printf("\n--- MENU DE OPÇÕES ---\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                inserirItem(mochila, &tamanho);
                break;
            case 2:
                removerItem(mochila, &tamanho);
                break;
            case 3:
                listarItens(mochila, tamanho);
                break;
            case 4:
                buscarItem(mochila, tamanho);
                break;
            case 0:
                printf("Saindo do sistema... Até logo!\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

/*
 * Função: inserirItem
 * -------------------
 * Permite o cadastro de um novo item na mochila, desde que haja espaço.
 */
void inserirItem(Item mochila[], int *tamanho) {
    if (*tamanho >= MAX_ITENS) {
        printf("A mochila está cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("\n--- Cadastro de Item ---\n");
    printf("Digite o nome do item: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // Remove o '\n'

    printf("Digite o tipo do item (ex: arma, munição, cura): ");
    fgets(novo.tipo, MAX_TIPO, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Digite a quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar();

    mochila[*tamanho] = novo;
    (*tamanho)++;

    printf("Item adicionado com sucesso!\n");
    listarItens(mochila, *tamanho);
}

/*
 * Função: removerItem
 * -------------------
 * Remove um item da mochila com base no nome informado.
 */
void removerItem(Item mochila[], int *tamanho) {
    if (*tamanho == 0) {
        printf("A mochila está vazia. Nenhum item para remover.\n");
        return;
    }

    char nome[MAX_NOME];
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscarPosicao(mochila, *tamanho, nome);
    if (pos == -1) {
        printf("Item '%s' não encontrado na mochila.\n", nome);
        return;
    }

    for (int i = pos; i < *tamanho - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    (*tamanho)--;

    printf("Item removido com sucesso!\n");
    listarItens(mochila, *tamanho);
}

/*
 * Função: listarItens
 * -------------------
 * Exibe todos os itens atualmente na mochila.
 */
void listarItens(Item mochila[], int tamanho) {
    printf("\n=== ITENS NA MOCHILA ===\n");

    if (tamanho == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("Item %d:\n", i + 1);
        printf("  Nome: %s\n", mochila[i].nome);
        printf("  Tipo: %s\n", mochila[i].tipo);
        printf("  Quantidade: %d\n", mochila[i].quantidade);
    }
}

/*
 * Função: buscarItem
 * ------------------
 * Busca um item na mochila com base no nome e exibe seus dados.
 */
void buscarItem(Item mochila[], int tamanho) {
    if (tamanho == 0) {
        printf("A mochila está vazia.\n");
        return;
    }

    char nome[MAX_NOME];
    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nome, MAX_NOME, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int pos = buscarPosicao(mochila, tamanho, nome);
    if (pos == -1) {
        printf("Item '%s' não encontrado.\n", nome);
    } else {
        printf("\nItem encontrado!\n");
        printf("  Nome: %s\n", mochila[pos].nome);
        printf("  Tipo: %s\n", mochila[pos].tipo);
        printf("  Quantidade: %d\n", mochila[pos].quantidade);
    }
}

/*
 * Função: buscarPosicao
 * ---------------------
 * Implementa busca sequencial no vetor de itens.
 */
int buscarPosicao(Item mochila[], int tamanho, const char *nome) {
    for (int i = 0; i < tamanho; i++) {
        if (strcmp(mochila[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}