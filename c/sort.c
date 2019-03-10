#include <stdio.h>

typedef int ElementType;  
// ---------------------------------------------------------------------------------------------------------------------
// ����� : �� i < j, ����Ai > Aj, ���(Ai, Aj)Ϊһ�������
// ð���������һ�β�������һ������� (ֻ������Ԫ�ؼ佻��)
void BubbleSort(ElementType *A, int N)
// ElementType * is the aim of sort 
// N is a positive interger which means the length of date
// the complexity of it is bewteen On to On2
// �ŵ�1. ÿһ�˴�ͷ�ŵ�β������������
// �ŵ�2. ����ֻ�� >/< ʱ������ð�ݾ����ȶ��� ( ��ֵͬ�Ķ��Ԫ�ص����λ�ò��� )
{
    int i, j, IsGood;
    ElementType temp; 
    for(i = 0; i < N-1; i++)// ����
    {
        IsGood = 1; // ��ʶ��
        for(j = 0; j < N-i-1; j++)// ��ͷ�ŵ�β����ȥ�Ѿ��źõĲ���
        {
            if(A[j] > A[j+1])
            {
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp; 
                IsGood = 0;
            }
        }
        if(IsGood)break;// ��ǰ����
    }
    return ;
}

void InsertSort(ElementType *A, int N)
// �ŵ�1. �ȶ���
// ���Ӷ���ð�ݻ�����ͬ
{
    int i, j;
    ElementType temp;

    for(i = 1; i < N; i++)
    // A[0]�������
    {
        temp = A[i];
        // �ѵ�ǰ�����ó���
        for(j = i; j > 0 && A[j-1] > temp; j--) // ����������� j - 1 >= 0
            A[j] = A[j-1];
        // �ѱȵ�ǰ�������ȫ������Ų������j��ǰһλ�ȵ�ǰ����С����һλ��֮��
        A[j] = temp;
        // �����ݲ���
    }
    return ;
}
// -----------------------------------------------------------------------------------------------------------------------------
// Ϊ�˽��͸��Ӷ�,����һ�β����������������,Ҳ����˵Ҫ�ڷ���������µĽ���
void ShellSort(ElementType *A, int N)
// ϣ������--���ŵĸĽ�, �����˲���ļ��
{
    int i, j, D, Sedgewick[2] = {1, 5}; // Sedgewick��������, ��ϸ��ʽ���Թȸ�
    ElementType temp;

    for(D = 1; D >= 0; D--) // ����һ���������, �������ڵ�Ч�����������, ����һ����������������
    {
        for(i = Sedgewick[D]; i < N; i++)
        {
            temp = A[i];
            for(j = i; j >= Sedgewick[D] && A[j-Sedgewick[D]] > temp; j-=Sedgewick[D]) // ����������� j - ��� >= 0
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