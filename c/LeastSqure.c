#include <stdio.h>
#include <string.h>
double abs(double a)
{
    if(a < 0.0) a *= -1;
    return a; 
}
// ��С���˷����������ֱ��
// ��ȥ��Ⱥ�㣬������
int main()
{
    double x, y, A, B, a[3], b[3], k;
    // ��� y = Ax + B
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    while(scanf("%lf%lf", &x, &y) != EOF)
    // ��ȡ����㣬Ҫ��������������޹�
    // ������ˣ�At*(A|b)
    {
        a[0] += 1; a[1] += x;      a[2] += y;  
        b[0] += x; b[1] += x * x;  b[2] += x * y; 
        // ������ʽ��ϵ��
        // a0B + a1A = a2
        // b0B + b1A = b2
    }
    // ����������ʽ���
    k = b[0] / a[0]; 
    for(int i = 0; i < 3; i++)
        a[i] *= k; 
    A = (a[2] - b[2]) / (a[1] - b[1]);
    B = (b[2] - b[1] * A) / b[0];
    printf("Y = %.2lfX", A);
    if(B > 0.0) printf(" + ");
    else printf(" - ");
    printf("%.2lf\n", abs(B));
    getchar();
    getchar();

    return 0;
}