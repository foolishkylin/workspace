#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

typedef struct Node{
	BiTree date;
	struct Node *next;
} Queue;

typedef struct SNode {
	BiTree date;
	struct SNode *next;
} Stack;

int isNum(char c);                                   // check if a char is a number
Status Traverse(TElemType a);                        // visit the char
double cal(double a, double b, char c);              // cal the result
int make_num(char a);                                // let a char became a number
void error(void);                                    // make the exp_error became true
void menu(void);

int IsEmpty(Queue *Q);                               // the queue
BiTree DeQueue(Queue *Q);
void EnQueue(Queue *Q, BiTree Element);

Stack *CreatStack(void);                             // the stack
void Pop(Stack *S);
void Push(Stack *S, BiTree Element);
BiTree Top(Stack *S);
int StackIsEmpty(Stack *S);

Status InOrderTraverse_cycle(BiTree T, Status (*visit)(TElemType e));    // the cycle traverse

int expression_error = 0;                            // if the exp is wrong

int main()
{
    menu();
    return 0;
}

void menu()
{
    char a[100]; double result;
    while (1)
    {
        puts("please enter a prefix expression(q to quit)");
        gets(a);
        if (a[0] == 'q')
            break;
        BiTree T;
        InitBiTree(&T);
        reset();
        CreateBiTree(&T, a);
        result = Value(T);
        if (expression_error)
        {
            puts("The expression is wrong");
            return ;
        }
        else
            printf("The result is %.2f\n\n", result);
        puts("pre order");
        PreOrderTraverse(T, Traverse);
        puts("\n");
        puts("in order");
        InOrderTraverse(T, Traverse);
        puts("\n");
        puts("post order");
        PostOrderTraverse(T, Traverse);
        puts("\n");
        puts("level order");
        LevelOrderTraverse(T, Traverse);
        puts("\n");
        puts("in order cycle");
        InOrderTraverse_cycle(T, Traverse);
        puts("\n");

        DestroyBiTree(T);
    }
}

int isNum(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/')
        return 0;
    return 1;
 }

Status Traverse(TElemType a)
{
    printf("%c ", a);
    return SUCCESS;
}

double cal(double a, double b, char c)
{
    double result = 0;
    switch (c)
    {
        case '+': result = a + b; break;
        case '-': result = a - b; break;
        case '*': result = a * b; break;
        case '/': result = a / b; break;
        default: error();
    }

    return result;
}

int make_num(char a)
{
    int result = 0;
    switch (a)
    {
        case '9' : result++;
        case '8' : result++;
        case '7' : result++;
        case '6' : result++;
        case '5' : result++;
        case '4' : result++;
        case '3' : result++;
        case '2' : result++;
        case '1' : result++;
        case '0' : break;
        default  : error();
    }
    return result;
}

void error(void)
{
    expression_error = 1;
}

int IsEmpty(Queue *Q)
{
	return Q->next == 0;
}

BiTree DeQueue(Queue *Q)
{
	Queue *Top;
	BiTree T;

	if (IsEmpty(Q))
		printf("\nEmpty queue\n");
	else
	{
		Top = Q->next;
		T = Q->next->date;
		Q->next = Q->next->next;
		free(Top);
	}

	return T;
}

void EnQueue(Queue *Q, BiTree Element)
{
	Queue *Rear = (Queue *) malloc (sizeof(Queue));

	if(Rear == 0)
		printf("\nerror in enqueue\n");
	else
	{
		for (;Q->next;Q=Q->next);
		Rear->next = 0;
		Rear->date = Element;
		Q->next = Rear;
	}

	return ;
}

int StackIsEmpty(Stack *S)
{
	return S->next == 0;
}

void Pop(Stack *S)
{
    if (StackIsEmpty(S))
    {
        puts("ERROR in pop");
        return ;
    }

	Stack *Top;
    Top = S->next;
    S->next = S->next->next;
    free(Top);
}

void Push(Stack *S, BiTree Element)
{
	Stack *Top=(Stack *)malloc(sizeof(Stack));
    Top->date=Element;
    Top->next=S->next;
    S->next=Top;
}

BiTree Top(Stack *S)
{
    if (StackIsEmpty(S))
    {
        puts("ERROR in pop");
        return 0;
    }

	return S->next->date;
}

Status InOrderTraverse_cycle(BiTree T, Status (*visit)(TElemType e))
{
    Stack S;
    S.next = 0;
    while (T || !StackIsEmpty(&S))
    {
        while (T)
        {
            Push(&S, T);
            T = T->lchild;
        }
        while (!StackIsEmpty(&S))
        {
            T = Top(&S);
            visit(T->data);
            Pop(&S);
            T = T->rchild;
        }
    }
}
