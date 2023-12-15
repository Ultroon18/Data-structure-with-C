#include<stdio.h>
#include<stdio_ext.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

#define NUMPARAMS 2
#define N 15

typedef struct tree
{
    int data;
    struct tree *left;
    struct tree *right;
}Tree;

void randomInteger(int *num);
int *initVector();
bool searchInVector(int *vector, int *num, int pos);
void fillVector(int *vector);
void printVector(int *vector);
void insertData(int *num);
Tree *createNode(int *num);
int treeEmpty(Tree **tree);
void insertNode(Tree **tree, int *num);
Tree *createTree();
bool searchNode(Tree **tree, int *num);
void findNode(Tree **tree);
int cleanInput();

int main()
{
    Tree *tree = NULL;
    tree = createTree();
    findNode(&tree);
    printf("\n\n");
    free(tree);
    return 0;
}

void randomInteger(int *num)
{
    srand(time(NULL));
    *num = rand() % 100;
}

int *initVector()
{
    int *vector = (int *)calloc(N, sizeof(int));
    if(vector == NULL)
    {
        printf("\nNo se puede asignar memoria.\n\n");
        exit(1);
    }
    return vector;
}

bool searchInVector(int *vector, int *num, int pos)
{
    for(register int j = 0; j < pos; j++)
        if(vector[j] == *num)
            return true;
    return false;
}

void fillVector(int *vector)
{
    int num = 0;
    for(register int i = 0; i < N; i++)
    {
        do
        {
            randomInteger(&num);
            if(i == 0)
                break;
        } while(searchInVector(vector, &num, i));
        vector[i] = num;
    }
}

void printVector(int *vector)
{
    printf("\n\n");
    for(register int i = 0; i < N; i++)
        printf("\t%d", vector[i]);
    printf("\n\n");
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

Tree *createNode(int *num)
{
    Tree *tree = (Tree *)malloc(sizeof(Tree));
    if(tree == NULL)
    {
        printf("\nNo se puede asignar memoria\n\n");
        exit(1);
    }
    tree -> data = *num;
    tree -> left = NULL;
    tree -> right = NULL;
    return tree;
}

int treeEmpty(Tree **tree)
{
    return *tree == NULL;
}

void insertNode(Tree **tree, int *num)
{
    if(!treeEmpty(&(*tree)) && *num < (*tree) -> data)
        insertNode(&((*tree) -> left), &(*num));
    else if(!treeEmpty(&(*tree)) && *num > (*tree) -> data)
        insertNode(&((*tree) -> right), &(*num));
    else
        *tree = createNode(&(*num));
}

Tree *createTree()
{
    int *vector = initVector();
    Tree *tree = NULL;
    fillVector(vector);
    printVector(vector);
    for(register int i = 0; i < N; i++)
        insertNode(&tree, &vector[i]);
    return tree;
}

bool searchNode(Tree **tree, int *num)
{
    if(*tree != NULL)
    {
        if(*num == (*tree) -> data)
            return true;
        else if(*num < (*tree) -> data)
            searchNode(&((*tree) -> left), &(*num));
        else if(*num > (*tree) -> data)
            searchNode(&((*tree) -> right), &(*num));
        else
            return false;
    }
}

void findNode(Tree **tree)
{
    int num = 0;
    if(!treeEmpty(&(*tree)))
    {
        insertData(&num);
        if(!searchNode(&(*tree), &num))
            printf("\n\nnum = %d no se encuentra en el arbol.", num);
        else
            printf("\n\nnum = %d se encuentra en el arbol.", num); 
    }
    else
        printf("\nEl arbol no se ha creado.");
}

int cleanInput()
{
    __fpurge(stdin);
    return 0;
}
