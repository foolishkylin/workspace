#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

typedef struct Node{
	BiTree date;
	struct Node *next;
} Queue;

extern int isNum(char c);
extern int isNum(char c);
extern Status Traverse(TElemType a);
double cal(double a, double b, char c);
extern int make_num(char a);
extern void error(void);
extern int IsEmpty(Queue *Q);
extern BiTree DeQueue(Queue *Q);
extern void EnQueue(Queue *Q, BiTree Element);
void reset(void);

int expression_error_copy = 0;
int pos = 0;
/**
 *  @name        : Status InitBiTree(BiTree T);
 *  @description : 构造空二叉树T
 *  @param       : 二叉树根结点T
 */
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return SUCCESS;
}


/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : 摧毁二叉树T
 *  @param       : 二叉树根结点T
 */
Status DestroyBiTree(BiTree T)
{
    if (T != NULL)
    {
        DestroyBiTree(T->lchild);
        DestroyBiTree(T->rchild);
        free(T);
    }
    return SUCCESS;
}


/**
 *  @name        : Status CreateBiTree(BiTree T, char* definition);
 *  @description : 构造二叉树T
 *  @param       : 二叉树根结点T, 二叉树先序遍历字符串definition
 */
Status CreateBiTree(BiTree *T, char* definition)
{
    while (definition[pos] == ' ')
        pos++;
    char x = definition[pos++];

    if (x == 0) error();
    *T = (BiTree) malloc (sizeof(BiTNode));
    (*T)->data = x;
    (*T)->lchild = (*T)->rchild = NULL;

    if (!isNum(x))
    {
        if (!(x == '+' || x == '-' || x == '*' || x == '/'))
        {
            error();
            return ERROR;
        }
        CreateBiTree(&((*T)->lchild), definition);
        CreateBiTree(&((*T)->rchild), definition);
    }

    return SUCCESS;
}


/**
 *  @name        : Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : 先序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status PreOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        visit(T->data);
        PreOrderTraverse(T->lchild, visit);
        PreOrderTraverse(T->rchild, visit);
    }
    return SUCCESS;
}


/**
 *  @name        : Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : 中序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status InOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        InOrderTraverse(T->lchild, visit);
        visit(T->data);
        InOrderTraverse(T->rchild, visit);
    }
    return SUCCESS;
}


/**
 *  @name        : Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e)));
 *  @description : 后序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status PostOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    if (T)
    {
        PostOrderTraverse(T->lchild, visit);
        PostOrderTraverse(T->rchild, visit);
        visit(T->data);
    }
    return SUCCESS;
}


/**
 *  @name        : Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e));
 *  @description : 层序遍历二叉树T
 *  @param       : 二叉树根结点T, 对结点的操作函数visit
 */
Status LevelOrderTraverse(BiTree T, Status (*visit)(TElemType e))
{
    Queue Q;
	Q.next = 0;
    if (T)
    {
        visit(T->data);
        EnQueue(&Q, T);
    }
    while(!IsEmpty(&Q))
    {
        T = DeQueue(&Q);
        if (T->lchild)
        {
            visit(T->lchild->data);
            EnQueue(&Q, T->lchild);
        }
        if (T->rchild)
        {
            visit(T->rchild->data);
            EnQueue(&Q, T->rchild);
        }
    }
}


/**
 *  @name        : int Value(BiTree T);
 *  @description : 对构造出的前缀表达式二叉树求值
 *  @param       : 二叉树根结点T
 *  @note        : 可在结点结构体中设置个Tag值标志数字与操作符来构造二叉树，
 *                 可根据需要自行增加操作.
 */
double Value(BiTree T)
{
    if (!T)
    {
        error();
        expression_error_copy = 1;
        return 0;
    }
    if(expression_error_copy)
        return 0;

    if (isNum(T->data))
        return make_num(T->data);
    else
        return cal(Value(T->lchild), Value(T->rchild), T->data);
}

/**
 *  @name        : void reset(void)
 *  @description : reset the pos
 *  @param       : none
 *  @note        : let the creating can be repeated
 */
void reset(void)
{
    pos = 0;
}
