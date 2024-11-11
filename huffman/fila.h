/**
 * @file fila.h
 * @brief Arquivo de cabeçalho para a implementação da fila de prioridade usada na codificação de Huffman.
 *
 * Este arquivo contém as definições e protótipos de funções para uma fila de prioridade
 * implementada usando uma lista ligada. A fila de prioridade é usada para gerenciar nós
 * no algoritmo de codificação de Huffman.
 */

#ifndef FILA_H
#define FILA_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Estrutura que representa um nó na fila de prioridade.
 *
 * Esta estrutura representa um nó na fila de prioridade. Cada nó contém
 * um item, sua frequência e ponteiros para o próximo nó na fila, bem como
 * nós filhos esquerdo e direito para uso na árvore de Huffman.
 */
typedef struct node {
    void *item;          /**< Ponteiro para o item armazenado no nó */
    void *frequency;     /**< Ponteiro para a frequência do item */
    struct node *next;   /**< Ponteiro para o próximo nó na fila */
    struct node *left;   /**< Ponteiro para o nó filho esquerdo (para a árvore de Huffman) */
    struct node *right;  /**< Ponteiro para o nó filho direito (para a árvore de Huffman) */
} Node;

/**
 * @brief Estrutura que representa a fila de prioridade.
 *
 * Esta estrutura representa a fila de prioridade, que é implementada como uma lista ligada.
 * A fila mantém um ponteiro para o nó cabeça.
 */
typedef struct priorityQueue {
    Node *head; /**< Ponteiro para o nó cabeça da fila */
} Queue;

/**
 * @brief Cria uma nova fila de prioridade.
 *
 * Esta função aloca memória para uma nova fila de prioridade e inicializa sua cabeça como NULL.
 *
 * @return Ponteiro para a fila de prioridade recém-criada.
 */
Queue *createQueue();

/**
 * @brief Verifica se a fila de prioridade está vazia.
 *
 * Esta função verifica se a fila de prioridade está vazia examinando seu ponteiro cabeça.
 *
 * @param fila Ponteiro para a fila de prioridade.
 * @return 1 se a fila estiver vazia, 0 caso contrário.
 */
int isEmpty(Queue *fila);

/**
 * @brief Enfileira um item na fila de prioridade.
 *
 * Esta função cria um novo nó com o item e a frequência fornecidos, e o insere
 * na fila de prioridade na posição correta com base em sua frequência.
 *
 * @param fila Ponteiro para a fila de prioridade.
 * @param item O item a ser enfileirado.
 * @param frequency A frequência do item.
 */
void enqueue(Queue *fila, unsigned char item, int frequency);


#endif // FILA_H