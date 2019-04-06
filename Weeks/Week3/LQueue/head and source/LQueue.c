#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LQueue.h"

extern void Print(char *str);
extern int GetSize(char type);
extern char GetType(void);

int IsTypeSelected = 0;
char Type;                          // show the type

/**
 *  @name        : void InitLQueue(LQueue *Q)
 *    @description : ��ʼ������
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void InitLQueue(LQueue *Q)
{
    if (IsTypeSelected)
    {
        Print("Now you are reset a new queue\n");
        DestoryLQueue(Q);
    }
    Type = GetType();
    IsTypeSelected = 1;
    Q->front = Q->rear = NULL;
    Q->length = 0;
}

/**
 *  @name        : void DestoryLQueue(LQueue *Q)
 *    @description : ���ٶ���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void DestoryLQueue(LQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return ;
    }
    ClearLQueue(Q);
    IsTypeSelected = 0;
}

/**
 *  @name        : Status IsEmptyLQueue(const LQueue *Q)
 *    @description : �������Ƿ�Ϊ��
 *    @param         Q ����ָ��Q
 *    @return         : ��-TRUE; δ��-FALSE
 *  @notice      : None
 */
Status IsEmptyLQueue(const LQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (Q->length == 0)
    {
        Print("The queue is empty\n");
        return TRUE;
    }
    return FALSE;
}

/**
 *  @name        : Status GetHeadLQueue(LQueue *Q, void *e)
 *    @description : �鿴��ͷԪ��
 *    @param         Q e ����ָ��Q,��������ָ��e
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ��
 */
Status GetHeadLQueue(LQueue *Q, void *e)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsEmptyLQueue(Q))
        return FALSE;
    if (Type != 'S')
        memcpy(e, Q->front->data, GetSize(Type));
    // deal the string case
    else
    {
        char *s = (char *)e;
        int len = strlen(s) + 1;
        memcpy(e, Q->front->data, len);
    }
    return TRUE;
}

/**
 *  @name        : int LengthLQueue(LQueue *Q)
 *    @description : ȷ�����г���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
int LengthLQueue(LQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return -1;
    }
    return Q->length;
}

/**
 *  @name        : Status EnLQueue(LQueue *Q, void *data)
 *    @description : ��Ӳ���
 *    @param         Q ����ָ��Q,�������ָ��data
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : �����Ƿ�Ϊ��
 */
Status EnLQueue(LQueue *Q, void *data)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if(Q->rear == NULL)
        Q->front = Q->rear = (Node *) malloc (sizeof(Node));
    else
    {
        Q->rear->next = (Node *) malloc (sizeof(Node));
        Q->rear = Q->rear->next;
    }
    Q->rear->next = NULL;

    if (Type != 'S')
    {
        Q->rear->data = malloc(GetSize(Type));
        memcpy(Q->rear->data, data, GetSize(Type));
    }
    else
    // string case
    {
        char *s = (char *)data;
        int len = strlen(s) + 1;
        Q->rear->data = malloc(len);
        memcpy(Q->rear->data, data, len);
    }
    Q->length++;
    return TRUE;
}

/**
 *  @name        : Status DeLQueue(LQueue *Q)
 *    @description : ���Ӳ���
 *    @param         Q ����ָ��Q
 *    @return         : �ɹ�-TRUE; ʧ��-FALSE
 *  @notice      : None
 */
Status DeLQueue(LQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsEmptyLQueue(Q))
        return FALSE;
    if (Q->front == NULL)
    {
        Print("ERROR\n");
        return FALSE;
    }
    Node *p = Q->front;
    Q->front = Q->front->next;
    Q->length--;
    free(p->data);
    free(p);
    return TRUE;
}

/**
 *  @name        : void ClearLQueue(AQueue *Q)
 *    @description : ��ն���
 *    @param         Q ����ָ��Q
 *  @notice      : None
 */
void ClearLQueue(LQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return ;
    }
    while (Q->front)
    {
        Q->rear = Q->front->next;
        free(Q->front->data);
        free(Q->front);
        Q->front = Q->rear;
    }
}

/**
 *  @name        : Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
 *    @description : ������������
 *    @param         Q ����ָ��Q����������ָ��foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseLQueue(const LQueue *Q, void (*foo)(void *q))
{
    if (!IsTypeSelected || IsEmptyLQueue(Q))
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    Print("");
    Node *p = Q->front;
    for(; p; p = p->next)
        foo(p->data);
    return TRUE;
}

/**
 *  @name        : void LPrint(void *q)
 *    @description : ��������
 *    @param         q ָ��q

 *  @notice      : None
 */
void LPrint(void *q)
{
    int *Icopy; float *Fcopy; char *Ccopy;
    switch (Type)
    {
        case 'I':   Icopy = (int *)q;   printf("%d->", *Icopy); break;

        case 'F':   Fcopy = (float *)q; printf("%.2f->", *Fcopy);  break;

        case 'C':   Ccopy = (char *)q;  printf("%c->", *Ccopy); break;

        case 'S':   Ccopy = (char *)q;  printf("%s->", Ccopy); break;

        default:    Print("ERROR\n");
    }
}
