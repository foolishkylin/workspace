#include <stdio.h>
#include <stdlib.h>
// binary search tree while don't allow the same node
// the nodes are just simple intergers
typedef int ElementType;
typedef struct TreeNode *SearchTree, LenthofTree;
struct TreeNode
{
    ElementType Element;
    SearchTree left;
    SearchTree right;
};

SearchTree MakeEmpty(SearchTree T)
// destory tree
{
    if(T != NULL)
    {
        MakeEmpty(T->left);
        MakeEmpty(T->right);
        free(T);
    }
    return NULL;
}

SearchTree Find(ElementType X, SearchTree T)
{
    if(T == NULL)
        return NULL;
    if(X < T->Element)
        return Find(X, T->left);
    if(X > T->Element)
        return Find(X, T->right);
    return T;
}

SearchTree FindMax(SearchTree T)
// FindMin is the same
{
    if(T == NULL)
        return NULL;
    if(T->right == NULL)
        return T;
    return FindMax(T->right);
    /*anothet way
    if(T != NULL)
        while(T->right != NULL)
            T = T->next;
    return T;
    */
}

SearchTree Insert(ElementType X, SearchTree T)
{
    if(T == NULL)
    {
        // creat a new treenode
        T = (SearchTree) malloc(sizeof(LenthofTree));
        if(T == NULL)
            puts("out of space");
        else
        {
            T->Element = X;
            T->left = T->right = NULL;
        }
    }
    else if(X > T->Element)
        T->right = Insert(X, T->right);
    else if(X < T->Element)
        T->left = Insert(X, T->left);
    // printf("%d\n",T->Element);
    // if X == T->Element, we don't need to do anything
     return T; 
}

void Print(SearchTree T, int Depth)
{
    int PrintTimes;
    if(T == NULL)
        return ;
    Print(T->left, Depth+1);
    for(PrintTimes = 0; PrintTimes < Depth; PrintTimes++)
        printf("      ");
    printf("%d\n",T->Element);
    Print(T->right, Depth+1);

    return ;
}

int main()
{
    ElementType date;
    SearchTree T = NULL;

    scanf("%d",&date);
    while(date){
        T = Insert(date, T);
        // it is extremely important to update T, if not, the result will be wrong
        scanf("%d",&date);
    }
    // printf("%d\n",T->Element);
    Print(T, 1);
    puts("this is the max node ");
    T = FindMax(T);
    printf("%d\n", T->Element);
    MakeEmpty(T);
    puts("now it is deleted");
    // Print(T, 4);
    getchar();
    getchar();
    getchar();
    getchar();

    return 0;
}