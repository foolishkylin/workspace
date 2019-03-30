#include <stdio.h>
#include <stdlib.h>
#include "../head/duLinkedList.h"

/**
 *  @name        : Status InitList(LinkList *L);
 *	@description : initialize an empty linked list with only the head node without value
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList(LinkedList *L) {
    (*L) = (LinkedList) malloc(sizeof(LNode));
    if((*L) == NULL){
        printf("ERROR\n");
        return ERROR;
    }
    else{
        (*L)->data = 1;
        (*L)->next = NULL;
        return SUCCESS;
    }
}

/**
 *  @name        : void DestroyList(LinkedList *L)
 *	@description : destroy a linked list, free all the nodes
 *	@param		 : L(the head node)
 *	@return		 : None
 *  @notice      : None
 */
void DestroyList(LinkedList *L) {
    if((*L) == NULL)
    {
        puts("The list is already empty");
    }
    else
    {
        while(*L)
        {
            LinkedList Ptr = (*L)->next;
            free((*L));
            // free the node one by one
            *L = Ptr;
        }
    }
}

/**
 *  @name        : Status InsertList(LNode *p, LNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : Status
 *  @notice      : None
 */
Status InsertList(LNode *p, LNode *q) {
    if(p == NULL)
    {
        puts("ERROR");
        return ERROR;
    }
    LinkedList Ptr = p, InsertPtr = q;
    InsertPtr->next = Ptr->next;
    Ptr->next = InsertPtr;
    //change the order
    return SUCCESS;
}
/**
 *  @name        : Status DeleteList(LNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : Status
 *  @notice      : None
 */
Status DeleteList(LNode *p, ElemType *e) {
    if(p == NULL || p->next == NULL)
    {
        puts("The node is NULL");
        return ERROR;
    }
    LinkedList Ptr = p, PtrCopy = p->next;
    Ptr->next = Ptr->next->next;
    *e = PtrCopy->data;
    free(PtrCopy);
    puts("Delete successfully");
    return SUCCESS;
}

/**
 *  @name        : void TraverseList(LinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : None
 *  @notice      : None
 */
void TraverseList(LinkedList L, void (*visit)(ElemType e)) {
    if(L == NULL)
    {
        puts("You must creat a list first");
        return ;
    }
    for(; L; L = L->next) visit(L->data);
    // visit is a pointer which point to a function
    puts("NULL");
}

/**
 *  @name        : Status SearchList(LinkedList L, ElemType e)
 *	@description : find the first node in the linked list according to e
 *	@param		 : L(the head node), e
 *	@return		 : Status
 *  @notice      : None
 */
Status SearchList(LinkedList L, ElemType e) {
    if(L == NULL)
    {
        puts("You must creat a list first");
        return ERROR;
    }
    int Position = 1;
    while(L && L->data != e) L = L->next, Position++;
    if(L == NULL)
    {
        puts("The node you want to search is not exsiting");
        return ERROR;
    }
    printf("The node is %dth\n", Position);
    // output the position
    return SUCCESS;
}

/**
 *  @name        : Status ReverseList(LinkedList *L)
 *	@description : reverse the linked list
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status ReverseList(LinkedList *L) {
    if(*L == NULL || (*L)->next == NULL)
    {
        puts("The list doesn't need to reverse");
        return ERROR;
    }
    LinkedList Ptr = *L, PtrNext = Ptr->next, Temp = PtrNext->next;
    // use 3 pointer to exchange the nodes
    PtrNext->next = Ptr, Ptr->next = NULL;
    // deal with the head case
    Ptr = PtrNext, PtrNext = Temp;
    while(PtrNext)
    {
        Temp = PtrNext->next;
        PtrNext->next = Ptr;
        Ptr = PtrNext, PtrNext = Temp;
    }
    *L = Ptr;
    puts("The list is already reversed");
    return SUCCESS;
}

/**
 *  @name        : Status IsLoopList(LinkedList L)
 *	@description : judge whether the linked list is looped
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status IsLoopList(LinkedList L) {
    if(L == NULL)
        return ERROR;
    // one is stedy, another is moving
    LinkedList Ptr = L->next;
    while(Ptr->next && L != Ptr) Ptr = Ptr->next;
    if(Ptr == L)return SUCCESS;
    else return ERROR;
}

/**
 *  @name        : LNode* ReverseEvenList(LinkedList *L)
 *	@description : reverse the nodes which value is an even number in the linked list, input: 1 -> 2 -> 3 -> 4  output: 2 -> 1 -> 4 -> 3
 *	@param		 : L(the head node)
 *	@return		 : LNode(the new head node)
 *  @notice      : choose to finish
 */
LNode* ReverseEvenList(LinkedList *L) {
    if(*L == NULL || (*L)->next == NULL)
    {
        puts("It can't be reversed");
        return *L;
    }
    // use 4 pointer to exchange
    LinkedList Ptr1, Ptr2 = *L, Ptr3 = Ptr2->next, Ptr4 = Ptr3->next, CountPtr;
    int Count;
    (*L) = (*L)->next;
    Ptr3->next = Ptr2, Ptr2->next = Ptr4;
    while(1)
    {
        // if the number of node is less than 2, we don't need to do anything
        for(CountPtr = Ptr2, Count = 0; CountPtr->next; CountPtr = CountPtr->next, Count++)
            if(Count == 2)break;
        if(Count < 2) break;
        Ptr1 = Ptr2, Ptr2 = Ptr4, Ptr3 = Ptr2->next, Ptr4 = Ptr3->next;
        Ptr1->next = Ptr3, Ptr3->next = Ptr2, Ptr2->next = Ptr4;
    }
    puts("The list is already reversed");
    return *L;
}

/**
 *  @name        : LNode* FindMidNode(LinkedList *L)
 *	@description : find the middle node in the linked list
 *	@param		 : L(the head node)
 *	@return		 : LNode
 *  @notice      : choose to finish
 */
LNode* FindMidNode(LinkedList *L) {
    if(*L == NULL)
    {
        puts("Please creat a list");
        return NULL;
    }
    LinkedList Ptr = *L, PtrCopy = Ptr;
    int Len = 1, Mid = 0;
    for(;Ptr->next; Ptr = Ptr->next, Len++);
    for(;Mid != Len / 2; PtrCopy = PtrCopy->next, Mid++);
    return PtrCopy;
}
