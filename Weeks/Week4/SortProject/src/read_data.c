#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qgsort.h"

typedef void (*FP)(int* a, int b);       // function pointer for formated sort_function
// stack
typedef struct SNode {
	int date;
	struct SNode *next;
} Stack;
Stack *CreatStack(void);
void Pop(Stack *S);
void Push(Stack *S, int Element);
int Top(Stack *S);
int IsEmpty(Stack *S);

void swap(int *a, int *b);
double test(int *a, int times, FP f);   // cal the time

void CMergeSort(int *a, int n);        // format the function
void CQuickSort(int *a, int n);
void CCountSort(int *a, int n);
int *load();

int main()
{
    Do();

    return 0;
}

int *load()
{
    int i;
    int *a = (int * ) malloc (sizeof(int) * 1e5);
    FILE *fp = fopen("data.txt","r");
    if (fp == NULL) return NULL;
    for (i = 0; i < 1e4; i++)
        if (fscanf(fp, "%d", a + i) == EOF)
            break;

    return a;
}

double test(int *a, int times, FP f)
{
    clock_t start, finish;
    double duration;
    start = clock();
    f(a,times);
    finish= clock();
    duration = (double)(finish- start) / CLOCKS_PER_SEC;

    return duration;
}

void Do(void)
{
    int *a = load();
    if (a == NULL)
    {
        puts("ERROR");
        getchar();
        return ;
    }
    puts("\n\n\tPlease wait...");
    printf("\tThis is 1e4 data\n\n");

    printf("\n\n\tInserted Sort: \t%lfs\n\n", test(a, 1e4, insertSort));
    free(a);

    a = load();
    printf("\tMerge Sort: \t%lfs\n\n", test(a, 1e4, CMergeSort));
    free(a);

    a = load();
    printf("\tQuick  Sort: \t%lfs\n\n", test(a, 1e4, CQuickSort));
    free(a);

    a = load();
    printf("\tCount Sort: \t%lfs\n\n", test(a, 1e4, CCountSort));
    free(a);

    a = load();
    printf("\tRadix Sort: \t%lfs\n\n", test(a, 1e4, RadixCountSort));
    free(a);

    getchar();
}

void CCountSort(int *a, int n)
{
    CountSort(a, n, 32768);
}

void CMergeSort(int *a, int n)
{
    int *b = (int *) malloc (n * sizeof(int));
    MergeSort(a, 0, n - 1, b);
    free(b);
}

void CQuickSort(int *a, int n)
{
    QuickSort_Recursion(a, 0, n - 1);
}

void swap(int *a, int *b)
{
    int c = *a;
    *a = *b, *b = c;
}

int IsEmpty(Stack *S)
{
	return S->next==0;
}

void Pop(Stack *S)
{
    if (IsEmpty(S))
    {
        puts("ERROR in pop");
        return ;
    }

	Stack *Top;
    Top=S->next;
    S->next=S->next->next;
    free(Top);
}

void Push(Stack *S, int Element)
{
	Stack *Top=(Stack *)malloc(sizeof(Stack));
    Top->date=Element;
    Top->next=S->next;
    S->next=Top;
}

int Top(Stack *S)
{
    if (IsEmpty(S))
    {
        puts("ERROR in pop");
        return 0;
    }

	return S->next->date;
}

Stack *CreatStack(void)
{
	Stack *S;

	S=(Stack *)malloc(sizeof(Stack));
	if(S==0)
		printf("\nerror\n");
	S->next=0;

	return S;
}
