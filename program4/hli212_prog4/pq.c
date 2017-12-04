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
    int index;
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
    int i;
    for(i = 0; i < capacity+1;i++)
    {
        pq->map[i] = NULL;
        pq->q[i] = NULL;
    }
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
    if(id < 0 || id >= pq->capacity)
    {
        return 0;
    }
    
    return 1;
}

int percolate_up_min(PQ* pq, int index)
{
    if(pq->minheap == 0)
        return 0;
    if(pq->q[index] == NULL || index <= 0)
    {
        return 0;
    }
    
    Node* temp;
    if(!(Parent(index)<= 0 || index <= 0 ) && pq->q[index]->priority < pq->q[Parent(index)]->priority)
    {
        temp = pq->q[Parent(index)];
        pq->q[Parent(index)] = pq->q[index];
        pq->q[Parent(index)]->index = Parent(index);
        pq->q[index] = temp;
        pq->q[index]->index = index;
        
        percolate_up_min(pq, Parent(index));
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
    
    Node* temp;
    if(!(Parent(index) <= 0 || index <= 0 ) && pq->q[index]->priority > pq->q[Parent(index)]->priority)
    {
        temp = pq->q[Parent(index)];
        pq->q[Parent(index)] = pq->q[index];
        pq->q[Parent(index)]->index = Parent(index);//correct the index
        
        pq->q[index] = temp;
        pq->q[index]->index = index;
        
        percolate_up_max(pq, Parent(index));
    }
    return 1;
}

int percolate_up(PQ* pq, int index)
{
    if(pq->minheap)
        return percolate_up_min(pq, index);
    return percolate_up_max(pq, index);
    
}

int percolate_down_min(PQ* pq, int index)
{
    if(pq->minheap == 0)
        return 0;
    if(pq->q[index] == NULL || index <= 0)
    {
        return 0;
    }
    Node* temp;
    // Then compare too
    int nextChild;
    // need to check for NUll
    
    if(pq->q[Left(index)] == NULL || pq->q[Right(index)] == NULL || Right(index) > pq->size || Left(index) > pq->size) // handle if children = NULL
    {
        if((pq->q[Left(index)] == NULL &&  pq->q[Right(index)] == NULL) || (Right(index) > pq->size && Left(index) > pq->size))
            return 1;
        if(pq->q[Left(index)] != NULL || Left(index) <= pq->size)
            nextChild = Left(index);
        else
            nextChild = Right(index);
        
    }
    else
    {
        if(pq->q[Left(index)]->priority < pq->q[Right(index)]->priority)
        {
            nextChild = Left(index);
        }
        else
        {
            nextChild = Right(index);
        }
    }
    
    if(pq->q[nextChild] == NULL)
        return 1;
    
    if(pq->q[nextChild]->priority < pq->q[index]->priority)
    {
        temp = pq->q[nextChild];
        pq->q[nextChild] = pq->q[index];
        pq->q[nextChild]->index = nextChild;
        
        pq->q[index] = temp;
        pq->q[index]->index = index;
        
        percolate_down_min(pq, nextChild);
    }
    
    return 1;
}

int percolate_down_max(PQ* pq, int index)
{
    if(pq->minheap == 1)
        return 0;
    if(pq->q[index] == NULL || index <= 0)
    {
        return 0;
    }
    Node* temp;
    // Then compare too
    int nextChild;
    Node* parent = pq->q[index];
    Node* left =pq->q[Left(index)];
    Node* right =pq->q[Right(index)];
    
    if(pq->q[Left(index)] == NULL || pq->q[Right(index)] == NULL || Right(index) > pq->size || Left(index) > pq->size) // handle if children = NULL
    {
        if((pq->q[Left(index)] == NULL &&  pq->q[Right(index)] == NULL) || (Right(index) > pq->size && Left(index) > pq->size))
            return 1;
        if(pq->q[Left(index)] != NULL || Left(index) <= pq->size)
            nextChild = Left(index);
        else
            nextChild = Right(index);
        
    }
    else
    {
        
    
        if(pq->q[Left(index)]->priority > pq->q[Right(index)]->priority)
        {
            nextChild = Left(index);
        }
        else
        {
            nextChild = Right(index);
        }
    }
    if(pq->q[nextChild] == NULL)
        return 1;
    
    if(pq->q[nextChild]->priority > pq->q[index]->priority)
    {
        temp = pq->q[nextChild];
        pq->q[nextChild] = pq->q[index];
        pq->q[nextChild]->index = nextChild;
        
        pq->q[index] = temp;
        pq->q[index]->index = index;
        
        percolate_down_max(pq, nextChild);
    }
    
    return 1;
}

int percolate_down(PQ* pq, int index)
{
    if(pq->minheap == 1)
        return percolate_down_min(pq, index);
    return percolate_down_max(pq, index);
    
}

int valid_heap_min(PQ* pq, int index)
{
    if(pq->q[index] == NULL)
    {
        return 1;
    }
    
    if(pq->q[Left(index)] != NULL&& Left(index) <= pq->size &&  pq->q[Left(index)]->priority < pq->q[index]->priority)
    {
        fprintf(stderr, "**** invalid min heap, Left child is less than parent,\n");
        fprintf(stderr, "Left child ID: %d\tParent ID: %d\n",Left(index),index);
        fprintf(stderr, "Left priority: %lf\tParent priority: %lf\n",pq->q[Left(index)]->priority,pq->q[index]->priority);
        return 0;
    }
    else if(pq->q[Right(index)] != NULL && Right(index) <= pq->size && pq->q[Right(index)]->priority < pq->q[index]->priority)
    {
        fprintf(stderr, "**** invalid min heap, Right child is less than parent,\n");
        fprintf(stderr, "Right child ID: %d\tParent ID: %d\n",Right(index),index);
        fprintf(stderr, "Right priority: %lf\tParent priority: %lf\n",pq->q[Right(index)]->priority,pq->q[index]->priority);
        return 0;
        
    }
    
    return valid_heap_min(pq, Left(index)) && valid_heap_min(pq, Right(index));
    
}

int valid_heap_max(PQ* pq, int index)
{
    
    if(pq->q[index] == NULL)
    {
        return 1;
    }
    
    if(pq->q[Left(index)] != NULL && Left(index) <= pq->size && pq->q[Left(index)]->priority > pq->q[index]->priority)
    {
        fprintf(stderr, "**** invalid min heap, Left child is less than parent,\n");
        fprintf(stderr, "Left child ID: %d\tParent ID: %d\n",Left(index),index);
        fprintf(stderr, "Left priority: %lf\tParent priority: %lf\n",pq->q[Left(index)]->priority,pq->q[index]->priority);
        return 0;
    }
    else if(pq->q[Right(index)] != NULL && Right(index) <= pq->size && pq->q[Right(index)]->priority > pq->q[index]->priority)
    {
        fprintf(stderr, "**** invalid min heap, Right child is less than parent,\n");
        fprintf(stderr, "Right child ID: %d\tParent ID: %d\n",Right(index),index);
        fprintf(stderr, "Right priority: %lf\tParent priority: %lf\n",pq->q[Right(index)]->priority,pq->q[index]->priority);
        return 0;
        
    }
    
    return valid_heap_max(pq, Left(index)) && valid_heap_max(pq, Right(index));
    
}

int valid_heap(PQ* pq)
{
    if(pq->minheap)
    {
        return valid_heap_min(pq, 1);
    }
    
    return valid_heap_max(pq, 1);
    
}

void display_heap(PQ* pq)
{
    
    int n = pq->size;
    int n_cap = pq->capacity;
    
    int i;
    for(i = 1; i <= n; i++)
    {
        
        printf("ID: %d,\tPriority: %lf\tindex: %d\n",pq->q[i]->id,pq->q[i]->priority,i);
    }
    
    printf("========End of display the heap========\n");
    
    for(i = 0; i<= n_cap; i++)
    {
        if(pq->map[i] == NULL)
        {
            printf("ID: %d,\tNULL\n",i);
        }
        else
        {
            printf("ID: %d,\tPriority: %lf\n",i,pq->map[i]->priority);
        }
    }
    printf("*** End of display\n");
    
    
}



int pq_insert(PQ * pq, int id, double priority)
{

    if(!valid_id(pq, id) || pq->size + 1 > pq->capacity)
    {
        fprintf(stderr, "**** id out of range\n");
        return 0;
    }
    
    if(pq->map[id] != NULL)
    {
        fprintf(stderr, "*** id already exist,to change priority call change priority function\n");
        return 0;
    }
    
    
    Node* temp = malloc(sizeof(Node));
    temp->id = id;
    temp->index = pq->size + 1;
    temp->priority = priority;
    pq->q[++pq->size] = temp;
    pq->map[id] = temp;
    
    // Need to perculate up and down
    percolate_up(pq, pq->size);
    percolate_down(pq, temp->index);
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
    
    // percolate up and down
    percolate_up(pq, pq->map[id]->index);
    percolate_down(pq, pq->map[id]->index);
    
    
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
    if(!valid_id(pq, id)  )
    {
        fprintf(stderr, "**** id out of range\n");
        return 0;
    }
    
    if (pq->map[id] == NULL)
    {
        return 1;
    }
    
    int delete_index = pq->map[id]->index;
    pq->map[id] = NULL;
    free(pq->q[delete_index]);
    pq->q[delete_index] = NULL;
    
    
    if(delete_index == pq->size)
    {
        pq->size--;
        return 1; // deleted last item, no need to percolate
    }
    
    pq->q[delete_index] = pq->q[pq->size];
    pq->size--;
    
    
    Node* pTemp = pq->q[delete_index];
    pTemp->index = delete_index;
    
    percolate_up(pq, delete_index);
    percolate_down(pq, pTemp->index);
    
    
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
    
    int delete_id = pq->q[1]->id;
    pq->map[delete_id] = NULL;
    
    free(pq->q[1]);
    pq->q[1] = NULL;
    
    
    
    pq->q[1] = pq->q[pq->size];
    if(pq->size == 1)
    {
        // this means the top is the last thing in the heap
        free(pq->q[1]);
        pq->q[1] = NULL;
        pq->size--;
        return 1;
    }
    Node* pTemp = pq->q[1];
    pTemp->index = 1;
    pq->q[pq->size] = NULL;
    pq->size--;
    
    percolate_up(pq, 1);
    percolate_down(pq, pTemp->index);
    
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













