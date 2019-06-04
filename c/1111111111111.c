#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    int a = 3;
    void *b;

    memcpy(b, &a, sizeof(int));
    int *c = (int *)b;
    printf("%d\n", *c);

    return 0;
}