#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LQueue.h"

void Print(char *str);        // print some char with decoration
void Wait(void);              // get some space to stop
void *GetKey(char type);        // get the right value
char GetOption(void);         // get the right char
char GetType(void);            // get the type of data
int GetSize(char type);         // get the size of the type
void Menu(void);              // print the menu and call the functions

char CType;                 // show the type

int main()
{
    Menu();

    return 0;
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

void *GetKey(char type)
{
    void *key = NULL;
    int *Icopy = (int *)malloc(sizeof(int));
    float *Fcopy = (float *)malloc(sizeof(float));
    char *Scopy = (char *)malloc(sizeof(char) * 20);
    Print("Please enter a value\n");
    switch (type)
    {
        case 'I':       while (1)
                        {
                            Print("");
                            if(scanf("%d", Icopy) == 1)
                                break;
                            else
                            {
                                Print("Input ERROR\n");
                                while(getchar() != '\n');
                            }
                        };
                        key = (void *)Icopy; break;

        case 'F':       while (1)
                        {
                            Print("");
                            if(scanf("%f", Fcopy) == 1)
                                break;
                            else
                            {
                                Print("Input ERROR\n");
                                while(getchar() != '\n');
                            }
                        };
                        key = (void *)Fcopy; break;

        case 'C':

        case 'S':       while (1)
                        {
                            Print("");
                            if (scanf("%20s",Scopy) != 1)
                            {
                                Print("Input ERROR\n");
                                continue;
                            }
                            else
                                break;
                        }
                        key = (void *)Scopy; break;

        default:    Print("ERROR\n");
    }
    while(getchar() != '\n');
    if (type != 'I')
        free(Icopy);
    if (type != 'F')
        free(Fcopy);
    if (type != 'C' && type != 'S')
        free(Scopy);
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

char GetType(void)
{
    char type;
    int Isend = 0;
    while(!Isend)
    {
        system("cls");
        char option;
        Print("Please select the type of queue\n\n");
        puts("   A. int");
        puts("   B. float");
        puts("   C. char");
        puts("   D. string(no more than 20 chars)");
        option = GetOption();
        system("cls");
        switch(option)
        {
            case 'A':   type = 'I';
                        Isend = 1; break;

            case 'B':   type = 'F';
                        Isend = 1; break;

            case 'C':   type = 'C';
                        Isend = 1; break;

            case 'D':   type = 'S';
                        Isend = 1; break;

            default :   Print("INPUT ERROR\n");
        }
    }

    CType = type;
    return type;
}

int GetSize(char type)
{
    int size;
    switch (type)
    {
        case 'I':   size = sizeof(int); break;

        case 'F':   size = sizeof(float); break;

        case 'C':   size = sizeof(char); break;

        case 'S':   size = 0; break;

        default :   Print("INPUT ERROR\n");
    }

    return size;
}

void Menu(void)
{
    int IsEnd = 0, times;
    int *I; float *F; char *C; void *data;
    LQueue Q;
    while(!IsEnd)
    {
        system("cls");
        char option;
        Print("Please select the function as follows\n\n");
        puts("   A. Create/Recreate a queue");
        puts("   B. Destroy the queue");
        puts("   C. Clean the queue");
        puts("   D. Get the length of queue");
        puts("   E. Enqueue");
        puts("   F. Get the head element");
        puts("   G. Dequeue");
        puts("   H. Traverse the queue");
        puts("   I. Return");
        option = GetOption();
        system("cls");
        switch(option)
        {
            case 'A':   InitLQueue(&Q);
                        Wait(); break;

            case 'B':   DestoryLQueue(&Q);
                        Wait(); break;

            case 'C':   ClearLQueue(&Q);
                        Wait(); break;

            case 'D':   if (LengthLQueue(&Q) != -1)
                        {
                            Print("");
                            printf("The length of it is %d\n", LengthLQueue(&Q));
                        }
                        Wait(); break;

            case 'E':   Print("Please enter the number of the element you want to enqueue\n");
                        while (1)
                        {
                            Print("");
                            if(scanf("%d", &times) == 1 && times > 0)
                                break;
                            else
                            {
                                Print("Input ERROR\n");
                                while(getchar() != '\n');
                            }
                        }
                        while (times--)
                        {
                            Print("");
                            printf("Last %d value\n", times + 1);
                            data = GetKey(CType);
                            if(!EnLQueue(&Q, data))
                                break;
                        }
                        Wait(); break;

            case 'F':   if (GetHeadLQueue(&Q, data))
                        {
                            Print("");
                            switch (CType)
                            {
                                case 'I':   I = (int *)data;   printf("The first element is %d\n", *I); break;

                                case 'F':   F = (float *)data; printf("The first element is %f\n", *F);  break;

                                case 'C':   C = (char *)data;  printf("The first element is %c\n", *C); break;

                                case 'S':   C = (char *)data;  printf("The first element is %s\n", C); break;

                                default:    Print("ERROR\n");
                            }


                        }
                        Wait(); break;

            case 'G':   DeLQueue(&Q);
                        Wait(); break;

            case 'H':   TraverseLQueue(&Q, LPrint);
                        Wait(); break;

            case 'I':   IsEnd = 1; break;

            default :   Print("INPUT ERROR\n"); Wait();
        }
    }
    DestoryLQueue(&Q);
}
