#include <stdio.h>
#include <string.h>
double abs(double a)
{
    if(a < 0.0) a *= -1;
    return a; 
}
// 最小二乘法（矩阵）拟合直线
// 无去离群点，无正则化
int main()
{
    double x, y, A, B, a[3], b[3], k;
    // 拟合 y = Ax + B
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    while(scanf("%lf%lf", &x, &y) != EOF)
    // 读取坐标点，要求坐标矩阵线性无关
    // 矩阵相乘，At*(A|b)
    {
        a[0] += 1; a[1] += x;      a[2] += y;  
        b[0] += x; b[1] += x * x;  b[2] += x * y; 
        // 两条等式的系数
        // a0B + a1A = a2
        // b0B + b1A = b2
    }
    // 联立两条等式求解
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