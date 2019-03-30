#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"

int IsInit = 0;
// due to the 'initstack' using the 1 rank pointer
// we cannot malloc ram for stack in the function
// this valuable is to check if the stack is initialized

//˳��ջ(���������)
Status initStack(SqStack *s,int sizes)  //��ʼ��ջ
{
    if (IsInit)
    {
        PrintLine();
        puts("The stack is already initialized");
        return ERROR;
    }
    IsInit = 1;
    // now the stack is already initialized
    s->elem = (ElemType *) malloc (sizes * sizeof(ElemType));
    s->top = -1;
    // means length equal 0
    s->size = sizes;
    PrintLine();
    puts("The stack is initialized successfully");

    return SUCCESS;
}

Status isEmptyStack(SqStack *s)   //�ж�ջ�Ƿ�Ϊ��
{
    if (!IsCreated(IsInit))
        return ERROR;
    if (s->top == -1)
    {
        PrintLine();
        puts("The stack is empty");
        return SUCCESS;
    }
    return ERROR;
}

Status getTopStack(SqStack *s,ElemType *e)   //�õ�ջ��Ԫ��
{
    if(!IsCreated(IsInit) || isEmptyStack(s))
        return ERROR;
    *e = s->elem[s->top];

    return SUCCESS;
}

Status clearStack(SqStack *s)   //���ջ
{
    if(!IsCreated(IsInit))
        return ERROR;
    s->top = -1;
    PrintLine();
    puts("The stack is already cleaned");

    return SUCCESS;
}

Status destroyStack(SqStack *s)  //����ջ
{
    if(!IsCreated(IsInit))
        return ERROR;
    free(s->elem);
    free(s);
    PrintLine();
    puts("The stack is already destroyed");

    return SUCCESS;
}

Status stackLength(SqStack *s,int *length)   //���ջ����
{
    if(!IsCreated(IsInit))
        return ERROR;
    *length = s->top + 1;
    return SUCCESS;
}

Status pushStack(SqStack *s,ElemType data)  //��ջ
{
    if (!IsCreated(IsInit) || IsFull(s))
        return ERROR;
    s->elem[++(s->top)] = data;
    return SUCCESS;
}

Status popStack(SqStack *s,ElemType *data)   //��ջ
{
    if(!IsCreated(IsInit) || isEmptyStack(s))
        return ERROR;
    *data = s->elem[(s->top)--];
    return SUCCESS;
}


