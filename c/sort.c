#include <stdio.h>

typedef int ElementType;  
// ---------------------------------------------------------------------------------------------------------------------
// 逆序对 : 对 i < j, 若有Ai > Aj, 则称(Ai, Aj)为一个逆序对
// 冒泡与插入中一次操作消除一个逆序对 (只在相邻元素间交换)
void BubbleSort(ElementType *A, int N)
// ElementType * is the aim of sort 
// N is a positive interger which means the length of date
// the complexity of it is bewteen On to On2
// 优点1. 每一趟从头排到尾，适用于链表
// 优点2. 由于只有 >/< 时交换，冒泡具有稳定性 ( 相同值的多个元素的相对位置不变 )
{
    int i, j, IsGood;
    ElementType temp; 
    for(i = 0; i < N-1; i++)// 趟数
    {
        IsGood = 1; // 标识量
        for(j = 0; j < N-i-1; j++)// 从头排到尾，除去已经排好的部分
        {
            if(A[j] > A[j+1])
            {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp; 
                IsGood = 0;
            }
        }
        if(IsGood)break;// 提前结束
    }
    return ;
}

void InsertSort(ElementType *A, int N)
// 优点1. 稳定性
// 复杂度与冒泡基本相同
{
    int i, j;
    ElementType temp;

    for(i = 1; i < N; i++)
    // A[0]无需操作
    {
        temp = A[i];
        // 把当前数据拿出来
        for(j = i; j > 0 && A[j-1] > temp; j--) // 这里必须满足 j - 1 >= 0
            A[j] = A[j-1];
        // 把比当前大的数据全都往后挪，最后的j的前一位比当前数据小，后一位比之大
        A[j] = temp;
        // 把数据插入
    }
    return ;
}
// -----------------------------------------------------------------------------------------------------------------------------
// 为了降低复杂度,必须一次操作消除多个逆序数,也就是说要在非相邻情况下的交换
void ShellSort(ElementType *A, int N)
// 希尔排序--插排的改进, 增加了插入的间隔
{
    int i, j, D, Sedgewick[2] = {1, 5}; // Sedgewick增量序列, 详细公式可以谷歌
    ElementType temp;

    for(D = 1; D >= 0; D--) // 增加一定间隔排序, 避免相邻低效地消除逆序对, 可以一次性消除多个逆序对
    {
        for(i = Sedgewick[D]; i < N; i++)
        {
            temp = A[i];
            for(j = i; j >= Sedgewick[D] && A[j-Sedgewick[D]] > temp; j-=Sedgewick[D]) // 这里必须满足 j - 间隔 >= 0
                A[j] = A[j-Sedgewick[D]];
            A[j] = temp;
        }
    }
    return ;
}

int main()
{
    ElementType A[10] = {99, 23, 44, 24, 77, 234, 65, 7, 6543, 324};
    // BubbleSort(A, 10);
    InsertSort(A, 10);
    // ShellSort(A, 10);
    for(int i = 0; i < 10; i++)
        printf("%d   ", A[i]);
    getchar();
    getchar();

    return 0;
}