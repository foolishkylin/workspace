#include <stdio.h>
#include <stdlib.h>
#include "duLinkedList.h"
// return        func name          input
    void          Visit          (ElemType e);
    void          PrintLine      (void);
    void          Wait           (void);
    ElemType      GetKey         (void);
    char          GetOption      (void);
    DuLinkedList  DuListCreat      (void);
    void          Mune           (void);

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
 *  @name        : DuLinkedList DuListCreat(void)
 *	@description : creat a dulist
 *	@param		 : None
 *	@return		 : Head
 *  @notice      : None
 */
DuLinkedList DuListCreat(void)
{
    DuLinkedList Head = NULL, InsertPtr = NULL, Ptr = NULL;
    PrintLine();
    puts("Please enter the lenth of the list");
    int Len = GetKey() - 1;
    InitList_DuL(&Head);
    Ptr = Head;
    Head->data = GetKey();
    while(Len--)
    {
        InsertPtr = (DuLinkedList) malloc(sizeof(DuLNode));
        PrintLine();
        printf("Please enter the key value (last %d nodes)\n", Len + 1);
        InsertPtr->data = GetKey();
        InsertPtr->next = NULL, InsertPtr->prior = NULL;
        InsertAfterList_DuL(Ptr, InsertPtr);
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
    DuLinkedList PtrCurrent = NULL, Ptr = NULL, InsertPtr = NULL, PtrTail = NULL;
    while(!IsEnd)
    {
        system("cls");
        char option;
        PrintLine();
        printf("Please select the function as follows\n");
        puts("   A. Creat a DuList");
        puts("   B. Delete a node");
        puts("   C. Insert node after");
        puts("   D. Print the List");
        puts("   E. Destroy the List");
        puts("   F. Back");
        option = GetOption();
        system("cls");
        switch(option)
        {
            case 'A':   PtrCurrent = DuListCreat(); break;
            case 'B':   D = GetKey();
                        if(PtrCurrent == NULL)
                        {
                            puts("You must creat a list first");
                            Wait(); break;
                        }
                        Ptr = PtrCurrent;
                        if(D == PtrCurrent->data)
                        {
                            if(PtrCurrent->next == NULL)
                            {
                                PtrCurrent = PtrCurrent->next;
                            }
                            else
                            {
                                PtrCurrent = PtrCurrent->next;
                                PtrCurrent->prior = NULL;
                            }
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
                                DeleteList_DuL(Ptr, &D);
                        }
                        Wait(); break;

            case 'C':   if(PtrCurrent == NULL)
                        {
                            PrintLine();
                            puts("You must creat a list first"); Wait();break;
                        }
                        InsertPtr = (DuLinkedList) malloc(sizeof(DuLNode)), PtrTail = PtrCurrent;
                        for(; PtrTail->next; PtrTail = PtrTail->next);
                        InsertPtr->data = GetKey();
                        InsertAfterList_DuL(PtrTail, InsertPtr);
                        Wait(); break;
            case 'D':   TraverseList_DuL(PtrCurrent, Visit); Wait(); break;
            case 'E':   DestroyList_DuL(&PtrCurrent); Wait(); break;
            case 'F':   IsEnd = 1; break;
            default :   PrintLine(); puts("INPUT ERROR"); Wait();
        }
    }
}
