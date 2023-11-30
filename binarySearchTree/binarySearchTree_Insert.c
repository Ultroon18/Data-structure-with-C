#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

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
Tree *createNode(int *num);
int treeEmpty(Tree **tree);
void insertNode(Tree **tree, int *num);
Tree *createTree();

int main()
{
    Tree *tree = NULL;
    tree = createTree();
    if(!treeEmpty(&tree))
        printf("\nEl arbol se ha creado exitosamente.");
    else
        printf("\nEl arbol no se ha creado.");
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
