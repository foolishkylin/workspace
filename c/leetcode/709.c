#include <stdio.h>
#include <string.h>

char* toLowerCase(char* str) {
    int bit;

    for(bit = 0; str[bit]; bit++)
    {
        if(str[bit] >= 'A'&& str[bit] <= 'Z')
            str[bit] += 32;
    }

    return str;
}

int main()
{
    char str[100];
    gets(str);
    puts(toLowerCase(str));
    getchar();
    getchar();
    return 0;
}

