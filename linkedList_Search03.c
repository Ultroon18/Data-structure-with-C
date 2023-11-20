#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define NUMPARAMS 2
#define N 10

typedef struct nodo
{
    int data;
    struct nodo *next;
} Nodo;

void randomInteger(int *num);
Nodo *createNewNode(int *num);
int listEmpty(Nodo **list);
void insertHead(Nodo **list, Nodo **newNode);
void insertAfterHead(Nodo **list, Nodo **newNode);
bool searchNode(Nodo **list, int *num);
bool insertNode(Nodo **list, int *num);
Nodo *createList();
int searchPosition(Nodo **list, int *num);
void insertData(int *num);
void findNode(Nodo **list);
int printList(Nodo **list);
int cleanInput();

int main()
{
    Nodo *list = NULL;
    list = createList();
    printList(&list);
    findNode(&list);
    free(list);
    return 0;
}

void randomInteger(int *num)
{
    srand(time(NULL));
    *num = rand() % 100;
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

int listEmpty(Nodo **list)
{
    return *list == NULL;
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
        previousNode = previousNode ->next;
    previousNode -> next = *newNode;
}

bool searchNode(Nodo **list, int *num)
{
    Nodo *currentNode = *list;
    while(currentNode != NULL)
    {
        if(currentNode -> data == *num)
            return true;
        currentNode = currentNode -> next;
    }
    return false;
}

bool insertNode(Nodo **list, int *num)
{
    Nodo *newNode = createNewNode(&(*num));
    if(!listEmpty(&(*list)))
    {
        if(!searchNode(&(*list), &(*num)))
        {
            insertAfterHead(&(*list), &newNode);
            return true;
        }
        else
            free(newNode);
    }
    else
    {
        insertHead(&(*list), &newNode);
        return true;
    }
    return false;
}

Nodo *createList()
{
    int num = 0;
    Nodo *list = NULL;
    printf("\n");
    for(register int i = 0; i < N; i++)
    {
        do
            randomInteger(&num);
        while(!insertNode(&list, &num));
    }
    return list;
}

int searchPosition(Nodo **list, int *num)
{
    register int pos = 0;
    Nodo *currentNode = *list;
    while(currentNode != NULL)
    {
        if(currentNode -> data == *num)
            return pos;
        pos++;
        currentNode = currentNode -> next;
    }
    return pos;
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

void findNode(Nodo **list)
{
    int num = 0;
    register int pos = 0;
    printf("\nIngresa el dato a buscar.\n");
    insertData(&num);
    if(!searchNode(&(*list), &num))
        printf("\nnum = %d no se encuentra en la lista.\n\n", num);
    else
    {
        pos = searchPosition(&(*list), &num) + 1;
        printf("\nnum = %d se encuentra en el nodo #%d de la lista.\n\n", num, pos);
    }
}

int printList(Nodo **list)
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
