#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

// super-hacky... including a .c file
#include "header.c"



// Global?  Yes... but this is a tester
BST *t;

/*
 * inserts integers 1..n into tree t
 *   (which is globally accessible...)
 *
 * always returns one to make the TIME_ONCE
 *    macro happy.
 */
int insert_1_N(int n) {
  int i;
    for(i=1; i<=n; i++)
        bst_insert(t, i);
    return 1;
}

int main(int argc, char *argv[]){
    int i;
    int n=5;

    if(argc == 2) 
      n = atoi(argv[1]);

    t = bst_create();

    cal_big_fudge();

    clock_t budget = calibrate_nlogn(n, 1);
    
    TIME_ONCE(insert_1_N(n), "insert-1..n test",  1, budget, 1.0);

    // this function is in header.c, not bst.c
    bst_report(t);

    if(n<11)
      bst_preorder(t);


    bst_free(t);
    
}
