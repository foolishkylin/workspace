#include <stdio.h>
#include <string.h>
// there is answer
// this is a simple question
// just use a double for syntax to search the answer 
// 1st need to find a better solution
int numJewelsInStones(char* J, char* S) {
    int Jbit, Sbit, result = 0;
    for(Sbit = 0; S[Sbit];Sbit++)
        for(Jbit = 0; J[Jbit]; Jbit++)
            if(S[Sbit] == J[Jbit])
                result++;
    return result;
}

int main()
{
    char jewel[50],stone[50];
    while(1)
    {
        gets(jewel);
        gets(stone);
        printf("%d\n", numJewelsInStones(jewel, stone));
    }
    return 0;
}