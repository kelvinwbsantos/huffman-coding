/**
 * @file codificacao.h
 * @brief Arquivo de cabeçalho para funções de codificação Huffman.
 *
 * Este arquivo contém as declarações das funções usadas para compressão
 * e descompressão de arquivos usando o algoritmo de codificação Huffman.
 */

#ifndef CODIFICACAO_H
#define CODIFICACAO_H

#include "fila.h"
#include "bytes.h"
#include <string.h>

/**
 * @brief Calcula o tamanho de um arquivo.
 *
 * Esta função calcula o tamanho do arquivo apontado pelo ponteiro de arquivo fornecido.
 * Ela move o ponteiro do arquivo para o final, obtém a posição atual do ponteiro (que é o tamanho do arquivo),
 * e depois volta o ponteiro para o início do arquivo.
 *
 * @param f Ponteiro para o arquivo.
 * @return O tamanho do arquivo em bytes.
 */
long int tamArquivo(FILE *f);

/**
 * @brief Comprime um arquivo usando a codificação Huffman.
 *
 * Esta função comprime um arquivo usando o algoritmo de codificação Huffman. Ela realiza as seguintes etapas:
 * 1. Lê o arquivo e calcula a frequência de cada byte.
 * 2. Constrói a árvore de Huffman com base nas frequências calculadas.
 * 3. Cria uma tabela de códigos de Huffman a partir da árvore.
 * 4. Codifica o arquivo original usando a tabela de códigos.
 * 5. Salva o arquivo comprimido, incluindo a árvore de Huffman e os dados codificados.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int compactarArquivo(const char *caminhoArquivo);

/**
 * @brief Descomprime um arquivo usando a codificação Huffman.
 *
 * Esta função descomprime um arquivo que foi comprimido usando o algoritmo de codificação Huffman. Ela realiza as seguintes etapas:
 * 1. Lê o cabeçalho do arquivo comprimido para obter o tamanho da árvore de Huffman e a quantidade de bits de lixo.
 * 2. Reconstrói a árvore de Huffman a partir dos dados lidos.
 * 3. Lê os dados comprimidos e decodifica-os usando a árvore de Huffman.
 * 4. Salva os dados descomprimidos em um novo arquivo.
 *
 * @return 0 em caso de sucesso, 1 em caso de falha.
 */
int descompactarArquivo(const char *caminhoArquivo);

/**
 * @brief Abre o arquivo e verifica erros.
 *
 * Esta função abre o arquivo no caminho especificado e verifica se houve erros ao abrir.
 *
 * @param caminhoArquivo Caminho do arquivo a ser aberto.
 * @return Ponteiro para o arquivo aberto, ou NULL em caso de erro.
 */
FILE *abrirArquivo(const char *caminhoArquivo);

/**
 * @brief Calcula a frequência dos bytes no arquivo.
 *
 * Esta função lê o arquivo e calcula a frequência de cada byte presente nele.
 *
 * @param f Ponteiro para o arquivo.
 * @param listaBytes Ponteiro para armazenar os bytes lidos.
 * @param frequencia Array para armazenar a frequência de cada byte.
 */
void calcularFrequencia(FILE *f, unsigned char *listaBytes, int *frequencia);

/**
 * @brief Enfileira os bytes com suas respectivas frequências.
 *
 * Esta função enfileira os bytes e suas frequências em uma fila.
 *
 * @param fila Ponteiro para a fila.
 * @param frequencia Array contendo a frequência de cada byte.
 */
void enfileirarBytes(Queue *fila, int *frequencia);

/**
 * @brief Cria o nome do arquivo compactado.
 *
 * Esta função cria o nome do arquivo compactado a partir do caminho original.
 *
 * @param caminhoArquivo Caminho do arquivo original.
 * @param nomeArquivo Ponteiro para armazenar o nome do arquivo compactado.
 */
void criarNomeArquivoCompactado(const char *caminhoArquivo, char *nomeArquivo);

#endif // CODIFICACAO_H