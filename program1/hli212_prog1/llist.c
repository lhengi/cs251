#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#include <time.h>
#define FREE(x) lst_free(x)

/**
 * See list.h for expected behavior of functions
 **/

typedef struct node {
    ElemType val;
    struct node *next;
} NODE;


struct list_struct {
    
    NODE *front;
    NODE *back;
    int size;
};


/*
 * returns pointer to newly created empty list
 */
LIST *lst_create() {
    LIST *l = malloc(sizeof(LIST));
    
    l->front = NULL;
    l->back = NULL;
    l->size = 0;
    return l;
}

void lst_free(LIST *l) {
    NODE *p = l->front;
    NODE *pnext;
    
    while(p != NULL) {
        pnext = p->next;   // keeps us from de-referencing a freed ptr
        free(p);
        p = pnext;
    }
    // now free the LIST
    free(l);
}

void lst_print(LIST *l) {
    NODE *p = l->front;
    
    printf("[");
    while(p != NULL) {
        printf(FORMAT, p->val);
        p = p->next;
    }
    printf("]\n");
}


/**
 * TODO:
 *   function:  lst_are_equal
 *   description:  returns true(1) if lst1 and lst2
 *      contain exactly the same sequenc of values.
 *      Returns 0 otherwise.
 **/
int lst_are_equal(LIST *lst1, LIST *lst2)
{
    NODE* pTemp1 = lst1->front;
    NODE* pTemp2 = lst2->front;
    
    while(pTemp1 != NULL || pTemp2 != NULL)
    {
        if(pTemp1->val != pTemp2->val)
        {
            return 0;
        }
        pTemp2 = pTemp2->next;
        pTemp1 = pTemp1->next;
        
    }
    
    if(pTemp2 != NULL || pTemp1 != NULL)
        return 0;
    
    
    return 1;
    
}

/**
 * TODO:  print in reverse order
 *
 * Try to do without looking at notes!
 * Hints:  recursive helper function
 */
void lst_print_rev_node(NODE* pTemp)
{
    if(pTemp == NULL)
    {
        return;
    }
    
    lst_print_rev_node(pTemp->next);
    printf("\t%d",pTemp->val);
}
void lst_print_rev(LIST *l)
{
    lst_print_rev_node(l->front);
    printf("\n");
}


void lst_push_front(LIST *l, ElemType val) {
    NODE *p = malloc(sizeof(NODE));
    
    p->val = val;
    p->next = l->front;
    
    l->front = p;
    if(l->back == NULL)   // was empty, now one elem
        l->back = p;
    l->size += 1;
}

void lst_push_back(LIST *l, ElemType val) {
    NODE *p;
    
    if(l->back == NULL)   // list empty - same as push_front
        lst_push_front(l, val);
    else {  // at least one element before push
        p = malloc(sizeof(NODE));
        p->val = val;
        p->next = NULL;
        l->back->next = p;
        
        l->back = p;
        l->size +=1;
    }
    
}

/** TODO
 *   modifications to enable this operation
 *   to execute in O(1) time.  (You will almost
 *   certainly modify other functions and the
 *   data structure itself -- see header).
 **/
int lst_length(LIST *l) {
    return l->size;
}
int hellll()
{
    return 0;
}

int lst_is_empty(LIST *l) {
    return l->front == NULL;
}


/** TODO
 *    function:  lst_count
 *     description:  Counts number of occurrences
 *     		of x in the list and returns
 *     		that value.
 */
int lst_count(LIST *l, ElemType x)
{
    NODE* pTemp = l->front;
    int total_x = 0;
    while(pTemp != NULL)
    {
        if(pTemp->val == x)
        {
            total_x++;
        }
        pTemp = pTemp->next;
    }
    return total_x;
}

/* These are "sanity checker" functions that check to see
 *     list invariants hold or not.
 */
int lst_sanity1(LIST *l) {
    if(l->front == NULL && l->back != NULL){
        fprintf(stderr, "lst_sanity1 error:  front NULL but back non-NULL\n");
        return 0;
    }
    if(l->back == NULL && l->front != NULL){
        fprintf(stderr, "lst_sanity1 error:  back NULL but front non-NULL\n");
        return 0;
    }
    return 1;
}

int lst_sanity2(LIST *l) {
    if(l->back != NULL && l->back->next != NULL) {
        fprintf(stderr, "lst_sanity2 error:  back elem has a non-NULL next?\n");
        return 0;
    }
    return 1;
}

/*
 * function:  find_back()
 * description:  returns a pointer to the last
 *               node of the given list.
 *		Note that we are operating at
 *		the "node level".
 *
 *		if p is NULL, NULL is returned.
 *
 * purpose:  mostly for debugging -- enables sanity3
 */
static NODE * find_back(NODE *p) {
    
    if(p ==  NULL)
        return NULL;
    
    while(p->next != NULL) {
        p = p->next;
    }
    return p;
}

/*
 *   makes sure that the back pointer is also the last reachable
 *    node when you start walking from front.
 *    HINT:  use pointer comparison
 */
int lst_sanity3(LIST *l) {
    NODE *real_back;
    
    real_back = find_back(l->front);
    
    return (real_back == l->back);
}



ElemType lst_pop_front(LIST *l) {
    ElemType ret;
    NODE *p;
    
    
    if(lst_is_empty(l))
        return DEFAULT;   // no-op
    
    ret = l->front->val;
    
    if(l->front == l->back) {  // one element
        free(l->front);
        l->front = NULL;
        l->back = NULL;
    }
    else {
        p = l->front;  // don't lose node being deleted
        l->front = l->front->next;  // hop over
        free(p);
    }
    l->size = (l->size)-1;
    return ret;
}





/* TODO
 *
 *    if list is empty, we do nothing and return arbitrary value
 *    otherwise, the last element in the list is removed and its
 *      value is returned.
 *
 */
ElemType lst_pop_back(LIST *l)
{
    if(lst_is_empty(l))
    {
        fprintf(stderr, "Error: The list is empty!\n");
        return -99999999;
    }
    
    NODE* pTemp = l->front;
    NODE* pTemp_back = l->back;
    int return_val = pTemp_back->val;
    
    if(pTemp == pTemp_back)
    {
        l->front = NULL;
        l->back = NULL;
        
        free(pTemp);
        l->size = (l->size)-1;
        return return_val;
    }
    
    while(pTemp->next->next != NULL)
    {
        pTemp = pTemp->next;
    }
    l->back = pTemp;
    l->back->next = NULL;
    free(pTemp_back);
    l->size = (l->size)-1;
    
    
    return return_val;
}

/* TODO
 *  For full credit, you cannot allocate any new memory!
 *
 *  description:  self-evident
 */
NODE* lst_reverse_recur(NODE* pHead)
{
    if(pHead->next == NULL)
    {
        return pHead;
    }
    NODE* pTemp_tail = lst_reverse_recur(pHead->next);
    pTemp_tail->next = pHead;
    return pHead;
    
}

void lst_reverse(LIST *l)
{
    if(lst_is_empty(l))
    {
        fprintf(stderr, "Error: The list is empty\n");
        return;
    }
    else if (l->front == l->back)
    {
        return;
    }
    
    lst_reverse_recur(l->front);
    NODE* pTemp = l->front;
    l->front = l->back;
    l->back = pTemp;
    l->back->next = NULL;
    
}


/*
 * removes first occurrence of x (if any).  Returns
 *   0 or 1 depending on whether x was found
 */
int lst_remove_first(LIST *l, ElemType x) {
    NODE *p;
    NODE *tmp;
    
    if(l->front == NULL) return 0;
    if(l->front->val == x) {
        lst_pop_front(l);
        return 1;
    }
    // lst non-empty; no match on 1st elem
    p = l->front;
    
    while(p->next != NULL) {
        if(x == p->next->val) {
            tmp = p->next;
            p->next = tmp->next;
            if(tmp == l->back)
                l->back = p;
            free(tmp);
            return 1;
        }
        p = p->next;
    }
    return 0;
}


/**
 * function: lst_remove_all_slow
 * description:  removes all occurrences of x
 *   from given list (if any).
 *   Returns number of occurrences (i.e., deletions).
 *
 * notes:  it is called "slow" because in the worst
 *   case, it takes quadratic time.
 *   (Discussion of why and when this happens is a
 *   lecture topic).
 */
int lst_remove_all_slow(LIST *l, ElemType x) {
    int n=0;
    while(lst_remove_first(l, x))
        n++;
    return n;
}

/**
 * function: lst_sra_bad_case (sra:  slow_remove_all)
 *
 * description: constructs a list of length n such that
 * the above function takes quadratic time to remove
 * all occurrences of a specified value.
 *
 * By convention, the specified value will be 0
 */
LIST *lst_sra_bad_case(int n) {
    LIST *l = lst_create();
    int i;
    int k=n/2;
    
    for(i=0; i<k; i++) {
        lst_push_front(l, 0);
    }
    for(i=0; i<n-k; i++) {
        lst_push_front(l, 1);
    }
    return l;
}

/** TODO
 *   function:  lst_remove_all_fast
 *   description:  same behavior/semantics as
 *      lst_remove_all_slow.  However, this function
 *      must guarantee linear time worst case
 *      runtime (hence, "fast").
 *
 *   REQUIREMENT:  linear worst-case runtime.
 *
 *   Note:  your solution may be either recursive or
 *   iteratieve.
 **/
int lst_remove_all_fast(LIST *l, ElemType x)
{
    NODE* pTmep = l->front->next;
    NODE* pre_pTemp = l->front;
    NODE* del_node;
    int return_Var = 0;
    while (pTmep != NULL)
    {
        if(pTmep->val == x)
        {
            l->size -= 1;
            pre_pTemp->next = pTmep->next;
            del_node = pTmep;
            pTmep = pTmep->next;
            free(del_node);
            return_Var = 1;
            
            continue;
        }
        pre_pTemp = pre_pTemp->next;
        pTmep = pTmep->next;
    }
    if(l->front->val == x)
    {
        del_node = l->front;
        l->front = l->front->next;
        l->size -= 1;
        free(del_node);
        return_Var = 1;
    }
    
    return return_Var;
}

int lst_is_sorted(LIST *l){
    NODE *p = l->front;
    
    while(p!=NULL && p->next != NULL) {
        if(p->val > p->next->val)
            return 0;
        p = p->next;
    }
    return 1;
}



/** TODO
 * function:  lst_insert_sorted
 *
 * description:  assumes given list is already in sorted order
 *	   and inserts x into the appropriate position
 * 	   retaining sorted-ness.
 * Note 1:  duplicates are allowed.
 *
 * Note 2:  if given list not sorted, behavior is undefined/implementation
 * 		dependent.  We blame the caller.
 * 		So... you don't need to check ahead of time if it is sorted.
 */
void lst_insert_sorted(LIST *l, ElemType x)
{
    NODE* new_node = malloc(sizeof(NODE));
    new_node->val = x;
    new_node->next = NULL;
    
    if(lst_is_empty(l))
    {
        lst_push_front(l, x);
        return;
    }
    
    NODE* pTemp = l->front;
    if(x < pTemp->val)
    {
        l->front = new_node;
        new_node->next = pTemp;
        l->size += 1;
        return;
    }
    
    
    
    while(pTemp->next != NULL)
    {
        if(pTemp->next->val > x)
        {
            break;
        }
        pTemp = pTemp->next;
    }
    
    if(pTemp->next == NULL)
    {
        pTemp->next = new_node;
        l->back = new_node;
        l->size += 1;
        return;
    }
    
    new_node->next = pTemp->next;
    pTemp->next = new_node;
    l->size += 1;
    
    
}

/** TODO
 * function:  lst_merge_sorted
 *
 * description:  assumes both list a and b are in
 * 	sorted (non-descending) order and merges them
 * 	into a single sorted list with the same
 * 	elements.
 *
 * 	This single sorted list is stored in a while
 * 	b becomes empty.
 *
 * 	if either of given lists are not sorted,
 * 	we blame the caller and the behavior is
 * 	implementation dependent -- i.e., don't worry
 * 	about it!
 *
 *      Condition in which both parameters are the same
 *      list (not merely "equal"), the function simply
 *      does nothing and returns.  This can be tested
 *      with simple pointer comparison.
 *
 * 	Example:
 *
 * 		a:  [2 3 4 9 10 30]
 * 		b:  [5 8 8 11 20 40]
 *
 * 		after call on (a,b)
 *
 * 		a:  [2 3 4 5 8 8 9 10 11 20 30 40]
 * 		b:  []
 *
 * implementation:  should not allocate ANY new list
 * 	nodes -- it should just re-link existing
 * 	nodes.
 *
 * 	Must be linear time in the |a|+|b| -- i.e.,
 * 	the total number of elements being processed.
 */

void node_insert_sorted(LIST *l, NODE* add_node)
{
    NODE* new_node = add_node;
    new_node->next = NULL;
    
    if(lst_is_empty(l))
    {
        l->front = new_node;
        l->back = new_node;
        return;
    }
    
    NODE* pTemp = l->front;
    if(new_node->val < pTemp->val && pTemp->next == NULL)
    {
        pTemp->next = new_node;
        l->back = new_node;
        return;
    }
    
    
    
    while(pTemp->next != NULL)
    {
        if(pTemp->next->val > new_node->val)
        {
            break;
        }
        pTemp = pTemp->next;
    }
    
    if(pTemp->next == NULL)
    {
        pTemp->next = new_node;
        l->back = new_node;
        return;
    }
    
    new_node->next = pTemp->next;
    pTemp->next = new_node;
    
    
}

void lst_merge_sorted(LIST *a, LIST *b)
{
    if(lst_is_empty(a))
    {
        a->size = b->size;
        a->front = b->front;
        a->back = b->back;
        b->front = NULL;
        b->back = NULL;
        return;
    }
    if(lst_is_empty(b))
    {
        return;
    }
    
    NODE* pTemp = b->front;
    
    NODE* a_pTemp = a->front;
    
    if( pTemp->val <= a_pTemp->val)
    {
        b->front = b->front->next;
        a->front = pTemp;
        pTemp->next = a_pTemp;
        //pTemp->next = a_pTemp;
        //a_pTemp = a_pTemp->next;
        a_pTemp = a->front;
        pTemp = b->front;
        
    }
    
    
    
    while(pTemp != NULL)
    {
        if(a_pTemp->next == NULL)
        {
            a_pTemp->next = b->front;
            a->back = b->back;
            break;
        }
        if(pTemp->val <= a_pTemp->next->val)
        //if(pTemp->val <= a_pTemp->val)
        {
            
            b->front = b->front->next;
            pTemp->next = a_pTemp->next;
            a_pTemp->next = pTemp;
            a_pTemp= a_pTemp->next;
            pTemp = b->front;
            continue;
            
        }
        
        a_pTemp = a_pTemp->next;
        
    }
    if(a->back->next != NULL)
    {
        a->back = b->back;
    }
    a->size += b->size;
    
    b->front = NULL;
    b->back = NULL;
    
    
}

/**
 * TODO
 * function:  lst_clone
 *
 * description:  makes a "deep copy" of the given list a
 *   and returns it (as a LIST pointer).
 *
 */
LIST * lst_clone(LIST *a)
{
    LIST* new_list = lst_create();
    if(lst_is_empty(a))
    {
        return new_list;
    }
    
    NODE* pTemp = a->front;
    NODE* new_list_node;
    NODE* new_list_pre_node;
    new_list_node = malloc(sizeof(NODE));
    new_list_node->val = pTemp->val;
    new_list_node->next = NULL;
    pTemp = pTemp->next;
    new_list->front = new_list_node;
    
    
    
    int k = 0;
    while (pTemp != NULL)
    {
        
        new_list_pre_node = new_list_node;
        new_list_node = malloc(sizeof(NODE));
        new_list_node->val = pTemp->val;
        new_list_node->next = NULL;
        new_list_pre_node->next = new_list_node;
        pTemp = pTemp->next;
        
    }
    
    new_list->back = new_list_node;
    new_list->size = a->size;
    
    
    return new_list;
    
}



/**
 * TODO
 * function:  lst_from_array
 *
 * description:  creates a new list populated with the
 *      elements of array a[] in the same order as
 *      they appear in a[] (element at a[0] will be the
 *      first element in the list and so-on).  List is
 *      returned as a LIST pointer.
 *
 *      Parameter n indicates the length of the given array.
 *
 * runtime requirement:  THETA(n)
 */
LIST * lst_from_array(ElemType a[], int n)
{
    
    LIST* new_list = lst_create();
    
    if(n < 1)
    {
        return new_list;
    }
    /*
    NODE* pTemp = malloc(sizeof(NODE));
    pTemp->val = a[0];
    pTemp->next = NULL;
    NODE* pTemp_pre_node;
    new_list->front = pTemp;
    int i;
    for(i = 1; i < n; i++)
    {
        pTemp_pre_node = pTemp;
        pTemp = malloc(sizeof(NODE));
        pTemp->val = a[i];
        pTemp->next = NULL;
        pTemp_pre_node->next = pTemp;
        
    }
    new_list->back = pTemp;
    new_list->size = n;
     */
    int i;
    for(i = 0; i < n; i++)
    {
        lst_push_back(new_list, a[i]);
    }
    
    return new_list;
    
}


/**
 * TODO
 * function:  lst_to_array
 *
 * description:  allocates an array of ElemType and populates
 *         it with the elements in the given list (as with
 *         lst_from_array elements are in the same order in
 *         both data structures).
 *
 * runtime requirement:  THETA(n)
 *
 */
ElemType * lst_to_array(LIST *lst)
{
    NODE* pTemp = lst->front;
    int n = lst_length(lst);
    ElemType* array = malloc(n*sizeof(ElemType));
    int i;
    pTemp = lst->front;
    for (i = 0; i < n; i++)
    {
        array[i] = pTemp->val;
        pTemp = pTemp->next;
    }
    
    printf("\n");
    return array;
}


/**
 * TODO
 * function:  lst_prefix
 *
 * description:  removes the first k elements from the
 *               given list which are used to form a new list
 *		which is then returned.
 *
 *		if n is the length of the given list, we have the
 *		following boundary conditions:
 *
 *		  if k==0:
 *			lst unchanged and an empty list returned
 *		  if k>=n:
 *			lst becomes empty and a list containing
 *			all elements previously in lst is returned.
 *
 *		examples:
 *
 *		  EX1:  lst:  [2, 3, 9, 7, 8]
 *			k:    3
 *
 *			after call:
 *			   lst:  [7, 8]
 *			   returned list:  [2, 3, 9]
 *
 *		  EX2  lst:  [2, 3, 9, 7, 8]
 *			k:    0
 *
 *			after call:
 *			   lst:  [2, 3, 9, 7, 8]  (unchanged)
 *			   returned list:  []
 *
 *		  EX3  lst:  [2, 3, 9, 7, 8]
 *			k:    5
 *
 *			after call:
 *			   lst:  []
 *			   returned list:  [2, 3, 9, 7, 8]
 *
 * REQUIREMENTS:
 *
 *	RUNTIME:  THETA(n) worst case where n is the length of the given list
 *
 *       ORDERING:  the ordering of the returned prefix should be the same as
 *                  in the given list
 *
 *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
 *		   you should just "re-use" the existing nodes.  HOWEVER, you will
 *		   need to allocate a LIST structure itself (i.e., for the returned
 *		   list).
 */
LIST * lst_prefix(LIST *lst, unsigned int k)
{
    LIST* return_list = lst_create();
    lst->size = (lst->size) - k;
    if(lst->size < 0)
    {
        lst->size = 0;
    }

    
    
    NODE* pTemp = lst->front;
    NODE* beginning = pTemp;
    
    int i;
    if(lst_is_empty(lst) && k!=0)
    {
        fprintf(stderr, "Error: The list is empty! \n");
        return return_list;
    }
    else if(k == 0)
    {
        return return_list;
    }
    
    int z = 0;
    for(i = 0; i < k; i++)
    {
        if(pTemp->next == NULL || i == k-1)
        {
            break;
        }
        pTemp = pTemp->next;
        z++;
    }
    
    return_list->front = beginning;
    return_list->back = pTemp;
    lst->front = pTemp->next;
    return_list->back->next = NULL;
    
    
    if(pTemp == NULL)
    {
        lst->back = NULL;
    }
    return_list->size = z+1;
    
    
    
    
    
    return return_list;
    
}




/**
 * TODO
 * function:  lst_filter_leq
 *
 * description:  removes all elements of the given list (lst) which
 *		are less than or equal to a given value (cutoff)
 *
 *		A list containing the removed elements is returned.
 *
 * examples:
 *
 *	EX1: 	lst:  [4, 9, 2, 4, 8, 12, 7, 3]
 *		cutoff:  4
 *
 *		after call:
 *			lst:  [9, 8, 12, 7]
 *			returned list:  [4, 2, 4, 3]
 *
 *       -----------------------------------------
 *	EX2: 	lst:  [6, 5, 2, 1]
 *		cutoff:  6
 *
 *		after call:
 *			lst:  []
 *	 		returned list:  [6, 5, 2, 1]
 *
 * REQUIREMENTS:
 *
 *	RUNTIME:  THETA(n) where n is the length of the given list
 *
 *       ORDERING:  the ordering of the returned list should be the same as
 *                  in the given list
 *
 *       MEMORY:    for full credit, no new nodes should be allocated or deallocated;
 *		   you should just "re-use" the existing nodes.  HOWEVER, you will
 *		   need to allocate a LIST structure itself (i.e., for the returned
 *		   list).
 *
 */
LIST * lst_filter_leq(LIST *lst, ElemType cutoff)
{
    
    
    LIST* new_list = lst_create();
    if(lst_is_empty(lst))
    {
        return new_list;
    }
    
    NODE* list_pTemp = lst->front->next;
    NODE* list_pre_pTemp = lst->front;
    NODE* new_list_pTemp = NULL;
    
    int total = 0;
    NODE* last_node = lst->back;
    
    while (list_pTemp != NULL)
    {
        if(list_pTemp->val > cutoff)
        {
            last_node = list_pre_pTemp;
            
        }
        if(list_pTemp->val <= cutoff)
        {
            if(new_list->front == NULL)
            {
                new_list->front = list_pTemp;
                new_list_pTemp = list_pTemp;
            }
            else
            {
            
                new_list_pTemp->next = list_pTemp;
                new_list_pTemp = new_list_pTemp->next;
            }
            
    
            list_pre_pTemp->next = list_pTemp->next;
            list_pTemp = list_pTemp->next;
            //last_node = list_pre_pTemp;
            total++;
            continue;
        }
        list_pre_pTemp = list_pTemp;
        list_pTemp = list_pTemp->next;
        
    }
    
    lst->size = (lst->size) - total;
    if(list_pTemp == NULL)
    {
        lst->back = list_pre_pTemp;
        list_pre_pTemp->next = NULL;
    }
    else
    {
        lst->back = list_pTemp;
        list_pTemp->next = NULL;
    }
    
    if(new_list_pTemp != NULL)
    {
        new_list_pTemp->next = NULL;
    }
    new_list->back = new_list_pTemp;
    
    
    
    
    
    NODE* first_node;
    if(lst->front->val <= cutoff)
    {
        lst->size -= 1;
        first_node = lst->front;
        lst->front = lst->front->next;
        first_node->next = new_list->front;
        new_list->front = first_node;
        total++;
    }
    new_list->size = total;
    
    
    
    return new_list;
    
}

/**
 * TODO
 * function:  lst_concat
 *
 * description:  concatenates lists a and b; resulting
 *    concatenation is reflected in list a; list b becomes
 *    empty.
 *
 *    example:
 *
 *	EX1:  a: [2, 9, 1]
 *	      b: [5, 1, 2]
 *
 *	after call:
 *
 *		a: [2, 9, 1, 5, 1, 2]
 *		b: []
 *
 * REQUIREMENTS:  
 *
 *     runtime:  O(1)
 *
 *     sanity:  this operation makes sense when a and b
 *		are distinct lists.  For example, we don't
 *		want/allow the caller to do something like
 *		this:
 *
 *			LIST *my_list;
 *
 *			lst_push_front(my_lst, 4);
 *			lst_push_front(my_lst, 2);
 *
 *			lst_concat(my_lst, my_lst);
 *
 *		your implementation must detect if it is being
 *		called this way.  If so the function does nothing
 *		and (optionally) prints an error message to
 *		stderr.
 *	
 */
void lst_concat(LIST *a, LIST *b)
{
    if(a->front == b->front)
    {
        fprintf(stderr, "Error: Same list, can't concat!\n");
        return;
    }
    if(lst_is_empty(b))
    {
        return;
    }
    if(lst_is_empty(a))
    {
        a->front = b->front;
        a->back = b->back;
        b->front = NULL;
        b->back = NULL;
        return;
    }
    
    a->back->next = b->front;
    a->back = b->back;
    a->size += b->size;
    b->size = 0;
    b->front = NULL;
    b->back = NULL;
    
    
}




