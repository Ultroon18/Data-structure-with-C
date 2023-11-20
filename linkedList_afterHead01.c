#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>

#define NUMPARAMS 2
#define N 10

typedef struct nodo
{
    int data;
    struct nodo *next;
}Nodo;

void insertData(int *num);
Nodo *createNewNode(int *num);
void insertHead(Nodo **list, Nodo **newNode);
void insertAfterHead(Nodo **list, Nodo **newNode);
Nodo *createList();
void printList(Nodo **list);
int cleanInput();

int main()
{
    Nodo *list = NULL;
    list = createList();
    printList(&list);
    free(list);
    return 0;
}

void insertData(int *num)
{
    char c;
    printf("num: ");
    while(!(scanf("%d%c", num, &c) == NUMPARAMS && c == '\n'))
    {
        printf("\nIngrese solo numeros enteros.\n");
        printf("num: ");
        cleanInput();
    } 
}

Nodo *createNewNode(int *num)
{
    Nodo *newNode = (Nodo *)malloc(sizeof(Nodo));
    if(newNode == NULL)
    {
        printf("\nNo se puede asignar memoria.\n\n");
        exit(1);
    }
    newNode -> data = *num;
    newNode -> next = NULL;
    return newNode;
}

void insertHead(Nodo **list, Nodo **newNode)
{
    (*newNode) -> next = *list;
    *list = *newNode;
}

void insertAfterHead(Nodo **list, Nodo **newNode)
{
    Nodo *previousNode = *list;
    while(previousNode -> next != NULL)
        previousNode = previousNode -> next;
    previousNode -> next = *newNode;
}

Nodo *createList()
{
    int num = 0;
    Nodo *list = NULL;
    printf("\n");
    for(register int i = 0; i < N; i++)
    {
        insertData(&num);
        Nodo *newNode = createNewNode(&num);
        if(i == 0)
            insertHead(&list, &newNode);
        else
            insertAfterHead(&list, &newNode);
    }
    return list;
}


void printList(Nodo **list)
{
    Nodo *currentNode = *list;
    printf("\n[");
    while(currentNode != NULL)
    {
        printf("\t%d", currentNode -> data);
        currentNode = currentNode -> next;
    }
    printf("\t]\n\n");
    free(currentNode);
}

int cleanInput()
{
    __fpurge(stdin);
    return 0;
}
