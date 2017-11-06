

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int TestNum = 1;
int NPassed = 0;
int NFailed = 0;

float Score = 0;
float MaxPts = 0;
float ThisScore = 0;
float ThisMaxPts = 0;

float MaxPtsAuto= 0;
float MaxPtsManual= 0;

float PtsPer = 1.0;

char *CurrFunc;

typedef struct {
  int a, b, c;
} JUNK;

// #define TIME_TRIALS 100000

int TIME_TRIALS = 100;

void set_ntrials(int ntrials) {
  TIME_TRIALS = ntrials;
}



#define TA_MESSAGE(msg) { \
	printf("  #### TA-TODO : #####\n"); \
	printf("  ####    %s\n", msg); \
	printf("  #### END TA-TODO ###\n"); } \
	

#define TEST_RET(func_call, answer, pts) { \
	int ret; \
	printf("  ###  TEST %i:  %s; %.2f points\n", TestNum, "\""#func_call"\"",  pts); \
	ret = func_call;  \
	printf("     Returned Value      : %i\n", ret); \
	printf("     Correct Return Value: %i\n", answer); \
	if(ret == answer) {NPassed++; ThisScore+=pts; Score += pts; printf("     PASSED\n");} \
	else {NFailed++; printf("     FAILED\n");} \
	printf("     Cummulative Score(%s): %.2f\n", CurrFunc, ThisScore); \
	printf("  ###  END TEST %i\n\n", TestNum); \
	MaxPts += pts; \
	MaxPtsAuto += pts; \
	TestNum++; \
}

#define TEST_RET_MESSAGE(func_call, msg, answer, pts) { \
	int ret; \
	printf("  ###  TEST %i:   %.2f points\n", TestNum,  pts); \
	printf("          DESC: %s\n", msg); \
	ret = func_call;  \
	printf("     Returned Value      : %i\n", ret); \
	printf("     Correct Return Value: %i\n", answer); \
	if(ret == answer) {NPassed++; ThisScore+=pts; Score += pts; printf("     PASSED\n");} \
	else { NFailed++; printf("     FAILED\n");} \
	printf("     Cummulative Score(%s): %.2f\n", CurrFunc, ThisScore); \
	printf("  ###  END TEST %i\n\n", TestNum); \
	MaxPts += pts; \
	MaxPtsAuto += pts; \
	TestNum++; \
}


#define TIME(func_call, answer, max_time, pts) { \
	int i, ret; \
	clock_t start, end, diff; \
	start  = clock(); \
	printf("  ###  TEST %i (TIMED):  %s; %.2f points\n", TestNum, "\""#func_call"\"",  pts); \
	MaxPts += pts; \
	MaxPtsAuto += pts; \
	for(i=0; i<TIME_TRIALS; i++) { \
	  ret = func_call; \
	  if(ret != answer) break; \
	} \
	end = clock(); \
	diff = end-start; \
	if(ret != answer){ \
	    printf("     FAILED; \n"); \
	    printf("     Returned Value      : %i\n", ret); \
	    printf("     Correct Return Value: %i\n", answer); \
	    NFailed++; \
	} \
	else if(diff > max_time) { \
	    printf("     FAILED \n"); \
	    printf("     TOO SLOW!\n"); \
	    printf("     MAX-TIME ALLOWED:  %ld\n", max_time); \
	    printf("     TIME TAKEN:        %ld\n", diff); \
	    printf("     (NUM-TRIALS:       %i\n", TIME_TRIALS); \
	    NFailed++; \
	} \
	else { \
	    printf("     PASSED\n"); \
	    printf("     MAX-TIME ALLOWED:  %ld\n", max_time); \
	    printf("     TIME TAKEN:        %ld\n", diff); \
	    Score += pts; \
	    NPassed++; \
	    ThisScore += pts; \
	} \
	printf("     Score So Far For Function: %.2f / %.2f\n", ThisScore, ThisMaxPts); \
	printf("  ###  END TEST %i\n\n", TestNum); \
	TestNum++;\
}

#define TIME_ONCE(func_call, msg, answer, max_time, pts) { \
	int i, ret; \
	clock_t start, end, diff; \
	start  = clock(); \
	printf("  ###  TEST %i (TIMED):   %.2f points\n", TestNum,  pts); \
	printf("        DESC: %s\n",  msg); \
	MaxPts += pts; \
	MaxPtsAuto += pts; \
	  ret = func_call; \
	end = clock(); \
	if(ret != answer){ \
	    printf("     FAILED; \n"); \
	    printf("     Returned Value      : %i\n", ret); \
	    printf("     Correct Return Value: %i\n", answer); \
	} \
	diff = end-start; \
	if(diff > max_time) { \
	    printf("     FAILED \n"); \
	    printf("     TOO SLOW!\n"); \
	    printf("     MAX-TIME ALLOWED:  %ld\n", max_time); \
	    printf("     TIME TAKEN:        %ld\n", diff); \
	    NFailed++; \
	} \
	else { \
	    printf("     PASSED\n"); \
	    printf("     MAX-TIME ALLOWED:  %ld\n", max_time); \
	    printf("     TIME TAKEN:        %ld\n", diff); \
	    Score += pts; \
	    NPassed++; \
	    ThisScore += pts; \
	} \
	printf("     Score So Far For Function: %.2f / %.2f\n", ThisScore, ThisMaxPts); \
	printf("  ###  END TEST %i\n\n", TestNum); \
	TestNum++;\
}
	
	
#define MANUAL(func_call, expected, pts) { \
	printf("  ###  TEST %i:  %s; %.2f points\n", TestNum, "\""#func_call"\"",  pts); \
	printf("  MANUAL TA TODO:  DETERMINE IF OUTPUT MATCHES EXPECTED AND ASSIGN SCORE\n\n");\
	printf("    EXPECTED OUTPUT: \n\n"); \
	printf("        %s \n\n", expected); \
	printf("    ACTUAL OUTPUT: \n\n"); \
	func_call; \
	printf("    \n END STUDENT OUTPUT: \n\n"); \
	printf("     TA REPORTED SCORE: ____ / %.2f\n", pts); \
	printf("  ###  END TEST %i\n\n", TestNum); \
	TestNum++;\
	MaxPts += pts; \
	MaxPtsManual += pts; \
}


	
	
	

#define START(func, pts) { \
    printf("~~~~ BEGIN TESTS OF %s ~~~~~\n", func); \
    ThisScore = 0.0; \
    TestNum = 1; \
    CurrFunc = func; \
    ThisMaxPts = pts; } 
	

#define END { \
    printf("~~~~ END TESTS OF %s ~~~~~\n", CurrFunc); \
    printf("~~~~     AUTO_SCORE(%21s):   %.2f / %.2f\n", CurrFunc, ThisScore, ThisMaxPts); \
    ThisScore = 0.0; ThisMaxPts=0.0; \
    cleanup(); \
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"); }

#define END_MANUAL { \
    printf("~~~~ END TESTS OF %s ~~~~~\n", CurrFunc); \
    printf("~~~~   TA TODO:  ENTER TOTAL POINTS FOR MANUAL TESTS ABOVE\n\n"); \
    printf("~~~~   MANUAL_SCORE(%21s):   ______ / %.2f\n", CurrFunc,  ThisMaxPts); \
    ThisScore = 0.0; ThisMaxPts=0.0; \
    cleanup(); \
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n"); }

void report() {
	printf("\n\n #####   TESTS_COMPLETED ######  \n");
	printf("\n\n    FINAL RESULTS OF TESTS:  \n");

	printf("\n\n        AUTOSCORED:    %.2f / %.2f\n", Score, MaxPtsAuto);

	printf("\n\n          AUTO TESTS PASSED:  %i\n", NPassed);
	printf("          AUTO TESTS FAILED:  %i\n", NFailed);

	if(MaxPtsManual > 0.0){
		printf("\n\n        POINTS NEEDING HUMAN EVAL:   %.2f \n\n", MaxPtsManual);
		printf("\n\n        TA INSTRUCTIONS:  TALLY HUMAN-SCORED TOTAL BELOW\n\n");

		printf("\n\n            HUMAN-EVAL:    ______ / %.2f\n\n", MaxPtsManual);

		printf("\n\n            GRAND-TOTAL:    ______ / %.2f\n\n", MaxPtsManual+MaxPts);

		printf("\n\n            TA DOING EVALUATION:  ____________________________\n\n");
	}
}

void cleanup(){
int i;
}

  

void parray(int a[], int n) {
int i;

  printf("[ ");
  for(i=0; i<n; i++) {
    printf(" %i ", a[i]);
  }
  printf("]\n");
}


  

  
  
int arrays_eq(int *a, int *b, int n) {
int i;

  for(i=0; i<n; i++){ 
	if(a[i] != b[i])
	  return 0;
  }
  return 1;
}


int num_occ(int a[], int n, int x) {
  int matches=0;
  int i;

  for(i=0; i<n; i++) {
    if(a[i]==x) matches++;
  }
  return matches;
}

int same_contents_arr(int a[], int b[], int n) {
int i, x;

  for(i=0; i<n; i++) {
	x = a[i];
	if(num_occ(a, n, x) != num_occ(b, n, x))
		return 0;
  }
  return 1;
}





clock_t Fudge = 1;


void cal_unit_fudge() {
  Fudge = 1;
}
void cal_big_fudge() {
  Fudge = 4;
}
void cal_huge_fudge() {
  Fudge = 8;
}
void cal_custom_fudge(clock_t fudge) {
  Fudge = fudge;
}





clock_t calibrate_constant(int ntrials) {
clock_t start, end, diff;
JUNK * a;
int i;

  start = clock();
  while(ntrials) {
    a = malloc(sizeof(JUNK));
    a->a = 1;
    a->b = 1;
    a->c = 1;
    free(a);
    ntrials--;
  }
  end = clock();

  diff = end - start;
  return Fudge * diff;
}

clock_t calibrate_linear(int n, int ntrials) {
  clock_t start, end, diff;
  JUNK **a;
  int i;

  start = clock();
  while(ntrials) {
    a = malloc(n*sizeof(JUNK *));
    for(i=0; i<n; i++) {
      a[i] = malloc(sizeof(JUNK));
      a[i]->a = 1;
      a[i]->b = 1;
      a[i]->c = 1;
    }
    for(i=0; i<n; i++) {
      free(a[i]);
    }
    free(a);
    ntrials--;
  }
  end = clock();

  diff = end - start;
  return Fudge * diff;
}
  
void logn(int idx, JUNK **a) {

  a[idx]->a = 3*idx;
  a[idx]->b = 3*idx+a[idx]->a;
  a[idx]->c = (a[idx]->a)*(a[idx]->b);
  
  if(idx > 0)
    logn(idx/2, a);
}


clock_t calibrate_nlogn(int n, int ntrials) {
  clock_t start, end, diff;
  JUNK **a;
  int i, k;

  start = clock();
  while(ntrials) {
    a = malloc(n*sizeof(JUNK *));
    for(i=0; i<n; i++) {
      a[i] = malloc(sizeof(JUNK));
    }
    for(i=0; i<n; i++) {
      k = n;
      logn(n-1, a);
    }
    for(i=0; i<n; i++) {
      free(a[i]);
    }
    free(a);
    ntrials--;
  }
  end = clock();

	diff = end - start;
	if(diff==0)
	  printf("calibrate_nlogn warning: elapsed time = 0?\n");
  return Fudge * diff;
}
  




  



void size_sanity(BST *t);

int max_sb_height(int n);

void bst_report(BST *t) {

  printf("BST REPORT: \n");
  printf("   n      = %i\n", bst_size(t));
  printf("   height = %i\n", bst_height(t));
  printf("   work   = %i\n", bst_sb_work(t));
  printf("   height-upper-bound: %i\n", 
               max_sb_height(bst_size(t)));
  printf("END BST REPORT: \n\n");

}

/* function:  max_sb_height
 ** desc:      returns maximum possible height of a
 **            size-balanced tree with n nodes.
 **
 ** Idea:  if you have a size-balanced tree with n
 **        nodes, it can't be any taller than what
 **        this function reports.
 **/
int max_sb_height(int n) {
  unsigned int big;

  if(n<=0) return -1;
  if(n==1) return 0;
  big = (n-1) - (n/3);  
  // makes as imbalanced as possible within rules
  //    of being size-balanced
  //
  return 1 + max_sb_height(big);
}
