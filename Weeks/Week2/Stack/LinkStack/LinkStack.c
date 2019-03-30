#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

int IsInited = 0;
// due to the 'initstack' using the 1 rank pointer
// we cannot malloc ram for LinkStack in the function
// this valuable is to check if the stack is initialized

//��ջ(���������)
Status initLStack(LinkStack *s)   //��ʼ��
{
    if (IsInited)
    {
        Print("The stack is already initialized\n");
        return ERROR;
    }
    IsInited = 1;
    s->top = NULL;
    s->count = 0;
    Print("The stack is initialized successfully\n");
    return SUCCESS;
}

Status isEmptyLStack(LinkStack *s)  //�ж���ջ�Ƿ�Ϊ��
{
    if (!IsInit(IsInited))
        return ERROR;
    if (s->top == NULL)
    {
        Print("The stack is empty\n");
        return SUCCESS;
    }
    return ERROR;
}

Status getTopLStack(LinkStack *s,ElemType *e)  //�õ�ջ��Ԫ��
{
    if (!IsInit(IsInited) || isEmptyLStack(s))
        return ERROR;
    *e = s->top->data;

    return SUCCESS;
}

Status clearLStack(LinkStack *s)   //���ջ
{
    if (!IsInit(IsInited) || isEmptyLStack(s))
        return ERROR;
    while(s->top)
    {
        LinkStackPtr ptr= s->top->next;
        // record the next pointer before it changed
        free(s->top);
        s->top = ptr;
    }
    s->top = NULL;
    Print("The stack is already cleaned\n");

    return SUCCESS;
}

Status destroyLStack(LinkStack *s)   //����ջ
{
    if (!IsInit(IsInited) || isEmptyLStack(s))
        return ERROR;
    clearLStack(s);
    free(s);
    Print("The stack is already destroyed\n");
    return ERROR;
}

Status LStackLength(LinkStack *s,int *length)    //���ջ����
{
    if (!IsInit(IsInited))
        return ERROR;
    *length = s->count;

    return SUCCESS;
}

Status pushLStack(LinkStack *s,ElemType data)   //��ջ
{
    if (!IsInit(IsInited))
        return ERROR;
    LinkStackPtr ptr_next = s->top;

    s->top = (LinkStackPtr) malloc (sizeof(StackNode));
    if (s->top == NULL)
    {
        Print("ERROR\n");
        return ERROR;
    }
    s->top->data = data;
    s->top->next = ptr_next;
    s->count++;

    return SUCCESS;
}

Status popLStack(LinkStack *s,ElemType *data)   //��ջ
{
    if (!IsInit(IsInited) || isEmptyLStack(s))
        return ERROR;
    LinkStackPtr ptr_copy = s->top;
    // record the pointer before it changed

    *data = s->top->data;
    s->top = s->top->next;
    free(ptr_copy);
    s->count--;

    return SUCCESS;
}
