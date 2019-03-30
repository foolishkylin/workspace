#include <stdio.h>
#include <stdlib.h>
#include "LinkStack.h"

void Print(char *str);        // print some char with decoration
void Wait(void);              // get some space to stop
ElemType GetKey(void);        // get the right value
char GetOption(void);         // get the right char
void Menu(void);              // print the menu and call the functions

Status IsInit(int flag);      // check if the stack is initialized and output some information


int main()
{
    Menu();

    return 0;
}

Status IsInit(int flag)
{
    if (flag == 0)
    {
        Print("You need to initialize the stack first\n");
        return ERROR;
    }
    return SUCCESS;
}

void Print(char *str)
{
    printf("\n>>> ");
    printf("%s", str);
}

void Wait(void)
{
    Print("Enter anything to continue\n");
    getchar();
    getchar();
}

ElemType GetKey(void)
{
    ElemType key;
    Print("Please enter a value\n");
    while (1)
    {
        Print("");
        if(scanf("%d", &key) == 1)
            break;
        else
        {
            Print("Input ERROR\n");
            while(getchar() != '\n');
        }
    }
    return key;
}

char GetOption(void)
{
    char Option[2];
    Print("Plese enter a char\n");
    while (1)
    {
        int IsRight = 1;
        Print("");
        scanf("%s",Option);
        getchar();
        if (Option[0] < 'A' || Option[0] >'Z' || Option[1] != 0)
            IsRight = 0;
        if (!IsRight)
        {
            Print("Input ERROR\n");
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
    LinkStack *s = (LinkStack *) malloc (sizeof(LinkStack));
    while(!IsEnd)
    {
        system("cls");
        char option;
        Print("Please select the function as follows\n\n");
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
            case 'A':   initLStack(s);
                        Wait(); break;

            case 'B':   if (getTopLStack(s, &e))
                        {
                            Print("");
                            printf("The top element is %d\n", e);
                        }
                        Wait(); break;

            case 'C':   clearLStack(s);
                        Wait(); break;

            case 'D':   if (LStackLength(s, &e))
                        {
                            Print("");
                            printf("The length of it is %d\n", e);
                        }
                        Wait(); break;

            case 'E':   Print("Please enter the number of the element you want to push\n");
                        while (1)
                        {
                            e = GetKey();
                            if (e < 1)
                                Print("The number of element must be positive\n");
                            else break;
                        }
                        while (e--)
                        {
                            Print("");
                            printf("Last %d value\n", e + 1);
                            if(!pushLStack(s, GetKey()))
                                break;
                        }
                        Wait(); break;

            case 'F':   if (popLStack(s, &e))
                        {
                            Print("");
                            printf("The final element is %d\n", e);
                        }
                        Wait(); break;

            case 'G':   IsEnd = 1; break;

            default :   Print("INPUT ERROR\n"); Wait();
        }
    }
    destroyLStack(s);
}

