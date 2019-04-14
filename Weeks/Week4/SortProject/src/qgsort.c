#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "qgsort.h"

#define MaxDigit 6
#define Radix 10

typedef struct SNode   // use in quick sort
{
	int date;
	struct SNode *next;
} Stack;

typedef struct LNode
{
    int key;
    struct LNode *next;
} *List;

typedef struct HeadNode // use in radix sort
{
    List head, tail;
} Bucket[Radix];

extern Stack *CreatStack(void);
extern void Pop(Stack *S);
extern void Push(Stack *S, int Element);
extern int Top(Stack *S);
extern int IsEmpty(Stack *S);
extern void swap(int *a, int *b);
/**
 *  @name        : void insertSort(int *a,int n);
 *  @description : 插入排序
 *  @param       : 数组指针 a, 数组长度 n
 */
void insertSort(int *a,int n)
{
    int i, j, temp;

    for(i = 1; i < n; i++)
    // A[0] doesn't need to handle
    {
        temp = a[i];
        // take the current data out
        for(j = i; j > 0 && a[j-1] > temp; j--) // must satisfy j - 1 >= 0
            a[j] = a[j-1];
        // the one which is bigger than the current one should move backwards
        a[j] = temp;
        // insert the data
    }

    return ;
}


/**
 *  @name        : void MergeArray(int *a,int begin,int mid,int end,int *temp);
 *  @description : 归并排序（合并数组）
 *  @param       : 数组指针a，数组起点begin，数组中点mid，数组终点end，承载数组指针temp
 */
void MergeArray(int *a,int begin,int mid,int end,int *temp)
{
    int left_end, number, pos;
    int i;

    left_end = mid - 1;
    pos = begin;
    number = end - begin + 1;

    while(begin <= left_end && mid <= end)
    {
        if (a[begin] <= a[mid])
            temp[pos++] = a[begin++]; /* copy the left array */
        else
            temp[pos++] = a[mid++];   /* copy the right array */
    }

    while(begin <= left_end)
        temp[pos++] = a[begin++];     /* deal with the last */
    while(mid <= end)
        temp[pos++] = a[mid++];

    for(i = 0; i < number; i++, end--)
        a[end] = temp[end];           /* copy the array to a[] */
}


/**
 *  @name        : void MergeSort(int *a,int begin,int end,int *temp);
 *  @description : 归并排序
 *  @param       : 数组指针a，数组起点begin，数组终点end，承载数组指针temp
 */
void MergeSort(int *a,int begin,int end,int *temp)
{
    int mid;
    if (begin < end)
    {
        mid = (begin + end) / 2;
        MergeSort(a, begin, mid, temp);              /* deal with the left part */
        MergeSort(a, mid + 1, end, temp);            /* deal with the right part */
        MergeArray(a, begin, mid + 1, end, temp);    /* Merge */
    }
}


/**
 *  @name        : void QuickSort(int *a, int begin, int end);
 *  @description : 快速排序（递归版）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
void QuickSort_Recursion(int *a, int begin, int end)
{
    if (begin >= end)
        return ;
    int pos = Partition(a, begin, end);
    QuickSort_Recursion(a, begin, pos - 1);         /* deal with the left part */
    QuickSort_Recursion(a, pos + 1, end);           /* deal with the right part */
}


/**
 *  @name        : void QuickSort(int *a,int size)
 *  @description : 快速排序（非递归版）
 *  @param       : 数组指针a，数组长度size
 */
void QuickSort(int *a,int size)
{
    Stack *S = CreatStack();
	Push(S, 0);
	Push(S, size - 1);
	int left, right, mid;
	while(!IsEmpty(S))
	{
		right = Top(S);
		Pop(S);
		left = Top(S);
		Pop(S);
		mid = Partition(a, left, right);
		if (mid - 1 > left)
		{
            Push(S, left);
            Push(S, mid - 1);
		}
		if (mid + 1 < right)
		{
            Push(S, mid + 1);
            Push(S, right);
		}
	}
}



/**
 *  @name        : void QuickSort(int *a, int begin, int end)
 *  @description : 快速排序（枢轴存放）
 *  @param       : 数组指针a，数组起点begin，数组终点end
 */
int Partition(int *a, int begin, int end)
{
    int pivot = a[begin];
    int i = begin, j = end;
    while (i < j)
    // take the ones less than the pivot before the pivot
    // and the bigger ones after the pivot
    {
        while (i < j && a[j] >= pivot) j--;
        while (i < j && a[i] <= pivot) i++;
        if(i < j) swap(a+i, a+j);
    }
    a[begin] = a[i];
    a[i] = pivot;

    return i;
}


/**
 *  @name        : void CountSort(int *a, int size , int max)
 *  @description : 计数排序
 *  @param       : 数组指针a，数组长度size，数组最大值max
 */
void CountSort(int *a, int size , int max)
{
    int i;
    int *count = (int *) malloc ((max + 1) * sizeof(int));
    int *temp = (int *) malloc ((size + 1) * sizeof(int));
    memset(count, 0, sizeof(count) * max);
    memset(temp, 0, sizeof(temp) * size);

    for (i = 0; i < size; i++) count[a[i]]++;                      // count the index
    for (i = 1; i < max + 1; i++) count[i] += count[i - 1];        // calculate the sum of the prefixes
    for (i = size - 1; i >= 0; i--)
    {
        temp[count[a[i]] - 1] = a[i];                              // output the count result according to the index
        count[a[i]]--;
    }
    for (i = 0; i < size; i++)                                     // copy the result
        a[i] = temp[i];

    if(count != NULL)free(count);
    if(temp != NULL)free(temp);
}


/**
 *  @name        : void RadixCountSort(int *a,int size)
 *  @description : 基数计数排序
 *  @param       : 数组指针a，数组长度size
 */
void RadixCountSort(int *a,int size)
{
    int D, Di, data_copy, i;                     // D - current digit    Di - current digit value of data
    Bucket B;
    List tmp, list = NULL;

    // initialize the buckets
    for (i=0; i<Radix; i++)
         B[i].head = B[i].tail = NULL;
    for (i=0; i<size; i++)
    // initialize the list and store the data in reverse order
    {
        tmp = (List) malloc (sizeof(struct LNode));
        tmp->key = a[i];
        tmp->next = list;
        list = tmp;
    }

    for (D = 1; D <= MaxDigit; D++)
    {
        // take the data in buckets
        while (list)
        {
            // get the current digit
            data_copy = list->key;
            for (i = 1; i <= D; i++)
            {
                Di = data_copy % Radix;
                data_copy /= Radix;
            }
            // into buckets
            tmp = list; list = list->next;
            tmp->next = NULL;
            if (B[Di].head == NULL)
                B[Di].head = B[Di].tail = tmp;
            else
            {
                B[Di].tail->next = tmp;
                B[Di].tail = tmp;
            }
        }
        // take the data in buckets back to the list
        list = NULL;
        for (Di = Radix - 1; Di>=0; Di--)
        {
            if (B[Di].head)
            {
                B[Di].tail->next = list;
                list = B[Di].head;
                B[Di].head = B[Di].tail = NULL;
            }
        }
    }
    for (i=0; i < size; i++)
    {
        tmp = list;
        list = list->next;
        a[i] = tmp->key;
        free(tmp);
    }
}


/**
 *  @name        : void ColorSort(int *a,int size)
 *  @description : 颜色排序
 *  @param       : 数组指针a（只含0，1，2元素），数组长度size
 */
void ColorSort(int *a, int size)
{
    int ptr1 = 0, ptr2 = size - 1, ptr_current = 0;
    for (ptr_current = 0; ptr_current <= ptr2; ptr_current++)
    {
        if (a[ptr_current] == 0)
            swap(&a[ptr_current], &a[ptr1++]);
        else if (a[ptr_current] == 2)
            swap(&a[ptr_current--], &a[ptr2--]);  // current pointer - 1 means to rejudge the current data
    }
}


/**
 *  @name        : 自拟
 *  @description : 在一个无序序列中找到第K大/小的数
 *  @param       : 数组指针a，数组长度size
 */
int findKth(int *a, int n, int k)
{
    int begin = 0, end = n - 1, index;
    while (begin < end)
    {
        index = Partition(a, begin, end);
        if (index + 1 == k)
                break;
        else if (index + 1 < k)
            begin = index + 1;
        else if (index + 1 > k)
            end = index;
    }
    return a[index];
}
