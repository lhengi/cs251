//
//  main.c
//  lab7
//
//  Created by Heng Li on 10/12/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "math.h"

typedef struct Node
{
    int val;
    struct Node* next;
}Node;

typedef struct list
{
    Node* front;
    Node* back;
}list;

int is_empty(list* lst)
{
    if(lst->front == NULL)
    {
        return 1;
    }
    return 0;
}

void push(list* lst,Node* pTemp)
{
    if(is_empty(lst))
    {
        lst->front = pTemp;
        lst->back = pTemp;
        return;
    }
    lst->back->next = pTemp;
    lst->back = lst->back->next;
}

Node* pop(list* lst)
{
    if(is_empty(lst))
        return NULL;
    //int returnVar = lst->front->val;
    Node* pTemp = lst->front;
    lst->front = lst->front->next;
    return pTemp;
}

list* read_ints()
{
    int x;
    Node* pTemp;
    printf("Type the input:");
    list* input = malloc(sizeof(list));
    while(scanf("%d",&x) == 1)
    {
        pTemp = malloc(sizeof(Node));
        pTemp->val = x;
        pTemp->next = NULL;
        push(input, pTemp);
    }
    printf("\n");
    return input;
}

void print_lst(list* lst)
{
    Node* pTemp = lst->front;
    printf("Print the list\n");
    while(pTemp != NULL)
    {
        printf(" %d ",pTemp->val);
        pTemp = pTemp->next;
    }
    printf("\nEnd of the list\n");
}

int findMax(list* lst)
{
    int max = -1;
    Node* pTemp  = lst->front;
    while (pTemp != NULL)
    {
        if(max < pTemp->val)
            max = pTemp->val;
        pTemp = pTemp->next;
    }
    
    return max;
}

void concat(list* lst1, list* lst2)
{
    if(is_empty(lst1))
    {
        lst1 = lst2;
        return;
    }
    lst1->back->next = lst2->front;
    lst1->back = lst2->back;
}

list* sort_1(list** list2d, int r)
{
    int i;
    for(i = 1; i < r;i++)
    {
        if(!is_empty(list2d[i]))
        {
            concat(list2d[0], list2d[i]);
        }
    }
    return list2d[0];
}

int main(int argc, const char * argv[])
{
    // insert code here...
    
    int r = 10;
    list** array = (list**)malloc(sizeof(list*)*r);
    int k;
    for(k = 0; k < r;k++)
    {
        array[k] = malloc(sizeof(list));
        array[k]->back = NULL;
        array[k]->front = NULL;
    }
    list* input_lst = read_ints();
    print_lst(input_lst);
    int max = findMax(input_lst);
    printf("The max is: %d ",max);
    Node* pTemp = input_lst->front;
    Node* pTemp_head;
    while(!is_empty(input_lst))
    {
        pTemp_head = pop(input_lst);
        push(array[pTemp_head->val%10], pTemp_head);
        pTemp = pTemp->next;
    }
    
    int passes = (int)ceill(log10(max));
    print_lst(array[2]);
    input_lst = sort_1(array, r);
    print_lst(input_lst);
    
    
    
    
    
    
    
    
    return 0;
}
