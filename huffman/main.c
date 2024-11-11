#include "fila.h"
#include "codificacao.h"
#include "bytes.h"
#include "arvoreHuffman.h"

int main(int argc, const char *argv[])
{
    if (argc < 2)
    {
        printf("Uso: %s <arquivo>\n", argv[0]);
        return 1;
    }

    if (strstr(argv[1], ".huff") != NULL)
    {
        descompactarArquivo(argv[1]);
        printf("\nArquivo %s descompactado com sucesso.\n", argv[1]);
    }
    else
    {
        compactarArquivo(argv[1]);
        printf("\nArquivo %s compactado com sucesso.\n", argv[1]);
    }

    return 0;
}