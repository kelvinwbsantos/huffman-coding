#ifndef BYTES_H
#define BYTES_H

#include <string.h>
#include "arvoreHuffman.h"

/**
 * @brief Verifica se o i-ésimo bit de um byte está definido.
 * 
 * @param c O byte a ser verificado.
 * @param i A posição do bit a ser verificada (0-7).
 * @return int 1 se o bit estiver definido, 0 caso contrário.
 */
int isBitSet(unsigned char c, int i);

/**
 * @brief Define o i-ésimo bit de um byte.
 * 
 * @param c O byte a ser modificado.
 * @param i A posição do bit a ser definida (0-7).
 * @return unsigned char O byte modificado.
 */
unsigned char setBit(unsigned char c, int i);

/**
 * @brief Verifica se o i-ésimo bit de um short está definido.
 * 
 * @param c O short a ser verificado.
 * @param i A posição do bit a ser verificada (0-15).
 * @return int 1 se o bit estiver definido, 0 caso contrário.
 */
int isHeaderSet(unsigned short c, int i);

/**
 * @brief Define o i-ésimo bit de um short.
 * 
 * @param c O short a ser modificado.
 * @param i A posição do bit a ser definida (0-15).
 * @return unsigned short O short modificado.
 */
unsigned short setHeader(unsigned short c, int i);

/**
 * @brief Aloca um array 2D (mapa) para armazenar os códigos de Huffman.
 * 
 * @param colunas O número de colunas (comprimento de cada código).
 * @return char** O array 2D alocado.
 */
char **alocarMapa(int colunas);

/**
 * @brief Cria um mapa de códigos de Huffman a partir de uma árvore de Huffman.
 * 
 * @param tabela O array 2D para armazenar os códigos.
 * @param raiz A raiz da árvore de Huffman.
 * @param caminho O caminho atual (código) na árvore.
 * @param colunas O número de colunas (comprimento de cada código).
 * @param nos O número de nós processados.
 */
void criarMapa(char **tabela, Node *raiz, char *caminho, int colunas, int *nos);

/**
 * @brief Calcula o comprimento total dos dados codificados.
 * 
 * @param tabela O array 2D contendo os códigos de Huffman.
 * @param listaBytes A lista de bytes a serem codificados.
 * @param tamListaBytes O tamanho da lista de bytes.
 * @return unsigned long long int O comprimento total dos dados codificados.
 */
unsigned long long int tamCodificado(char **tabela, unsigned char *listaBytes, long int tamListaBytes);

/**
 * @brief Codifica um arquivo usando os códigos de Huffman.
 * 
 * @param tabela O array 2D contendo os códigos de Huffman.
 * @param listaBytes A lista de bytes a serem codificados.
 * @param tamListaBytes O tamanho da lista de bytes.
 * @param tamSaida O tamanho da saída codificada.
 * @return char* O arquivo codificado como uma string.
 */
char *codificarArquivo(char **tabela, unsigned char *listaBytes, long int tamListaBytes, long int *tamSaida);

/**
 * @brief Salva o arquivo compactado.
 * 
 * @param tamCodificado O tamanho dos dados codificados.
 * @param bytesArvore Os bytes que representam a árvore de Huffman.
 * @param arquivoCodificado O arquivo codificado como uma string.
 * @param tamArvore O tamanho da árvore de Huffman.
 * @param nomeArquivo O nome do arquivo de saída.
 * @return int 1 se bem-sucedido, 0 caso contrário.
 */
int salvarCompactado(long int tamCodificado, unsigned char bytesArvore[], char *arquivoCodificado, int tamArvore, char nomeArquivo[]);

#endif // BYTES_H
