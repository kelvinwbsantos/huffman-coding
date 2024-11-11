#include "fila.h"
#include "codificacao.h"

long int tamArquivo(FILE *f)
{
    long int tam;

    fseek(f, 0, SEEK_END); // Move o ponteiro do arquivo para o final
    tam = ftell(f);        // Obtém a posição atual do ponteiro, que é o tamanho do arquivo
    rewind(f);             // Volta o ponteiro do arquivo para o início

    return tam;
}

void calcularFrequencia(FILE *f, unsigned char *listaBytes, int *frequencia)
{
    // Variável para armazenar o byte lido do arquivo
    int byte;
    
    // Variável para contar a posição no array listaBytes
    long int i = 0;
    
    // Loop para ler cada byte do arquivo até o final (EOF)
    while ((byte = fgetc(f)) != EOF)
    {
        // Incrementa a frequência do byte lido
        frequencia[byte]++;
        
        // Armazena o byte lido na lista de bytes
        listaBytes[i] = byte;
        
        // Incrementa o índice para a próxima posição na lista de bytes
        i++;
    }
    
    // Marca o final da lista de bytes com o caractere nulo
    listaBytes[i] = '\0';
}

void enfileirarBytes(Queue *fila, int *frequencia)
{
    for (int j = 0; j < 256; j++)
    {
        if (frequencia[j] != 0)
        {
            enqueue(fila, j, frequencia[j]);
        }
    }
}

int compactarArquivo(const char *caminhoArquivo)
{

    // Abre o arquivo no caminho especificado // Ponteiro para o arquivo a ser compactado
    FILE *f = fopen(caminhoArquivo, "rb");

    // Vetor para armazenar a frequência de cada byte no arquivo
    int frequencia[256] = {0};

    // Obtém o tamanho do arquivo
    long int tam_arquivo = tamArquivo(f);

    // Aloca memória para armazenar os bytes do arquivo
    unsigned char *listaBytes = malloc(tam_arquivo * sizeof(unsigned char));

    // Calcula a frequência de cada byte no arquivo e faz uma copia dos bytes para *listaBytes
    calcularFrequencia(f, listaBytes, frequencia);

    // Cria uma fila para armazenar os nós da árvore de Huffman
    Queue *fila = createQueue();

    // Enfileira os bytes na fila com base na frequência
    enfileirarBytes(fila, frequencia);

    // Cria a árvore de Huffman a partir da fila
    Node *arvore = criarArvoreHuffman(fila->head);

    char **tabela; // Tabela de códigos de Huffman

    // Calcula o número de colunas da tabela de códigos de Huffman
    int colunas = height(arvore);

    // Aloca memória para a tabela de códigos de Huffman
    tabela = alocarMapa(colunas);

    int nos = 0; // Contador de nós da árvore

    // Cria a tabela de códigos de Huffman
    criarMapa(tabela, arvore, "", colunas, &nos);

    // Vetor para armazenar a árvore de Huffman em pré-ordem
    unsigned char bytesArvore[nos];

    int tamArvore = 0; // Tamanho da árvore em bytes
    int k = 0; // Índice auxiliar

    // Salva a árvore de Huffman em pré-ordem no vetor bytesArvore
    salvarArvorePreOrdem(arvore, bytesArvore, &k, &tamArvore);

    char *arquivoCodificado; // String que armazenará o arquivo codificado
    long int tamCodificado; // Tamanho do arquivo codificado
    // Codifica o arquivo usando a tabela de códigos de Huffman
    arquivoCodificado = codificarArquivo(tabela, listaBytes, tam_arquivo, &tamCodificado);
 
    // Cria uma copia do *caminhoArquivo pq ele originalmente é const
    char caminhoArquivoCompactado[strlen(caminhoArquivo)];
    caminhoArquivoCompactado[0] = '\0'; 
    printf("caminhoArquivo: %s\n", caminhoArquivo);
    strcat(caminhoArquivoCompactado, caminhoArquivo);

    // Salva o arquivo compactado
    salvarCompactado(tamCodificado, bytesArvore, arquivoCodificado, tamArvore, caminhoArquivoCompactado);

    // Libera a memória alocada
    free(listaBytes);
    free(arquivoCodificado);
    free(fila);
    free(arvore);
    free(tabela);

    // Reposiciona o ponteiro do arquivo para o início
    rewind(f);
    // Fecha o arquivo
    fclose(f);
    
    return 0;
}

int descompactarArquivo(const char *caminhoArquivoHuff)
{
    FILE *f; // Ponteiro para o arquivo a ser descompactado
    
    // Abre o arquivo em modo binário
    f = fopen(caminhoArquivoHuff, "rb");
    if (f == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int tamExtensaoCompactado = 5; // ".huff"

    // Obtém o tamanho do arquivo
    long int tam_arquivo = tamArquivo(f);

    unsigned short cabecalho; // Cabeçalho do arquivo compactado
    unsigned short lixo = 0; // Quantidade de bits de lixo no final do arquivo
    unsigned short tamArvore = 0; // Tamanho da árvore de Huffman em bytes

    // Lê o cabeçalho do arquivo
    fread(&cabecalho, sizeof(unsigned short), 1, f);

    lixo = cabecalho >> (16 - 3);

    tamArvore = cabecalho & 0b0001111111111111;

    // Vetor para armazenar a árvore de Huffman
    unsigned char arvore[tamArvore];

    // Lê a árvore de Huffman do arquivo
    fread(&arvore, sizeof(unsigned char), tamArvore, f);

    // Índice auxiliar
    int h = 0;

    // Reconstrói a árvore de Huffman
    Node *arvoreHuffman = refazerArvore(arvore, tamArvore, &h, NULL);
    Node *aux = arvoreHuffman;

    
    // Extrai o tamanho da extensao original
    unsigned char tamExtensaoArquivo; 
    fread(&tamExtensaoArquivo, sizeof(unsigned char), 1, f);

    printf("Tamanho Extensão Original no Cabeçalho: ");

    for (int i = 7; i >= 0; i--)
    {
        // Verifica se o bit atual é 1 ou 0
        if ((tamExtensaoArquivo >> i) & 1)
        {
            printf("1");
        }
        else
        {
            printf("0");
        }
    }

    printf("\n");

    tamExtensaoArquivo = tamExtensaoArquivo >> 5;

    printf("Tamanho Extensão Original no Cabeçalho Convertido: %d\n", tamExtensaoArquivo);

    
    if (tamExtensaoArquivo > 6)
    {
        printf("\033[31mNao e possivel, tamanho da extensao do arquivo original maior que 6.\033[0m\n");
        return 1;
    }

    // Extrai a extensao original
    unsigned char extensaoArquivo[tamExtensaoArquivo + 1];
    fread(extensaoArquivo, sizeof(unsigned char), tamExtensaoArquivo, f);
    extensaoArquivo[tamExtensaoArquivo] = '\0';

    printf("Extensão do Arquivo Original: ");

    for (int i = 0 ; i < tamExtensaoArquivo; i++)
    {
        printf("%c", extensaoArquivo[i]);
    }

    printf("\n");


    // Cria o nome do arquivo descompactado
    int tamCaminhoDescompactado = (int) strlen(caminhoArquivoHuff) - tamExtensaoCompactado + tamExtensaoArquivo + 1; // spongebob.huff - 5 + jpg + 1
    char caminhoDescompactado[tamCaminhoDescompactado + 1]; // \0
    caminhoDescompactado[0] = '\0';

    strncat(caminhoDescompactado, caminhoArquivoHuff, (strlen(caminhoArquivoHuff) - tamExtensaoCompactado)); 
    strcat(caminhoDescompactado, ".");
    strcat(caminhoDescompactado, extensaoArquivo);
    printf("Caminho original: %s\n", caminhoDescompactado);
    strcat(caminhoDescompactado, "\0");

    // Cria o arquivo descompactado
    FILE *arquivoDescompactado = fopen(caminhoDescompactado, "wb");
    if (arquivoDescompactado == NULL)
    {
        printf("Erro ao criar o arquivo descompactado.\n");
        return 1;
    }

    unsigned char byte; // Byte lido do arquivo compactado
    int i; // Índice auxiliar
    int nBitsLidos = 0; // Número de bits lidos

    // Lê o arquivo compactado e escreve o conteúdo descompactado no novo arquivo
    while (fread(&byte, sizeof(unsigned char), 1, f) != EOF)
    {
        long int posicaoArquivo = ftell(f);

        for (i = 7; i >= 0; i--)
        {
            if (byte & (1 << i))
                aux = aux->right;
            else
                aux = aux->left;

            nBitsLidos++;

            if (aux->left == NULL && aux->right == NULL)
            {
                unsigned char *item = (unsigned char *)malloc(sizeof(unsigned char));
                item = (unsigned char *)aux->item;
                
                fwrite(item, sizeof(unsigned char), 1, arquivoDescompactado);
                aux = arvoreHuffman;
            }
            
            if (posicaoArquivo == tam_arquivo)
                break;

        }
        if (posicaoArquivo == tam_arquivo)
                break;
    }
    // Fecha os arquivos
    fclose(f);
    fclose(arquivoDescompactado);
    return 0;
}