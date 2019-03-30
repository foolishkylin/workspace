#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"
// return     func name          input
    void        Visit          (ElemType e);
    void        PrintLine      (void);
    void        Wait           (void);
    ElemType    GetKey         (void);
    char        GetOption      (void);
    LinkedList  ListCreat      (void);
    void        Mune           (void);

int main()
{
    Mune();
    system("pause");
    return 0;
}

/**
 *  @name        : void Visit(ElemType e)
 *	@description : print the value
 *	@param		 : e (ElemType)
 *	@return		 : None
 *  @notice      : None
 */
void Visit(ElemType e)
{
    printf("%d-> ",e);
}

/**
 *  @name        : void PrintLine(void)
 *	@description : print to decorate the mune
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
void PrintLine(void)
{
    printf("\n>>> ");
}

/**
 *  @name        : void Wait(void)
 *	@description : get some keys to wait
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
void Wait(void)
{
    PrintLine();
    puts("Enter anything to continue");
    getchar();
    getchar();
}

/**
 *  @name        : ElemType GetKey(void)
 *	@description : get the right value
 *	@param		 : None
 *	@return		 : Element
 *  @notice      : None
 */
ElemType GetKey(void)
{
    char Str[20] = {0};
    ElemType Key;
    PrintLine();
    puts("Please enter a number");
    while(1)
    {
        int IsRight = 1;
        PrintLine();
        scanf("%s",Str);
        for(int bit = 0; Str[bit]; bit++)
            if(Str[bit] < '0' || Str[bit] > '9')
            {
                IsRight = 0;
                break;
            }
        if(!IsRight)
        {
            PrintLine();
            puts("Please enter a right interger");
            continue;
        }
        else
            break;
    }
    Key = atoi(Str);
    return Key;
}

/**
 *  @name        : char GetOption(void)
 *	@description : get the right char
 *	@param		 : None
 *	@return		 : char
 *  @notice      : None
 */
char GetOption(void)
{
    char Option[2];
    PrintLine();
    puts("Plese enter");
    while(1)
    {
        int IsRight = 1;
        PrintLine();
        scanf("%s",Option);
        getchar();
        if(Option[0] < 'A' || Option[0] >'Z' || Option[1] != 0)
            IsRight = 0;
        if(!IsRight)
        {
            PrintLine();
            puts("Please enter a right char");
            continue;
        }
        else
            break;
    }
    return Option[0];
}

/**
 *  @name        : LinkedList ListCreat(void)
 *	@description : creat a list
 *	@param		 : None
 *	@return		 : Head
 *  @notice      : None
 */
LinkedList ListCreat(void)
{
    LinkedList Head = NULL, InsertPtr = NULL, Ptr = NULL;
    PrintLine();
    puts("Please enter the lenth of the list");
    int Len = GetKey() - 1;
    InitList(&Head);
    Ptr = Head;
    Head->data = GetKey();
    while(Len--)
    {
        InsertPtr = (LinkedList) malloc(sizeof(LNode));
        PrintLine();
        printf("Please enter the key value (last %d nodes)\n", Len + 1);
        InsertPtr->data = GetKey(), InsertPtr->next = NULL;
        InsertList(Ptr, InsertPtr);
        Ptr = InsertPtr;
    }
    return Head;
}

/**
 *  @name        : void Mune(void)
 *	@description : call other function and print the mune
 *	@param		 : None
 *	@return		 : None
 *  @notice      : None
 */
void Mune(void)
{
    ElemType D;
    int IsEnd = 0;
    LinkedList Head = NULL, Ptr = NULL, InsertPtr = NULL, PtrTail = NULL;
    while(!IsEnd)
    {
        system("cls");
        char option;
        PrintLine();
        printf("Please select the function as follows\n");
        puts("   A. Creat a List");
        puts("   B. Find a node");
        puts("   C. Delete a node");
        puts("   D. Insert nodes");
        puts("   E. Print the List (Use it to obsert the list)");
        puts("   F. Reverse the List");
        puts("   G. Check that if the List is Loop");
        puts("   H. Reverse the even node");
        puts("   I. Find the mid node");
        puts("   J. Back");
        option = GetOption();
        system("cls");
        switch(option)
        {
            case 'A':   Head = ListCreat(); break;
            case 'B':   SearchList(Head, GetKey()); Wait(); break;

            case 'C':   D = GetKey();
                        if(Head == NULL)
                        {
                            puts("You must creat a list first");
                            Wait(); break;
                        }
                        Ptr = Head;
                        if(D == Head->data)
                        {
                            Head = Head->next;
                            free(Ptr);
                            PrintLine();
                            puts("The node is deleted successfully");
                        }
                        else
                        {
                            while(Ptr->next && Ptr->next->data != D)
                                Ptr = Ptr->next;
                            if(!Ptr->next)
                            {
                                PrintLine();
                                puts("The node you want to delete is not existed");
                            }
                            else
                                DeleteList(Ptr, &D);
                        }
                        Wait(); break;

            case 'D':   if(Head == NULL)
                        {
                            PrintLine();
                            puts("You must creat a list first"); Wait();break;
                        }
                        InsertPtr = (LinkedList) malloc(sizeof(LNode)), PtrTail = Head;
                        for(; PtrTail->next; PtrTail = PtrTail->next);
                        InsertPtr->data = GetKey();
                        InsertList(PtrTail, InsertPtr);
                        Wait(); break;
            case 'E':   PrintLine(); TraverseList(Head, Visit); Wait(); break;
            case 'F':   ReverseList(&Head); Wait(); break;
            case 'G':   if(IsLoopList(Head)) puts("Yes, it is");
                        else puts("No, it isn't");
                        Wait(); break;
            case 'H':   ReverseEvenList(&Head); Wait(); break;
            case 'I':   Ptr = FindMidNode(&Head);
                        if(Ptr != NULL)
                        {
                            PrintLine();
                            printf("The result is %d\n", Ptr->data);
                        }
                        Wait(); break;
            case 'J':   IsEnd = 1; break;
            default :   PrintLine(); puts("INPUT ERROR"); Wait();
        }
    }
    DestroyList(&Head);
}
