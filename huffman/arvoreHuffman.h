#ifndef ARVOREHUFFMAN_H
#define ARVOREHUFFMAN_H

#include "fila.h"

/**
 * @brief Verifica se a lista está vazia.
 * 
 * @param head Ponteiro para o início da lista.
 * @return int Retorna 1 se a lista estiver vazia, 0 caso contrário.
 */
int isEmptyList(Node *head);

/**
 * @brief Retorna o máximo de dois inteiros.
 * 
 * @param a Primeiro inteiro.
 * @param b Segundo inteiro.
 * @return int O máximo entre a e b.
 */
int max(int a, int b);

/**
 * @brief Cria uma árvore de Huffman a partir de uma lista de nós.
 * 
 * @param fila Ponteiro para o início da lista de nós.
 * @return Node* Ponteiro para a raiz da árvore de Huffman criada.
 */
Node *criarArvoreHuffman(Node *fila);

/**
 * @brief Calcula a altura da árvore de Huffman.
 * 
 * @param arvore Ponteiro para a raiz da árvore de Huffman.
 * @return int A altura da árvore de Huffman.
 */
int height(Node *arvore);

/**
 * @brief Salva a árvore de Huffman em percurso pré-ordem.
 * 
 * @param arvore Ponteiro para a raiz da árvore de Huffman.
 * @param array Array para armazenar o percurso pré-ordem.
 * @param i Ponteiro para o índice atual no array.
 * @param tamArvore Ponteiro para o tamanho da árvore.
 */
void salvarArvorePreOrdem(Node *arvore, unsigned char array[], int *i, int *tamArvore);

/**
 * @brief Reconstrói a árvore de Huffman a partir de uma string de percurso pré-ordem.
 * 
 * @param string Array contendo o percurso pré-ordem.
 * @param size Tamanho do array.
 * @param i Ponteiro para o índice atual no array.
 * @param tree Ponteiro para a raiz da árvore de Huffman.
 * @return Node* Ponteiro para a árvore de Huffman reconstruída.
 */
Node *refazerArvore(unsigned char string[], int size, int *i, Node *tree);

#endif //ARVOREHUFFMAN_H
