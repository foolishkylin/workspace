#include <stdio.h>
#include <stdlib.h>
// this a AVL tree which can rotate to make the tree more efficent
// AVL树与普通二叉树的区别在于新增了高度属性（便于检查是否平衡）和旋转函数
// 双旋转基于单旋转，若有所遗忘，可以查阅书籍或视频
typedef int ElementType;
typedef struct TreeNode *AVLTree, LenthofTree;
struct TreeNode
{
    ElementType Element; // the key value
    AVLTree Left; // the ptr point to the left son
    AVLTree Right; // to right son
    int Height; //show the height of a node which can compare to chiek if the tree is balanced
};

int Max(int a, int b)
// compare and return the bigger one
{
    return a > b? a : b; 
}

int Height(AVLTree T)
// output the higher one.  if empty, return -1, which means no son
{
    if(T == NULL)
        return -1;
    else 
        return T->Height;
}

AVLTree MakeEmpty(AVLTree T)
// destory tree
{
    if(T != NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

AVLTree Find(ElementType X, AVLTree T)
// find the node whose key is X
{
    if(T == NULL)
        return NULL;
    if(X < T->Element)
        return Find(X, T->Left);
    if(X > T->Element)
        return Find(X, T->Right);
    return T;
}

AVLTree FindMax(AVLTree T)
// FindMin is the same
{
    if(T == NULL)
        return NULL;
    if(T->Right == NULL)
        return T;
    return FindMax(T->Right);
    /*anothet way
    if(T != NULL)
        while(T->Right != NULL)
            T = T->next;
    return T;
    */
}

AVLTree SingleRotateWithLeft(AVLTree T)
// deal with the LL case
{
    AVLTree N; 

    N = T->Left; 
    // N is T's Lson
    T->Left = N->Right;
    // let T's Lson(N) become T's Lson's R'son(LRgrandson) because the key of LRgrandson is bewteen N and T
    N->Right = T; 
    // let T become N's Rson
    N->Height = Max(Height(N->Left), Height(N->Right)) + 1;
    // reset the height
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

    return N; 
}

AVLTree SingleRotateWithRight(AVLTree T)
// deal with the RRcase
{
    AVLTree N; 

    N = T->Right; 
    T->Right = N->Left; 
    N->Left = T; 
    N->Height = Max(Height(N->Left), Height(N->Right)) + 1;
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;

    return N; 
}

AVLTree DoubleRotateWithLeft(AVLTree T)
// deal with the LR case
{
    T->Left = SingleRotateWithRight(T->Left);
    // make the case become LL
    
    return SingleRotateWithLeft(T);
}

AVLTree DoubleRotateWithRight(AVLTree T)
// deal with the RL case
{
    T->Left = SingleRotateWithLeft(T->Left);
    // make the case become RR
    
    return SingleRotateWithRight(T);
}

AVLTree Insert(ElementType X, AVLTree T)
{
    if(T == NULL)
    {
        // creat a new treenode
        T = (AVLTree) malloc(sizeof(LenthofTree));
        if(T == NULL)
            puts("out of space");
        else
        {
            T->Element = X;
            T->Height = 0; 
            // when comparing, height(T->L/R)==0 means it has 1 son and 1 means 2 son, and -1 means none
            // this kind of expression can let the height of a node be a true value
            // if let a new treenode's height equals 1 and set the emptynode' height equal 0, when comparing 
            // it can show a true height of a tree's bunches, but the height of a node will be wrong
            T->Left = T->Right = NULL;
        }
    }
    else if(X > T->Element)
    // if the tree isn't balanced, the case includes LL, RR, LR, RL. the LL and RR are easy and it just need change once
    // but the LR and RL are complex and it takes twice. 
    {
        T->Right = Insert(X, T->Right);
        if(Height(T->Right) - Height(T->Left) == 2)
        // if not balanced
        if(X > T->Element)
            T = SingleRotateWithRight(T);// RR
        else
            T = DoubleRotateWithRight(T);//RL
    }
    else if(X < T->Element)
    {
        T->Left = Insert(X, T->Left);
        if(Height(T->Left) - Height(T->Right) == 2)
            if(X < T->Element)
                T = SingleRotateWithLeft(T);// LL
            else
                T = DoubleRotateWithLeft(T);// LR
    }
    T->Height = Max(Height(T->Left), Height(T->Right)) + 1;
    //reset the height

    // if X == T->Element, we don't need to do anything
     return T; 
}

void Print(AVLTree T, int Depth)
{
    int PrintTimes;
    if(T == NULL)
        return ;
    Print(T->Left, Depth+1);
    for(PrintTimes = 0; PrintTimes < Depth; PrintTimes++)
        printf("            ");
    printf("%d ( %d ) \n",T->Element, T->Height);
    Print(T->Right, Depth+1);

    return ;
}

int main()
{
    ElementType date;
    AVLTree T = NULL;

    scanf("%d",&date);
    while(date){
        T = Insert(date, T);
        // it is extremely important to update T, if not, the result must be wrong
        scanf("%d",&date);
    }
    Print(T, 1);
    puts("the max node is");
    T = FindMax(T);
    printf("%d\n", T->Element);
    MakeEmpty(T);
    puts("now the tree is deleted");
    getchar();
    getchar();
    getchar();
    getchar();

    return 0;
}