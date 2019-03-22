#include <stdio.h>
#include <stdlib.h>
#define MaxDate 1e8
// ����
typedef struct HeapStruct *MaxHeap; 
typedef int ElementType; 
struct HeapStruct
{
    ElementType *Element; // ������
    int Size;             // ��Ԫ������
    int Capacity;         // ������
};

MaxHeap Creat(int MaxSize) // ��������Ϊmaxsize�Ķ�
{
    MaxHeap H = (MaxHeap) malloc(sizeof(struct HeapStruct));
    H->Element = (ElementType *) malloc((MaxSize + 1) * sizeof(ElementType));
    // +1����Ϊ�ڱ���ռһ������λ�����䲢�����ڳ�Ա
    H->Size = 0; 
    H->Capacity = MaxSize; 
    H->Element[0] = MaxDate; // �ڱ�

    return H; 
}

int IsEmpty(MaxHeap H)
{
    return H->Size == 0; 
}

int IsFull(MaxHeap H)
{
    return H->Size == H->Capacity; 
}

void Insert(MaxHeap H, ElementType item)
{
    int i; 
    if(IsFull(H))
    {
        printf("the maxheap is full of element\n");
        return ;
    }
    i = ++H->Size; 
    // ֱ�Ӳ��뵽���Ԫ��
    for(; H->Element[i/2] < item; i/=2)
        H->Element[i] = H->Element[i/2];
    // ���ڲ��������Сλ��������Ҫ����
    // �����ǰ�ĸ�λС�ڲ���Ԫ�أ�ֱ�Ӱ���������(��λ�����游λ)
    // ���ѭ�������ҵ����ʵ�λ��ʱ������ԭ��λ���������պÿճ�һ��λ��
    H->Element[i] = item; 
    // ֱ�Ӳ���
    return ;
}

ElementType DeleteMax(MaxHeap H)
// ɾ�����㣬���ض���ֵ����Ҫ����
{
    int Parent, Child; 
    ElementType MaxItem, temp; 
    if(IsEmpty(H))
    {
        printf("the maxheap is empty\n");
        return 0; 
    }
    MaxItem = H->Element[1];
    // ����
    temp = H->Element[H->Size--]; 
    for(Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    // �Ӷ��㿪ʼѭ��
    // Parent * 2 <= H->Size ��������Ӵ��ڣ������ʽ�������򲻴��������
    {
        Child = Parent * 2; 
        if((Child != H->Size) && (H->Element[Child] < H->Element[Child+1]))
            Child++;
        //ʹchildָ�����Ҷ��Ӽ�Ĵ���
        if(temp >= H->Element[Child]) break; 
        // ���ҵ�temp�Ĳ������˳�
        else 
            H->Element[Parent] = H->Element[Child];
        // �Ѵ���temp�ĵ������� ��һ�λḲ�Ƕ���
        // ֱ���ҵ�����λ��
    }
    H->Element[Parent] = temp;
    // ����

    return MaxItem; 
}

void PercDown(MaxHeap H, int p)
// ����H->Element[p]Ϊ�����Ӷѵ���Ϊ����
// ��ɾ����������
// ��С���ʱ3��������һ�����ڵ���������������������Ǹ�
{
    int Parent, Child; 
    ElementType Root; 
    Root = H->Element[p]; 
    for(Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2; 
        if((Child != H->Size) && (H->Element[Child] < H->Element[Child+1]))
            Child++;
        if(Root >= H->Element[Child]) break; 
        else H->Element[Parent] = H->Element[Child];       
    }
    H->Element[Parent] = Root; 
    return ;
}

void BuildHeap(MaxHeap H)
// ��������Ԫ��ֱ����Ϊ����
// Ĭ�϶�������Ԫ��
{
    int i; 
    for(i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
    return ;
}

int main()
{
    MaxHeap H = Creat(6); 
    for(int i = 1; i < 6; i++)
        Insert(H, i); 
    for(int i = 1; i < 6; i++)
        printf("%d  ", H->Element[i]);  
    puts("");
    BuildHeap(H);
    for(int i = 1; i < 6; i++)
        printf("%d  ", H->Element[i]);
    getchar();
    getchar();

    return 0;
}