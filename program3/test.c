#include <stdio.h>
#include <assert.h>
#include "bst.h"

/**
    BARE-BONES DEMO PROGRAM.
    You may use this as a starting pint for developing your
    testing code
**/

int main(){
    int i;

    int a[] = {8, 2, 6, 9, 11, 3, 7};

    BST * t = bst_create();

    for(i=0; i<7; i++)
        bst_insert(t, a[i]);

    assert(bst_size(t) == 7);

    printf("AFTER SEQUENTIAL INSERTION OF  {8, 2, 6, 9, 11, 3, 7}\n\n");; 
    bst_inorder(t);
    bst_preorder(t);
    bst_free(t);
    
    printf("NOW TRYING bst_from_sorted_arr()\n\n");
    int sorted_a[] = {2, 3, 6, 7, 8, 9, 11};
    
    t = bst_from_sorted_arr(sorted_a, 7);
    
    bst_inorder(t);
    bst_preorder(t);
    bst_free(t);

    t = bst_create();
    printf("NOW INSERTING 1...10 in ordern\n");

    for(i=1; i<=10; i++) 
       bst_insert(t, i);

    bst_inorder(t);
    bst_preorder(t);
    //bst_free(t);
    
    printf("Start bst_to_array\n");
    int* array_from_tree = bst_to_array(t);
    for(i = 0; i < bst_size(t);i++)
    {
        printf(" %d",array_from_tree[i]);
    }
    printf("end bst_to_array\n");
    
    bst_inorder(t);
    
    printf("\n get 6 th, %d\n",bst_get_ith(t, 0));
    
    bst_free(t);
    t = bst_create();
    printf("\n***New array new tree\n");
    int array[] = {3,45,62,3,6,4,21,5,67,9,6,5,4,3,2,0};
    int n = 16;
    for(i = 0; i < n; i++)
    {
        bst_insert(t, array[i]);
    }
    bst_postorder(t);
    
    int* array_from_bst = bst_to_array(t);
    for(i = 0; i < bst_size(t);i++)
    {
        printf(" %d,",array_from_bst[i]);
    }
    printf("\n****End of bst_to_array\n");
    //bst_postorder(t);
    printf("\n\n******* Before remove 3 size = %d\n\n",bst_size(t));
    bst_preorder(t);
    bst_remove(t, 3);
    printf("\n\n******* After remove 3 size = %d\n\n",bst_size(t));
    bst_preorder(t);
    bst_remove(t, 99);
    printf("\n\n******* After remove 99 size = %d\n\n",bst_size(t));
    bst_preorder(t);
    printf("\n\n******* bst from array, using array: array_from_bst\n Expecting 0,2,3,4,5,6,7,21,45,62,67\n\n");
    BST* t_from_array = bst_from_sorted_arr(array_from_bst, 11);
    printf("size of new three: %d\n",bst_size(t_from_array));
    bst_inorder(t_from_array);
    bst_preorder(t_from_array);
    
    printf("bst_leq(0): expecting 1, result: %d\n",bst_num_leq(t, 0));
    printf("bst_geq(0): expecting 10, result: %d\n",bst_num_geq(t, 0));
    printf("bst_leq(21): expecting 8, result: %d\n",bst_num_leq(t_from_array, 21));
    printf("bst_geq(21): expecting 4, result: %d\n",bst_num_geq(t_from_array, 21));
   
    
    
    
    
    

    return 0;
}
