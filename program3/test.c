#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bst.h"

/**
    BARE-BONES DEMO PROGRAM.
    You may use this as a starting pint for developing your
    testing code
**/

int main(){
    int i;
    
    printf("DONT FORGET TO DO YOUR WRITEUP\n");
    
    printf("Starting tests...\n");
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int arrSize = 10;
    int temp = 0;
    
    temp = 10000;
    
    BST * t = bst_create();
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Add a bunch, remove a bunch
    //////////////////////////////////////////////////////////////////////////////////////////////////
    
    printf("Adding %d and then removing all %d (list should be empty at end):\n", temp, temp);
    printf("");
    
    for(i = 1; i < temp; i++)
        bst_insert(t, i);
    
    if(bst_size(t) != temp - 1)
        printf("FAIL (sizes don't match)\n");
    
    for(i = 1; i < temp; i++)
        bst_remove(t, i);
    
    printf("Testing remove on invalid values..\n");
    printf("No error message provide. Passes if list is empty at end\n");
    
    for(i = 1; i < temp; i++)
        bst_insert(t, i);
    
    for(i = 1; i < (temp * 2); i++)
    {
        bst_remove(t, i);
    }
    
    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
    printf("Add/Remove test over.\n\n");
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Size balance tests:
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Size balance test: start (%d inserts)\nIf becomes unbalanced, will show error message..\n", temp);
    
    for(i=1; i<temp; i++)
    {
        bst_insert(t, i);
        if(max_sb_height(bst_size(t)) < bst_height(t))
        {
            printf("UH OH: %d  %d  SIZE: %d\n", max_sb_height(bst_size(t)), bst_height(t), bst_size(t));
        }
    }
    
    printf("Inserts over.\n");
    printf("Size balance test: start (%d removes)\n", temp);
    
    for(i=1; i<temp; i++)
    {
        bst_remove(t, i);
        
        if(max_sb_height(bst_size(t)) < bst_height(t))
        {
            printf("UH OH: %d  %d  SIZE: %d\n", max_sb_height(bst_size(t)), bst_height(t), bst_size(t));
        }
    }
    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
    
    printf("Removes over.\n");
    printf("Test over..\n\n");
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Height test
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing height (tests size balancing)\n");
    printf("Will print FAIL if height of BST is over max_height.\n");
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        if(bst_height(t) > max_sb_height(bst_size(t)))
            printf("***FAIL\n");
        
    }
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
        if(bst_height(t) > max_sb_height(bst_size(t)))
            printf("***FAIL\n");
        
    }
    if(bst_size(t) == 0)
        printf("PASSED.\n");
    else
        printf("FAILED.\n");
    printf("Height test over.\n");
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing get_ith()
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing get_ith()\n");
    printf("Will show FAIL if wrong\n");
    
    int ith = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        ith = bst_get_ith(t, i);
        if(ith != i)
            printf("***FAIL\n");
    }
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    
    //////////////////////////
    
    printf("Test over.\n");
    printf("Inserting in reverse order to test get_ith() again..\n");
    
    for(i = temp; i > 0; i--)
        bst_insert(t, i);
    
    for(i = 1; i < temp; i++)
    {
        ith = bst_get_ith(t, i);
        if(ith != i)
            printf("FAIL at %d\n",i);
    }
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    printf("Test over.\n");
    
    //////////////////////////////////////////
    printf("Testing get_ith on invalid values (assumes not found returns -1\n");
    
    for(i = 1; i < temp; i++)
    {
        if(i == 9999)
        {
            printf("at 9999\n");
        }
        bst_insert(t, i);
        ith = bst_get_ith(t, temp + 1);
        
        if(ith != -1)
            printf("***FAIL\n");
    }
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    
    printf("Test over.\n\n");
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing greater than or equal
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing geq()\nWill print FAIL if wrong\n");
    
    int val = 1;
    int geq = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        geq = bst_num_geq(t, val);
        if(geq != bst_size(t))
            printf("***FAIL\n");
    }
    
    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_geq(t, i);
        if(geq != (temp - i + 1))
            printf("***FAIL\n");
    }
    printf("Test over.\n");
    printf("Another test..\n");
    
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_geq(t, temp + 1);
        if(geq != 0)
            printf("***FAIL\n");
    }
    
    printf("Test over.\n");
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    
    printf("Test over.\n\n");
    
    /////////////////////
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing less than or equal
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing leq()\nWill print FAIL if wrong\n");
    
    val = 1;
    geq = 0;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        geq = bst_num_leq(t, val);
        if(geq != 1)
            printf("***FAIL\n");
    }
    
    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_leq(t, i);
        if(geq != i)
            printf("***FAIL\n");
    }
    printf("Test over.\n");
    
    ////////////////////////////
    
    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        geq = bst_num_leq(t, 0);
        if(geq != 0)
            printf("***FAIL\n");
    }
    printf("Test over.\n");
    
    /////////////////////////////
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    
    printf("Test over.\n\n");
    
    /////////////////////
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing range
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Test num_range()\nWill print FAIL if wrong\n");
    
    val = 1;
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
    }
    
    for(i = 1; i < temp; i++)
    {
        val = bst_num_range(t, 1, temp);
        if(val != temp)
            printf("FAIL");
    }
    
    printf("Another test..\n");
    for(i = 1; i < temp; i++)
    {
        val = bst_num_range(t, -100, temp);
        if(val != temp)
            printf("FAIL");
    }
    
    for(i = 1; i < temp; i++)
        bst_remove(t, i);
    
    printf("Test over\n\n");
    
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing nearest
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Testing get_nearest() will print FAIL if wrong\n");
    
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
        val = bst_get_nearest(t, i);
        if(val != i)
            printf("***FAIL\n");
    }
    
    for(i = 1; i < temp; i++)
    {
        bst_remove(t, i);
    }
    
    printf("Test over.\nAnother test..\n");
    
    for(i = 1; i < temp; i = i + 10)
    {
        bst_insert(t, i);
    }
    
    for(i = 1; i < temp; i = i + 10)
    {
        val = bst_get_nearest(t, i - 1);
        if(val != i)
            printf("***FAIL\n");
        val = bst_get_nearest(t, i + 1);
        if(val != i)
            printf("***FAIL\n");
    }
    
    printf("Test over (removing in strange way to provoke errors..\n");
    for(i = -100; i < temp; i++)
        bst_remove(t, i);
    
    
    printf("Test over.\n\n");
    
    //////////////////////////////////////////////////////////////////////////////////////////////////
    ///Testing bst_from_array and bst_to_array
    //////////////////////////////////////////////////////////////////////////////////////////////////
    printf("Test bst_from_array and bst_to_array\n");
    
    t = bst_from_sorted_arr(arr, arrSize);
    if(bst_height(t) > max_sb_height(bst_size(t)))
        printf("***FAIL\n");
    
    if(bst_size(t) != arrSize)
        printf("FAIL (sizes don't match)\n");
    
    val = bst_get_ith(t, 1);
    if(val != arr[0])
        printf("***FAIL\n");
    
    val = bst_num_geq(t, arr[arrSize - 1]);
    if(val != 1)
        printf("***FAIL\n");
    
    val = bst_num_leq(t, arr[0]);
    if(val != 1)
        printf("***FAIL\n");
    
    for(i = -100; i < (arrSize + 200); i++)
        bst_remove(t, i);
    
    printf("Another test..\n");
    
    for(i = 1; i < temp; i++)
    {
        bst_insert(t, i);
    }
    
    ///////////////////////////
    
    ///Test bst_to_array, sorted
    int* newArr;
    
    newArr = bst_to_array(t);
    
    for(i = 0; i < temp - 2; i++)
    {
        if(newArr[i] > newArr[i+1])
            printf("***FAIL\n");
    }
    free(newArr);
    for(i = -100; i < (temp + 200); i++)
        bst_remove(t, i);
    
    printf("Test over.\n\n");
    
    
    printf("Freeing BST\n");
    bst_free(t);
    printf("All tests over.\n");
    
    
    
    return 0;
}


/*
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
    printf("Now remove 1\n");
    bst_remove(t, 1);
    bst_inorder(t);
    bst_preorder(t);
    printf("Now insert 1 back\n");
    bst_insert(t, 1);
    printf("Now insert 0\n");
    bst_insert(t, 0);
    //good
    bst_remove(t, 1);
    //good
    bst_insert(t, 1);
    bst_remove(t, 3);
    bst_inorder(t);
    bst_preorder(t);
    
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
}*/
