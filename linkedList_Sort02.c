#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

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
void sortList(Nodo **list);
void printList(Nodo **list);

int main()
{
    Nodo *list = NULL;
    list = createList();
    printf("\nLista original:\n");
    printList(&list);
    printf("Lista ordenada:\n");
    sortList(&list);
    printList(&list);
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

void sortList(Nodo **list)
{
    register int count = 0, temp = 0;
    Nodo *previousNode = *list, *nextNode = (*list) -> next;
    while(nextNode != NULL)
    {
        if(&previousNode == &(*list) && (*list) -> data > nextNode -> data)
        {
            previousNode -> next = nextNode -> next;
            nextNode -> next = *list;
            *list = nextNode;
            count++;
        }
        else
        {
            if(previousNode -> data > nextNode -> data)
            {
                temp = nextNode -> data;
                nextNode -> data = previousNode -> data;
                previousNode -> data = temp;
                count++;
            }
        }
        previousNode = nextNode;
        nextNode = nextNode -> next;
    }

    if(count != 0)
        sortList(&(*list));
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
