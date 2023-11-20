#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define N 10

typedef struct nodo
{
    int data;
    struct nodo *next;
}Nodo;

void randomInteger(int *num);
Nodo *createNewNode(int *num);
int listEmpty(Nodo **list);
bool searchNode(Nodo **list, int *num);
bool insertNode(Nodo **list, int *num);
Nodo *createList();
void printList(Nodo **list);

int main()
{
    Nodo *list = NULL;
    list = createList();
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

bool searchNode(Nodo **list, int *num)
{
    Nodo *currentNode = *list;
    while(currentNode != NULL)
    {
        if(currentNode -> data == *num)
            return true;
        currentNode = currentNode -> next;
    }
    free(currentNode);
    return false;
}

bool insertNode(Nodo **list, int *num)
{
    Nodo *newNode = createNewNode(&(*num));
    if(!listEmpty(&(*list)))
    {
        if(!searchNode(&(*list), &(*num)))
        {
            newNode -> next = *list;
            *list = newNode;
            return true;
        }
        else
            free(newNode);
    }
    else
    {
        newNode -> next = *list;
        *list = newNode;
        return true;
    }
    return false;
}

Nodo *createList()
{
    int num = 0;
    Nodo *newNode = NULL;
    for(register int i = 0; i < N; i++)
    {
        do
        {
            randomInteger(&num);
        } while(!insertNode(&newNode, &num));
    }
    return newNode;
}

void printList(Nodo **list)
{
    Nodo *currentNode = *list;
    printf("\n[");
    while (currentNode != NULL)
    {
        printf("\t%d", currentNode -> data);
        currentNode = currentNode -> next;
    }
    printf("\t]\n\n");
    free(currentNode);
}
