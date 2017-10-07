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
    int i = 0;
    printf("[");
    while(p != NULL) {
        printf(" %d", p->val);
        p = p->next;
        if(i > 999)
            break;
        i++;
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
    pTemp->next = NULL;
    pTemp->pre = NULL;
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


void lst_push_back(LIST* l, Node* pTemp)
{
    pTemp->next = NULL;
    pTemp->pre = NULL;
    if(lst_is_empty(l))
    {
        lst_push_front(l, pTemp);
        return;
    }
    l->back->next = pTemp;
    pTemp->pre = l->back;
    l->back = pTemp;
}



Node* lst_pop_front(LIST* l)
{
    Node* pTemp = l->front;
    l->front = l->front->next;
    if(l->front != NULL)
    {
        l->front->pre = NULL;
    }
    
    if(l->front == NULL)
    {
        l->back = NULL;
    }
    
    
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
    q->array = (Node**)malloc(sizeof(Node*)*8);
    int i;
    for(i = 0; i < 8; i++)
    {
        q->array[i] = NULL;
    }
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
    /*
    printf("Current bucket:\n   ");
    lst_print(q->buzzer_bucket);
    printf("\n");
    
    printf("Array:\n");
    int* arrayCopy = malloc(sizeof(int)* q->capacity);
    int i;
    for(i = 0; i < q->capacity;i++)
    {
        if(q->array[i] != NULL)
        {
            arrayCopy[i] = q->array[i]->val;
        }
        else
        {
            arrayCopy[i] = -1;
        }
        printf(" %d ",arrayCopy[i]);
        
    }
    printf("End Array***\n");
     */
}


/**
 * Function: sq_length()
 * Description:  see sq.h
 *
 * REQUIRED RUNTIME:  O(1)
 * ACHIEVED RUNTIME:  O(1)
 */
int  sq_length(SQ *q) {
    return q->que_length;
}

void growArray(SQ* q)
{
    Node** newArray = (Node**)malloc(sizeof(Node*)*q->capacity*2);
    //Node newArray[][];
    int i;
    Node* pTemp;
    for(i = 0; i < q->capacity * 2; i++)
    {
        newArray[i] = NULL;
        pTemp = newArray[i];
    }
    
    for(i = 0; i < q->capacity;i++)
    {
        newArray[i] = q->array[i];
        pTemp = newArray[i];
    }
    q->capacity *= 2;
    q->array = newArray;
    
    
    
}

//give buzzer to the customer
//return the buzzer id that was handed to the customer
// required runtime:  O(1)
// Achived runtime:   O(1)
// using array of Node*
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
        pTemp->pre = NULL;
        pTemp->next = NULL;
        lst_push_back(q->the_queue, pTemp);
        // add to the array
        q->array[buzzerId] = pTemp;
        
        q->que_length++;
        return buzzerId;
    }
    
    // take buzzer from the bucket
    pTemp = lst_pop_front(q->buzzer_bucket);
    buzzerId = pTemp->val;
    pTemp->pre = NULL;
    pTemp->next = NULL;
    lst_push_back(q->the_queue, pTemp);
    // add to the array
    q->array[buzzerId] = pTemp;
    
    q->que_length++;
    return buzzerId;
    
}

// required runtime:  O(1)
// Achived runtime:   O(1)

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


// required runtime:  O(1)
// Achived runtime:   O(1)
int sq_kick_out(SQ* q, int buzzerId)
{

    
    if(buzzerId >= q->capacity || q->array[buzzerId] == NULL)
    {
        fprintf(stderr, "The buzzer does not exist\n");
        return 0;
    }
    
    if(q->array[buzzerId] == NULL)
    {
        fprintf(stderr, "The buzzer is not in the queue\n");
        return 0;
    }
    if(q->array[buzzerId]->pre == NULL)
    {
        lst_push_back(q->buzzer_bucket, lst_pop_front(q->the_queue));
        q->array[buzzerId] = NULL;
        q->que_length--;
        return 1;
    }
    Node* pTemp = q->array[buzzerId];
    Node* prepTemp = pTemp->pre;
    if(pTemp->next == NULL)// if next is null, then this is the tail
    {
        q->the_queue->back = prepTemp;
        prepTemp->next = NULL;
    }
    else
    {
        prepTemp->next = pTemp->next;
        pTemp->next->pre = prepTemp;// updating pre of next
    }
    
    lst_push_back(q->buzzer_bucket, q->array[buzzerId]);
    q->array[buzzerId] = NULL;
    q->que_length--;
    
    return 1;
}   


// required runtime:  O(1)
// Achived runtime:   O(1)
int sq_take_bribe(SQ *q, int buzzerId)
{
    if(buzzerId >= q->capacity || q->array[buzzerId] == NULL)
    {
        fprintf(stderr, "The buzzer does not exist\n");
        return 0;
    }
    
    if(q->array[buzzerId] == NULL)
    {
        fprintf(stderr, "The buzzer is not in the queue\n");
        return 0;
    }
    
    // if the id is the head of the list, just return
    // because there's no need
    if(q->array[buzzerId]->pre == NULL)
        return 1;
    
    Node* pTemp = q->array[buzzerId];
    Node* prepTemp = q->array[buzzerId]->pre;
    if(q->array[buzzerId]->next == NULL)
    { // handle if the buzzer is at the end of the list
        q->the_queue->back = q->the_queue->back->pre;// move up the back pointer
        //q->the_queue->back->next = NULL;// set back pointer next to null
    }
    else
    {
        pTemp->next->pre = prepTemp;// update the next's pre
    }
    prepTemp->next = pTemp->next;
    //q->array[buzzerId]->pre->next = q->array[buzzerId]->next;
    
    lst_push_front(q->the_queue, q->array[buzzerId]);
    
    return 1;
}








