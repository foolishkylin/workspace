#include <stdio.h>
#include <stdlib.h>
#define MaxDate 1e8
// 最大堆
typedef struct HeapStruct *MaxHeap; 
typedef int ElementType; 
struct HeapStruct
{
    ElementType *Element; // 堆数组
    int Size;             // 堆元素上限
    int Capacity;         // 堆容量
};

MaxHeap Creat(int MaxSize) // 创建容量为maxsize的堆
{
    MaxHeap H = (MaxHeap) malloc(sizeof(struct HeapStruct));
    H->Element = (ElementType *) malloc((MaxSize + 1) * sizeof(ElementType));
    // +1是因为哨兵会占一个数组位，但其并不属于成员
    H->Size = 0; 
    H->Capacity = MaxSize; 
    H->Element[0] = MaxDate; // 哨兵

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
    // 直接插入到最后元素
    for(; H->Element[i/2] < item; i/=2)
        H->Element[i] = H->Element[i/2];
    // 由于插入的是最小位，所以需要调整
    // 如果当前的父位小于插入元素，直接把它拉下来(子位拿来存父位)
    // 如此循环，当找到合适的位置时，所有原父位都下拉，刚好空出一个位置
    H->Element[i] = item; 
    // 直接插入
    return ;
}

ElementType DeleteMax(MaxHeap H)
// 删除顶点，返回顶点值，需要调整
{
    int Parent, Child; 
    ElementType MaxItem, temp; 
    if(IsEmpty(H))
    {
        printf("the maxheap is empty\n");
        return 0; 
    }
    MaxItem = H->Element[1];
    // 备份
    temp = H->Element[H->Size--]; 
    for(Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    // 从顶点开始循环
    // Parent * 2 <= H->Size 代表左儿子存在，若表达式不成立则不存在左儿子
    {
        Child = Parent * 2; 
        if((Child != H->Size) && (H->Element[Child] < H->Element[Child+1]))
            Child++;
        //使child指向左右儿子间的大者
        if(temp >= H->Element[Child]) break; 
        // 若找到temp的插入则退出
        else 
            H->Element[Parent] = H->Element[Child];
        // 把大于temp的点上拉， 第一次会覆盖顶点
        // 直至找到合适位置
    }
    H->Element[Parent] = temp;
    // 插入

    return MaxItem; 
}

void PercDown(MaxHeap H, int p)
// 将以H->Element[p]为根的子堆调整为最大堆
// 与删除极其类似
// 最小情况时3个数必有一个大于等于另外两个，这个数就是根
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
// 调整堆中元素直到成为最大堆
// 默认堆中已有元素
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