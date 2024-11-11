#include "arvoreHuffman.h"

// Verifica se a lista está vazia

int isEmptyList(Node *head)
{
    return head == NULL;
}

// Retorna o maior valor entre a e b

int max(int a, int b)
{
    return (a > b) ? a : b;
}

// Cria a árvore de Huffman a partir da fila de nós

Node *criarArvoreHuffman(Node *fila)
{
    while (fila->next != NULL)
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->frequency = malloc(sizeof(int));

        // Soma as frequências dos dois primeiros nós da fila
        *(int *)newNode->frequency = *(int *)fila->frequency + *(int *)fila->next->frequency;

        newNode->left = fila; // Define o filho esquerdo
        newNode->right = fila->next; // Define o filho direito

        unsigned char *itemPtr = (unsigned char *)malloc(sizeof(unsigned char));
        *itemPtr = '\\'; // Caractere especial para nós internos;
        newNode->item = (void *)itemPtr;
        free(itemPtr);

        fila = fila->next->next; // Avança na fila
        newNode->left->next = NULL;
        newNode->right->next = NULL;

        // Insere o novo nó na posição correta na fila
        if (isEmptyList(fila) || *(int *)newNode->frequency <= *(int *)fila->frequency)
        {
            newNode->next = fila;
            fila = newNode;
        }
        else
        {
            Node *current = fila;
            while (current->next != NULL && *(int *)current->next->frequency < *(int *)newNode->frequency)
                current = current->next;
            newNode->next = current->next;
            current->next = newNode;
        }
    }
    return fila;
}

// Calcula a altura da árvore

int height(Node *arvore)
{
    if (arvore == NULL)
        return -1;
    else
        return 1 + max(height(arvore->left), height(arvore->right));
}

// Salva a árvore em pré-ordem em um array

void salvarArvorePreOrdem(Node *arvore, unsigned char arr[], int *i, int *tamArvore)
{
    if (!isEmptyList(arvore))
    {
        unsigned char c = *(unsigned char *)arvore->item;
        if (arvore->left == NULL && arvore->right == NULL)
        {
            if (c == '*' || c == '\\')
            {
                arr[*i] = '\\'; // Adiciona caractere de escape
                (*i)++;
                (*tamArvore)++;
            }
            arr[*i] = c;
        }
        else
            arr[*i] = '*'; // Nó interno

        (*i)++;
        (*tamArvore)++;
        
        salvarArvorePreOrdem(arvore->left, arr, i, tamArvore);
        salvarArvorePreOrdem(arvore->right, arr, i, tamArvore);
    }
}

// Reconstrói a árvore a partir de uma string em pré-ordem
Node *refazerArvore(unsigned char str[], int n, int *i, Node *arvore)
{
    if (*i < n)
    {
        unsigned char *item = (unsigned char *)malloc(sizeof(unsigned char));
        *item = str[*i];
        (*i)++;

        if (*item == '*')
        {
            arvore = (Node *)malloc(sizeof(Node));
            arvore->item = item;
            arvore->left = NULL;
            arvore->right = NULL;
            arvore->left = refazerArvore(str, n, i, arvore->left);
            arvore->right = refazerArvore(str, n, i, arvore->right);
        }
        else
        {
            if (*item == '\\')
            {
                *item = str[*i];
                (*i)++;
            }

            arvore = (Node *)malloc(sizeof(Node));
            arvore->item = item;
            arvore->left = NULL;
            arvore->right = NULL;
        }
    }
    return arvore;
}