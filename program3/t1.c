#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

#include "header.c"


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

int delete_evens(int n) {
  int count=0;
  int x, ndel=0;
  for(x=2; x<n; x+=2) {
    ndel += bst_remove(t, x);
    count++;
  }
  return ndel==count;
}

int main(int argc, char *argv[]){
    int i;
    int n=5;

    if(argc == 2) 
      n = atoi(argv[1]);

    t = bst_create();

    cal_huge_fudge();

    clock_t budget = calibrate_nlogn(n, 1);
    
    TIME_ONCE(insert_1_N(n), "insert-1..n test",  1, budget, 1.0);

    bst_report(t);

    TIME_ONCE(delete_evens(n), "del-evens test",  1, budget, 1.0);

    bst_report(t);



    size_sanity(t);

    bst_free(t);
    
}
