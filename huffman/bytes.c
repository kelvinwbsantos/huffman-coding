#include "bytes.h"

// Aloca uma tabela de 256 ponteiros para strings, cada string com tamanho colunas

char **alocarMapa(int colunas)
{
    char **tabela;

    tabela = malloc(256 * sizeof(char *));

    for (int i = 0; i < 256; i++)
        tabela[i] = calloc(colunas, sizeof(char));

    return tabela;
}

// Cria um mapa de codificação a partir da árvore de Huffman

void criarMapa(char **tabela, Node *raiz, char *caminho, int colunas, int *nos)
{
    // Declara dois arrays de caracteres para armazenar os caminhos da esquerda e da direita
    char esquerda[colunas], direita[colunas];

    // Incrementa o contador de nós
    (*nos)++;

    // Verifica se o nó atual é uma folha (não possui filhos)
    if (isEmptyList(raiz->left) && isEmptyList(raiz->right))
    {
        // Se for uma folha, obtém o caractere armazenado no nó
        unsigned char c = *(unsigned char *)raiz->item;
        // Copia o caminho atual para a tabela na posição do caractere
        strcpy(tabela[c], caminho);
    }
    else
    {
        // Se não for uma folha, copia o caminho atual para os arrays esquerda e direita
        strcpy(esquerda, caminho);
        strcpy(direita, caminho);

        // Adiciona '0' ao caminho da esquerda e '1' ao caminho da direita
        strcat(esquerda, "0");
        strcat(direita, "1");

        // Chama recursivamente a função criarMapa para os filhos esquerdo e direito
        criarMapa(tabela, raiz->left, esquerda, colunas, nos);
        criarMapa(tabela, raiz->right, direita, colunas, nos);
    }
}

// Calcula o tamanho total do arquivo codificado

unsigned long long int tamCodificado(char **tabela, unsigned char *listaBytes, long int tamListaBytes)
{
    unsigned long long int tam_codificado = 0;
    
    for (int i = 0; i != tamListaBytes; i++)
        tam_codificado += strlen(tabela[listaBytes[i]]);
        
    return tam_codificado;
}

// Codifica o arquivo usando a tabela de codificação

char *codificarArquivo(char **tabela, unsigned char *listaBytes, long int tamListaBytes, long int *tamSaida)
{
    // Calcula o tamanho do arquivo codificado usando a tabela de codificação e a lista de bytes
    unsigned long long int tam_codificado = tamCodificado(tabela, listaBytes, tamListaBytes);
    // Define o tamanho da saída como o tamanho do arquivo codificado
    *tamSaida = tam_codificado;

    // Aloca memória para o arquivo codificado
    char *arquivoCodificado = calloc(tam_codificado, sizeof(char));
    // Ponteiro auxiliar para percorrer o arquivo codificado
    char *aux = arquivoCodificado;

    // Itera sobre a lista de bytes
    for (int i = 0; i < tamListaBytes; i++)
    {
        // Copia a codificação do byte atual para o arquivo codificado
        strcpy(aux, tabela[listaBytes[i]]);
        // Avança o ponteiro auxiliar pelo comprimento da codificação copiada
        aux += strlen(tabela[listaBytes[i]]);
    }

    // Retorna o arquivo codificado
    return arquivoCodificado;
}

// Salva o arquivo compactado no formato .huff

int salvarCompactado(long int tamCodificado, unsigned char bytesArvore[], char *arquivoCodificado, int tamArvore, char caminhoArquivo[])
{
    ////////////////////

    unsigned char *extensaoArquivo = strrchr(caminhoArquivo, '.') + 1; // Tira o ponto da extensão
    printf("Extensão Original do Arquivo: %s\n", extensaoArquivo);

    int tamExtensao = strlen(extensaoArquivo); // sem o ponto
    printf("Tamanho da Extensão Original do Arquivo: %d\n", tamExtensao);

    int tamanhoCaminhoArquivoSemExtensao = (strlen(caminhoArquivo) - tamExtensao) - 1; // Sem o ponto
    printf("Tamanho do caminhoArquivo sem extensão: %d\n", tamanhoCaminhoArquivoSemExtensao);

    int tamanhoCaminhoCompactado = tamanhoCaminhoArquivoSemExtensao + 5; // .huff

    char caminhoCompactado[tamanhoCaminhoCompactado + 1]; // +1 string

    caminhoCompactado[0] = '\0'; 

    strncat(caminhoCompactado, caminhoArquivo, tamanhoCaminhoArquivoSemExtensao);

    strcat(caminhoCompactado, ".huff");

    ////////////

    // Abre o arquivo no modo de escrita binária
    FILE *f = fopen(caminhoCompactado, "wb");
    // Verifica se o arquivo foi criado com sucesso
    if (f == NULL)
    {
        // Se não, imprime uma mensagem de erro e retorna 1
        printf("Erro ao criar o arquivo compactado.\n");
        return 1;
    }

    // Calcula o tamanho total dos dados codificados em bits, arredondado para o byte mais próximo
    int tamTotal = (tamCodificado - (tamCodificado % 8)) + 8;
    // Calcula o número de bits de preenchimento (lixo)
    unsigned short lixo = tamTotal - tamCodificado;
    
    // Inicializa o cabeçalho como 0
    unsigned short cabecalho = 0;

    // Escrever o tamanho da arvore no cabecalho
    cabecalho = tamArvore & 0b0001111111111111;

    // Escrever o tamanho do lixo no cabecalho
    cabecalho = cabecalho | (lixo << 13);

    // Escreve o cabeçalho no arquivo
    fwrite(&cabecalho, sizeof(unsigned short), 1, f);

    // Escreve os bytes da árvore no arquivo
    for (int i = 0; i < tamArvore; i++)
        fwrite(&bytesArvore[i], sizeof(unsigned char), 1, f);

    ////////////// tam da extensao

    unsigned char byteTamExtensao = (unsigned char) tamExtensao << 5;
    fwrite(&byteTamExtensao, sizeof(unsigned char), 1, f);

    printf("\nTamanho da extensao em binario: ");
    for (int i = 7; i >= 0; i--)
    {
        if ((byteTamExtensao >> i) & 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }
    printf("\n");


    // adicao da extensao
    
    int qnt = fwrite(extensaoArquivo, sizeof(unsigned char), tamExtensao, f);
    printf("Tamanho da extensao: %d\n", qnt);

    /////

    unsigned char byte = 0;
    int j = 7;

    // Escreve o arquivo codificado bit a bit
    for (int i = 0; i < tamCodificado; i++)
    {
        if(arquivoCodificado[i] == '1')
            byte = byte | (1 << j);
        
        j--;

        if(j < 0)
        {
            j = 7;
            fwrite(&byte, sizeof(unsigned char), 1, f);
            byte = 0;
        }
    }
    // Se ainda houver bits não escritos, escreve o último byte
    if(j != 7)
        fwrite(&byte, sizeof(unsigned char), 1, f);

    // Fecha o arquivo
    fclose(f);
    return 1;
}