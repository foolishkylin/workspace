#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AQueue.h"

extern void Print(char *str);
extern int GetSize(char type);
extern char GetType(void);

int IsTypeSelected = 0;
char Type;                          // show the type

/**
 *  @name        : void InitAQueue(AQueue *Q)
 *    @description : 初始化队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void InitAQueue(AQueue *Q)
{
    if (IsTypeSelected)
    {
        Print("Now you are reset a new queue\n");
        DestoryAQueue(Q);
    }
    Type = GetType();
    IsTypeSelected = 1;
    Q->front = Q->rear = Q->length = 0;
}


/**
 *  @name        : void DestoryAQueue(AQueue *Q)
 *    @description : 销毁队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void DestoryAQueue(AQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    int star = Q->front;
    for (; star < Q->length + Q->front; star++)
        free(Q->data[star % MAXQUEUE]);
    ClearAQueue(Q);
    IsTypeSelected = 0;
}



/**
 *  @name        : Status IsFullAQueue(const AQueue *Q)
 *    @description : 检查队列是否已满
 *    @param         Q 队列指针Q
 *    @return         : 满-TRUE; 未满-FALSE
 *  @notice      : None
 */
Status IsFullAQueue(const AQueue *Q)
{
    if (Q->length == MAXQUEUE)
    {
        Print("The queue is full\n");
        return TRUE;
    }
    return FALSE;
}

/**
 *  @name        : Status IsEmptyAQueue(const AQueue *Q)
 *    @description : 检查队列是否为空
 *    @param         Q 队列指针Q
 *    @return         : 空-TRUE; 未空-FALSE
 *  @notice      : None
 */
Status IsEmptyAQueue(const AQueue *Q)
{
    if (Q->length == 0)
    {
        Print("The queue is empty\n");
        return TRUE;
    }

    return FALSE;
}



/**
 *  @name        : Status GetHeadAQueue(AQueue *Q, void *e)
 *    @description : 查看队头元素
 *    @param         Q 队列指针Q，存放元素e
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否空
 */
Status GetHeadAQueue(AQueue *Q, void *e)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsEmptyAQueue(Q))
        return FALSE;

    if (Type != 'S')
        memcpy(e, Q->data[Q->front], GetSize(Type));
    // deal the string case
    else
    {
        char *s = (char *)e;
        int len = strlen(s) + 1;
        memcpy(e, Q->data[Q->front], len);
    }
    return TRUE;
}



/**
 *  @name        : int LengthAQueue(AQueue *Q)
 *    @description : 确定队列长度
 *    @param         Q 队列指针Q
 *    @return         : 队列长度count
 *  @notice      : None
 */
int LengthAQueue(AQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return -1;
    }
    if (!Q)
    {
        Print("You must initialize a queue first\n");
        return -1;
    }
    else
        return Q->length;
}



/**
 *  @name        : Status EnAQueue(AQueue *Q, void *data)
 *    @description : 入队操作
 *    @param         Q 队列指针Q,入队数据指针data
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : 队列是否满了或为空
 */
Status EnAQueue(AQueue *Q, void *data)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsFullAQueue(Q))
        return FALSE;
    Q->length++;

    if (Type != 'S')
    {
        Q->data[Q->rear] = malloc(GetSize(Type));
        memcpy(Q->data[Q->rear], data, GetSize(Type));
    }
    // deal with the string case
    else
    {
        char *s = (char *)data;
        int len = strlen(s) + 1;
        Q->data[Q->rear] = malloc(len);
        memcpy(Q->data[Q->rear], data, len);
    }
    Q->rear = (Q->rear + 1) % MAXQUEUE;

    return TRUE;
}



/**
 *  @name        : Status DeAQueue(AQueue *Q)
 *    @description : 出队操作
 *    @param         Q 队列指针Q
 *    @return         : 成功-TRUE; 失败-FALSE
 *  @notice      : None
 */
Status DeAQueue(AQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsEmptyAQueue(Q))
        return FALSE;
    Q->length--;
    free(Q->data[Q->front]);
    Q->front = (Q->front + 1) % MAXQUEUE;

    return TRUE;
}



/**
 *  @name        : void ClearAQueue(Queue *Q)
 *    @description : 清空队列
 *    @param         Q 队列指针Q
 *  @notice      : None
 */
void ClearAQueue(AQueue *Q)
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return ;
    }
    Q->front = Q->rear = Q->length = 0;
}



/**
 *  @name        : Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
 *    @description : 遍历函数操作
 *    @param         Q 队列指针Q，操作函数指针foo
 *    @return         : None
 *  @notice      : None
 */
Status TraverseAQueue(const AQueue *Q, void (*foo)(void *q))
{
    if (!IsTypeSelected)
    {
        Print("You need to create a queue first\n");
        return FALSE;
    }
    if (IsEmptyAQueue(Q))
        return FALSE;

    int star = Q->front;
    Print("");
    for (; star < Q->length + Q->front; star++)
        foo(Q->data[star % MAXQUEUE]);
    return TRUE;
}



/**
 *  @name        : void APrint(void *q)
 *    @description : 操作函数
 *    @param         q 指针q
 *  @notice      : None
 */
void APrint(void *q)
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
