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
 *  @description : ����ն�����T
 *  @param       : �����������T
 */
Status InitBiTree(BiTree *T)
{
    *T = NULL;
    return SUCCESS;
}


/**
 *  @name        : Status DestroyBiTree(BiTree T);
 *  @description : �ݻٶ�����T
 *  @param       : �����������T
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
 *  @description : ���������T
 *  @param       : �����������T, ��������������ַ���definition
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
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
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
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
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
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
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
 *  @description : �������������T
 *  @param       : �����������T, �Խ��Ĳ�������visit
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
 *  @description : �Թ������ǰ׺���ʽ��������ֵ
 *  @param       : �����������T
 *  @note        : ���ڽ��ṹ�������ø�Tagֵ��־������������������������
 *                 �ɸ�����Ҫ�������Ӳ���.
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
