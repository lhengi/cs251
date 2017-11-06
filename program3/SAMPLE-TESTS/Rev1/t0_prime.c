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
void insert_1_N(int n) {
  int i;
    t = bst_create();
    for(i=1; i<=n; i++)
        bst_insert(t, i);
}
int insert_1_N_free(int n) {
  int i;
    insert_1_N(n);
    bst_free(t);
    return 1;
}

int main(int argc, char *argv[]){
    int i;
    int n=5;

    if(argc >= 2) 
      n = atoi(argv[1]);
    if(argc==3)
      set_ntrials(atoi(argv[2]));

    t = bst_create();

    cal_big_fudge();

    clock_t budget = calibrate_nlogn(n, TIME_TRIALS);
    
    TIME(insert_1_N_free(n), 1, budget, 1.0);

    insert_1_N(n);  // do it one more time for report

    // this function is in header.c, not bst.c
    bst_report(t);

    if(n<11)
      bst_preorder(t);


    bst_free(t);
    
}
