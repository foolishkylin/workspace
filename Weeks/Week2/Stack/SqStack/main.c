#include <stdio.h>
#include <stdlib.h>
#include "SqStack.h"

#define MaxSize 50
// the maximum size of stack

Status IsCreated(int Flag); // check if the stack is created
Status IsFull(SqStack *s);  // check if the stack is full
void PrintLine(void);       // print some char to decoration
void Wait(void);            // get some space to stop
ElemType GetKey(void);      // get the right value
char GetOption(void);       // get the right char
void Menu(void);            // print the menu and call the functions

int main()
{
    Menu();

    return 0;
}

Status IsCreated(int Flag)
{
    if (Flag == 0)
    {
        PrintLine();
        puts("You need to creat a stack first");
        return ERROR;
    }
    return SUCCESS;
}

Status IsFull(SqStack *s)
{
    if (s->top == s->size-1)
    {
        PrintLine();
        puts("The stack is full");
        return SUCCESS;
    }
    return ERROR;
}

void PrintLine(void)
{
    printf("\n>>> ");
}

void Wait(void)
{
    PrintLine();
    puts("Enter anything to continue");
    getchar();
    getchar();
}

ElemType GetKey(void)
{
    ElemType key;
    PrintLine();
    puts("Please enter a value");
    while (1)
    {
        PrintLine();
        if(scanf("%d", &key) == 1)
            break;
        else
        {
            PrintLine();
            puts("Input ERROR");
            while(getchar() != '\n');
        }
    }
    return key;
}

char GetOption(void)
{
    char Option[2];
    PrintLine();
    puts("Plese enter a char");
    while (1)
    {
        int IsRight = 1;
        PrintLine();
        scanf("%s",Option);
        getchar();
        if (Option[0] < 'A' || Option[0] >'Z' || Option[1] != 0)
            IsRight = 0;
        if (!IsRight)
        {
            PrintLine();
            puts("Input ERROR");
            continue;
        }
        else
            break;
    }
    return Option[0];
}

void Menu(void)
{
    int IsEnd = 0;
    ElemType e;
    SqStack *s = (SqStack *) malloc (sizeof(SqStack));
    while(!IsEnd)
    {
        system("cls");
        char option;
        PrintLine();
        printf("Please select the function as follows\n");
        puts("   A. Creat a stack");
        puts("   B. Get the top element");
        puts("   C. Clean the stack");
        puts("   D. Get the length of stack");
        puts("   E. Push");
        puts("   F. Pop");
        puts("   G. Back");
        option = GetOption();
        system("cls");
        switch(option)
        {
            case 'A':   initStack(s,MaxSize);
                        Wait(); break;

            case 'B':   if (getTopStack(s, &e))
                        {
                            PrintLine();
                            printf("The top element is %d\n", e);
                        }
                        Wait(); break;

            case 'C':   clearStack(s);
                        Wait(); break;

            case 'D':   if (stackLength(s, &e))
                        {
                            PrintLine();
                            printf("The length of it is %d\n", e);
                        }
                        Wait(); break;

            case 'E':   pushStack(s, GetKey());
                        Wait(); break;

            case 'F':   if (popStack(s, &e))
                        {
                            PrintLine();
                            printf("The final element is %d\n", e);
                        }
                        Wait(); break;

            case 'G':   IsEnd = 1; break;

            default :   PrintLine(); puts("INPUT ERROR"); Wait();
        }
    }
    destroyStack(s);
}
