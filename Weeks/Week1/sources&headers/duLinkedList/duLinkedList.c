#include <stdio.h>
#include <stdlib.h>
#include "../head/duLinkedList.h"

/**
 *  @name        : Status InitList_DuL(DuLinkedList *L)
 *	@description : initialize an empty linked list with only the head node
 *	@param		 : L(the head node)
 *	@return		 : Status
 *  @notice      : None
 */
Status InitList_DuL(DuLinkedList *L) {
    (*L) = (DuLinkedList) malloc(sizeof(DuLNode));
    if((*L) == NULL){
        printf("ERROR\n");
        return ERROR;
    }
    else{
        (*L)->data = 1;
        (*L)->prior = NULL;
        (*L)->next = NULL;
        return SUCCESS;
    }
}

/**
 *  @name        : void DestroyList_DuL(DuLinkedList *L)
 *	@description : destroy a linked list
 *	@param		 : L(the head node)
 *	@return		 : status
 *  @notice      : None
 */
void DestroyList_DuL(DuLinkedList *L) {
    if((*L) == NULL)
    {
        puts("The list is already empty");
    }
    else
    {
        while(*L)
        {
            DuLinkedList Ptr = (*L)->next;
            free((*L));
            // free the node one by one
            *L = Ptr;
        }
        puts("The list is already destroied");
    }
    return SUCCESS;
}

/**
 *  @name        : Status InsertBeforeList_DuL(DuLNode *p, LNode *q)
 *	@description : insert node q before node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertBeforeList_DuL(DuLNode *p, DuLNode *q) {
    if(p == NULL || q == NULL)
    {
        puts("ERROR");
        return ERROR;
    }
    DuLinkedList Ptr = p, InsertPtr = q;
    if(Ptr->prior == NULL)
    // if Ptr's next node is empty
    {
        InsertPtr->prior = NULL;
        InsertPtr->next = Ptr;
        Ptr->prior = InsertPtr;
    }
    else
    {
        Ptr->prior->next = InsertPtr;
        InsertPtr->prior = Ptr->prior;
        InsertPtr->next = Ptr;
        Ptr->prior = InsertPtr;
    }
    puts("Insert successfully");
    return SUCCESS;
}

/**
 *  @name        : Status InsertAfterList_DuL(DuLNode *p, DuLNode *q)
 *	@description : insert node q after node p
 *	@param		 : p, q
 *	@return		 : status
 *  @notice      : None
 */
Status InsertAfterList_DuL(DuLNode *p, DuLNode *q) {
    if(p == NULL || q == NULL)
    {
        puts("ERROR");
        return ERROR;
    }
    DuLinkedList Ptr = p, InsertPtr = q;
    if(Ptr->next == NULL)
    {
        InsertPtr->next = NULL;
        Ptr->next = InsertPtr;
        InsertPtr->prior = Ptr;
    }
    else
    {
        Ptr->next->prior = InsertPtr;
        InsertPtr->next = Ptr->next;
        Ptr->next = InsertPtr;
        InsertPtr->prior = Ptr;
    }
    puts("Insert successfully");
    return SUCCESS;
}

/**
 *  @name        : Status DeleteList_DuL(DuLNode *p, ElemType *e)
 *	@description : delete the first node after the node p and assign its value to e
 *	@param		 : p, e
 *	@return		 : status
 *  @notice      : None
 */
Status DeleteList_DuL(DuLNode *p, ElemType *e) {
    if(p == NULL || p->next == NULL)
    {
        puts("The node is NULL");
        return ERROR;
    }
    DuLinkedList Ptr = p, PtrDel = p->next;
    if(PtrDel->next == NULL)
    // if the ptrdel's next node is empty
        Ptr->next = NULL;
    else
    {
        PtrDel->next->prior = Ptr;
        Ptr->next = PtrDel->next;
    }
    *e = PtrDel->data;
    free(PtrDel);
    puts("Delete successfully");
    return SUCCESS;
}

/**
 *  @name        : void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e))
 *	@description : traverse the linked list and call the funtion visit
 *	@param		 : L(the head node), visit
 *	@return		 : Status
 *  @notice      : None
 */
void TraverseList_DuL(DuLinkedList L, void (*visit)(ElemType e)) {
    if(L == NULL)
    {
        puts("You must creat a list first");
        return ;
    }
    DuLinkedList Ptr = L;
    puts("To behind");
    for(; L; L = L->next) visit(L->data);
    // visit is a pointer which point to a function
    puts("NULL");
    puts("To front");
    for(; Ptr; Ptr = Ptr->prior) visit(Ptr->data);
    puts("NULL");

}

