//
//  sq.c
//  cs251
//
//  Created by Heng Li on 10/01/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
//#include "list.h"
// self defining everything needed
#include "sq.h"

/****************************************************/
// Get all the llist.c's methods

typedef struct node {
    int val;
    struct node* next;
    struct node* pre;
}Node;


typedef struct list_struct {
    Node *front;
    Node *back;
    
}LIST;


LIST *lst_create() {
    LIST *l = malloc(sizeof(LIST));
    
    l->front = NULL;
    l->back = NULL;
    return l;
}

int lst_is_empty(LIST *l) {
    return l->front == NULL;
}

void lst_print(LIST *l) {
    Node *p = l->front;
    
    printf("[");
    while(p != NULL) {
        printf(FORMAT, p->val);
        p = p->next;
    }
    printf("]\n");
}

void lst_free(LIST *l) {
    Node *p = l->front;
    Node *pnext;
    
    while(p != NULL) {
        pnext = p->next;   // keeps us from de-referencing a freed ptr
        free(p);
        p = pnext;
    }
    // now free the LIST
    free(l);
}

// take a node then push it to the front of the list
void lst_push_front(LIST* l, Node* pTemp)
{
    if(lst_is_empty(l))
    {
        l->front = pTemp;
        l->back = pTemp;
        return;
    }
    pTemp->next = l->front;
    l->front->pre = pTemp;
    l->front = pTemp;
    
}

/*
void lst_push_front(LIST *l, int val) {
    Node *p = malloc(sizeof(Node));
    
    p->val = val;
    p->next = l->front;
    
    l->front = p;
    if(l->back == NULL)   // was empty, now one elem
        l->back = p;
    l->size += 1;
}*/

void lst_push_back(LIST* l, Node* pTemp)
{
    if(lst_is_empty(l))
    {
        lst_push_front(l, pTemp);
        return;
    }
    l->back->next = pTemp;
    pTemp->pre = l->back;
    l->back = l->back->next;
}


/*
void lst_push_back(LIST *l, int val) {
    Node *p;
    
    if(l->back == NULL)   // list empty - same as push_front
        lst_push_front(l, val);
    else {  // at least one element before push
        p = malloc(sizeof(Node));
        p->val = val;
        p->next = NULL;
        l->back->next = p;
        
        l->back = p;
        l->size +=1;
    }
    
}*/

Node* lst_pop_front(LIST* l)
{
    Node* pTemp = l->front;
    l->front = l->front->next;
    l->front->pre = NULL;
    
    pTemp->next = NULL;
    pTemp->pre = NULL;
    return pTemp;
}

Node* lst_pop_back(LIST* l)
{
    Node* pTemp = l->back;
    l->back = l->back->pre;
    l->back->next = NULL;
    
    pTemp->pre = NULL;
    
    return pTemp;
}

struct service_queue {
    LIST * the_queue;
    LIST * buzzer_bucket;
    Node** array;
    int que_length;
    int capacity;
};

/**
 * Function: sq_create()
 * Description: creates and intializes an empty service queue.
 * 	It is returned as an SQ pointer.
 */
SQ * sq_create()
{
    SQ *q;
    
    q = malloc(sizeof(SQ));
    
    q->the_queue = lst_create();
    q->buzzer_bucket = lst_create();
    q->que_length = 0;
    q->array = (Node**)malloc(sizeof(Node*)*8)
    q->capacity = 8;
    return q;
}



/**
 * Function: sq_free()
 * Description:  see sq.h
 *
 * RUNTIME REQUIREMENT:  O(N_t)  where N_t is the number of buzzer
 *	IDs that have been used during the lifetime of the
 *	service queue; in general, at any particular instant
 *	the actual queue length may be less than N_t.
 *
 *	[See discussion of in header file]
 *
 * RUNTIME ACHIEVED:  ???
 *
 */
void sq_free(SQ *q)
{
    
    lst_free(q->the_queue);
    lst_free(q->buzzer_bucket);
    free(q->array);
    
    free(q);
}



/**
 * Function: sq_display()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(N)  (N is the current queue length).
 * ACHIEVED RUNTIME:  O(N)  YAY!!
 */
void sq_display(SQ *q) {
    
    printf("current-queue contents:\n    ");
    lst_print(q->the_queue);
    printf("\n");
}


/**
 * Function: sq_length()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 * ACHIEVED RUNTIME:  ???
 */
int  sq_length(SQ *q) {
    return q->que_length;
}

void growArray(SQ* q)
{
    Node** newArray = (Node**)malloc(sizeof(Node*)*q->capacity*2);
    int i;
    
    for(i = 0; i < q->capacity; i++)
    {
        newArray[i] = q->array[i];
    }
    q->capacity *= 2;
    
    q->array = newArray;
    free(newArray);
    
    
}

//give buzzer to the customer
//return the buzzer id that was handed to the customer
int  sq_give_buzzer(SQ *q)
{
    // grow the array
    if(q->que_length >= q->capacity)
    {
        growArray(q);
    }
    
    int buzzerId;
    Node* pTemp;
    
    // when all the buzzers are in use
    if(lst_is_empty(q->buzzer_bucket))
    {
        buzzerId = q->que_length;
        pTemp = malloc(sizeof(Node));
        pTemp->val = buzzerId;
    }
    else// take buzzer from the bucket
    {
        pTemp = lst_pop_front(q->buzzer_bucket);
    }
    
    lst_push_back(q->the_queue, pTemp);
    // add to the array
    q->array[buzzerId] = pTemp;
    
    q->que_length++;
    return buzzerId;
    
}

int sq_seat(SQ* q)
{
    if(lst_is_empty(q->the_queue))
    {
        return -1;
    }
    
    Node* pTemp = lst_pop_front(q->the_queue);
    lst_push_back(q->buzzer_bucket, pTemp);
    q->que_length--;
    q->array[pTemp->val] = NULL;
    return pTemp->val;
    
}

int sq_kick_out(SQ* q, int buzzerId)
{
    if(buzzerId >= q->capacity || q->array[buzzerId] == NULL)
    {
        return 0;
    }
    
    q->array[buzzerId]->pre = q->array[buzzerId]->next;
    
    lst_push_back(q->buzzer_bucket, q->array[buzzerId]);
    q->array[buzzerId] = NULL;
    q->que_length--;
    
    return 1;
}










