#include "fila.h"

Queue *createQueue()
{
    Queue *fila = (Queue *)malloc(sizeof(Queue));
    fila->head = NULL;
    return fila;
}

int isEmpty(Queue *fila)
{
    return fila->head == NULL;
}

void enqueue(Queue *fila, unsigned char item, int frequency)
{
    // Cria um novo nó e aloca memória para ele
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->item = malloc(sizeof(unsigned char));
    newNode->frequency = malloc(sizeof(int));
    
    // Atribui os valores do item e da frequência ao novo nó
    *(unsigned char *)newNode->item = item;
    *(int *)newNode->frequency = frequency;
    
    // Inicializa os ponteiros left e right do novo nó como NULL
    newNode->left = NULL;
    newNode->right = NULL;

    // Se a fila estiver vazia ou a frequência do novo nó for menor ou igual à frequência do nó na cabeça da fila
    if (isEmpty(fila) || frequency <= *(int *)fila->head->frequency)
    {
        // Insere o novo nó na cabeça da fila
        newNode->next = fila->head;
        fila->head = newNode;
    }
    else
    {
        // Caso contrário, percorre a fila para encontrar a posição correta para inserir o novo nó
        Node *current = fila->head;
        while (current->next != NULL && *(int *)current->next->frequency < frequency)
            current = current->next;
            
        // Insere o novo nó na posição correta
        newNode->next = current->next;
        current->next = newNode;
    }
}