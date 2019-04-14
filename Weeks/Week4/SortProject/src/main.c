#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "qgsort.h"

#define CASE1 1e4
#define CASE2 5e4
#define CASE3 2e5
#define CASE4 100
#define TIMES 1e5

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
void massive_once(int cases);
void massive_repeated();
double test(int *a, int times, FP f);   // cal the time
void color_test();
void kth_test();

void CMergeSort(int *a, int n);        // format the function
void CQuickSort(int *a, int n);
void CCountSort(int *a, int n);


int main()
{
    massive_once(CASE1);
    massive_once(CASE2);
    massive_once(CASE3);
    massive_repeated();
    puts("\n\tenter anything to continue(color test and the kth test)\n\n");
    getchar();
    system("cls");
    color_test();
    kth_test();
    getchar();
    return 0;
}

void kth_test()
{
    int i; srand(time(NULL));
    int *a = (int *) malloc (101 * sizeof(int));
    for (i = 0; i < 100; i++) a[i] = rand();
    puts("\n\n\tThis is the kth test\n");
    puts("\tThe example is :\n");
    for(i = 0; i < 100; i++)
        printf("\t%d", a[i]);
    printf("\n\n\tthe biggest (100th) one is %d\n\n", findKth(a, 100, 100));
    printf("\tthe smallest (0th) one is %d\n\n", findKth(a, 100, 0));
    printf("\tthe mid (50th) one is %d\n\n", findKth(a, 100, 50));

}

void color_test()
{
    int i; srand(time(NULL));
    int *a = (int *) malloc (101 * sizeof(int));
    for (i = 0; i < 100; i++) a[i] = rand() % 3;
    puts("\n\tThis is the color sort test\n");
    puts("\tThe example is :\n");
    for(i = 0; i < 100; i++)
        printf("%d\t", a[i]);
    ColorSort(a, 100);
    puts("\n\n\tThe result is :\n");
    for(i = 0; i < 100; i++)
        printf("%d\t", a[i]);
    puts("\n\n");
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

void massive_repeated()
{
    int i, j; double times;
    srand(time(NULL));              // initialize the seed
    int *a = (int *) malloc (CASE4 * sizeof(int));
    puts("\n\n\tPlease wait...");
    printf("\tThis is 100 data and sort it for 100k times\n\n");

    for (i = 0, times = 0; i < TIMES; i++)
    {
        for (j = 0; j < CASE4; j++) a[j] = rand();
        times += test(a, CASE4, insertSort);
    }
    printf("\n\n\tInserted Sort: \t%lfs\n\n", times);

    for (i = 0, times = 0; i < TIMES; i++)
    {
        for (j = 0; j < CASE4; j++) a[j] = rand();
        times += test(a, CASE4, CMergeSort);
    }
    printf("\tMerge Sort: \t%lfs\n\n", times);

    for (i = 0, times = 0; i < TIMES; i++)
    {
        for (j = 0; j < CASE4; j++) a[j] = rand();
        times += test(a, CASE4, CQuickSort);
    }
    printf("\tQuick Sort: \t%lfs\n\n", times);

    for (i = 0, times = 0; i < TIMES; i++)
    {
        for (j = 0; j < CASE4; j++) a[j] = rand();
        times += test(a, CASE4, CCountSort);
    }
    printf("\tCount Sort: \t%lfs\n\n", times);

    for (i = 0, times = 0; i < TIMES; i++)
    {
        for (j = 0; j < CASE4; j++) a[j] = rand();
        times += test(a, CASE4, RadixCountSort);
    }
    printf("\tRadix Sort: \t%lfs\n\n", times);

    free(a);
}

void massive_once(int cases)
{
    srand(time(NULL)); int i;
    int *a = (int *) malloc (cases * sizeof(int));
    puts("\n\n\tPlease wait...");
    printf("\tThis is %d data\n\n", cases);

    for (i = 0; i < cases; i++) a[i] = rand();
    printf("\n\n\tInserted Sort: \t%lfs\n\n", test(a, cases, insertSort));

    for (i = 0; i < cases; i++) a[i] = rand();
    printf("\tMerge Sort: \t%lfs\n\n", test(a, cases, CMergeSort));

    for (i = 0; i < cases; i++) a[i] = rand();
    printf("\tQuick  Sort: \t%lfs\n\n", test(a, cases, CQuickSort));

    for (i = 0; i < cases; i++) a[i] = rand();
    printf("\tCount Sort: \t%lfs\n\n", test(a, cases, CCountSort));

    for (i = 0; i < cases; i++) a[i] = rand();
    printf("\tRadix Sort: \t%lfs\n\n", test(a, cases, RadixCountSort));

    free(a);
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
