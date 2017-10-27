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
    bst_free(t);


    return 0;
}
