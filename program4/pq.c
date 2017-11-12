//
//  pq.c
//  program4
//
//  Created by Heng Li on 11/10/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

#define Left(i) (2*i)
#define Right(i) (2*i+1)
#define Parent(i) (i/2)

typedef struct Node
{
    int id;
    double priority;
}Node;

struct pq_struct
{
    Node** q;
    Node** map;
    int capacity;
    int size;
    int minheap;
};

PQ* pq_create(int capacity, int min_heap)
{
    PQ* pq = malloc(sizeof(PQ));
    pq->map = (Node**)malloc(sizeof(Node*)*(capacity+1));
    pq->q = (Node**)malloc(sizeof(Node*)*(capacity+1));// index 0 is reserved
    pq->capacity = capacity;
    pq->size = 0;
    pq->minheap = min_heap;
    return pq;
}

void pq_free(PQ * pq)
{
    int i;
    for(i = 0; i < pq->capacity +1; i++)
    {
        free(pq->map[i]);
    }
    free(pq->map);
    free(pq->q);
    free(pq);
}

int valid_id(PQ* pq, int id)
{
    if(id <= 0 || id > pq->capacity)
    {
        return 0;
    }
    
    return 1;
}

int percolate_up_min(PQ* pq, int index)
{
    if(pq->minheap == 0)
        return 0;
    if(pq->q[index] == NULL || index <= 1)
    {
        return 0;
    }
    Node* pTemp;
    if(pq->q[Parent(index)]->id > pq->q[index]->id)
    {
        pTemp = pq->q[Parent(index)];
        pq->q[Parent(index)] = pq->q[index];
        pq->q[index] = pTemp;
        percolate_up_min(pq,Parent(index));
        
    }
    return 1;
}

int percolate_up_max(PQ* pq, int index)
{
    if(pq->minheap == 1)
        return 0;
    
    if(pq->q[index] == NULL || index <= 0)
    {
        return 0;
    }
    Node* pTemp;
    if(pq->q[Parent(index)]->id < pq->q[index]->id)
    {
        pTemp = pq->q[Parent(index)];
        pq->q[Parent(index)] = pq->q[index];
        pq->q[index] = pTemp;
        percolate_up_max(pq,Parent(index));
        
    }
    return 1;
}


int pq_insert(PQ * pq, int id, double priority)
{

    if(!valid_id(pq, id) || pq->size + 1 > pq->capacity)
    {
        fprintf(stderr, "**** id out of range\n");
        return 0;
    }
    
    Node* temp = malloc(sizeof(Node));
    temp->id = id;
    temp->priority = priority;
    pq->q[++pq->size] = temp;
    pq->map[id] = temp;
    // Need to perculate up
    percolate_up(pq, pq->size);
    
    
    
    // *******
    return 1;
}


int pq_change_priority(PQ * pq, int id, double new_priority)
{
    if(!valid_id(pq, id) || pq->map[id] == NULL)
    {
        if(pq->map[id] == NULL)
            fprintf(stderr, "**** id not initialized\n");
        else
            fprintf(stderr, "**** id out of range\n");
        return 0;
        
    }
    pq->map[id]->priority = new_priority;
    return 1;
}

int pq_size(PQ * pq)
{
    return pq->size;
}

int pq_capacity(PQ * pq)
{
    return pq->capacity;
}

int pq_remove_by_id(PQ * pq, int id)
{
    if(!valid_id(pq, id))
    {
        fprintf(stderr, "**** id out of range\n");
        return 0;
        
    }
    
    
    return 1;
}


int pq_peek_top(PQ * pq, int *id, double *priority)
{
    if(pq->q[1] == NULL)
    {
        fprintf(stderr, "**** Q is empty\n");
        return 0;
    }
    *id = pq->q[1]->id;
    *priority = pq->q[1]->priority;
    return 1;
}


int pq_delete_top(PQ * pq, int *id, double *priority)
{
    if(!pq_peek_top(pq, id, priority))
        return 0;
    // perculate
    
    return 1;
}

int pq_get_priority(PQ * pq, int id, double *priority)
{
    if(!valid_id(pq, id) || pq->map[id] == NULL)
    {
        if(pq->map[id] == NULL)
            fprintf(stderr, "*** id not initialized\n");
        else
            fprintf(stderr, "*** id out of range\n");
        
        return 0;
    }
    *priority = pq->map[id]->priority;
    return 1;
}















