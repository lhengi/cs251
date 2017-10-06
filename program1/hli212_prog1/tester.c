#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define FREE(x) lst_free(x)

/*
1 lst_print_rev
3 lst_pop_back
5 lst_is_sorted
7 lst_length
9 lst_clone
11 lst_to_array
13 lst_filter_leq
*/

void print_arr(int *arr, int n) {
		int i = 0;
		printf("[");
		for(; i < n; i++) {
			printf(" %d ", arr[i]);
		}
		printf("]\n");
}

int main() {
    printf("REMINDER: This test suite is NOT exhaustive\n");
    printf("   Passing all of these tests does NOT mean you will get 100%% on the project.\n");
    srand(time(NULL));
    
    LIST* main_list = lst_create();
    lst_push_front(main_list, 2);
    printf("Print the original list\n");
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    printf("Print the list after insert_order adding 3\n");
    lst_insert_sorted(main_list, 3);
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    printf("Insert in order another 2\n");
    lst_insert_sorted(main_list, 2);
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    printf("Insert in order 1 and 3\n");
    lst_insert_sorted(main_list, 1);
    printf("List size (1): %d\n",lst_length(main_list));
    lst_insert_sorted(main_list, 3);
    printf("List size (2): %d\n",lst_length(main_list));
    lst_print(main_list);
    printf("push front 8, push back 10  then insert another 7\n");
    printf("Expecting 7 8 1 2 2 3 3 10\n");
    lst_push_front(main_list, 8);
    lst_push_back(main_list,10);
    lst_insert_sorted(main_list, 7);
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    printf("Looks like lst_insert_sorted passed the test\n");
    
    
    
    
    
    printf("***Test lst_are_equal via lst_clone the main_list***\n");
    LIST* new_main_list = lst_clone(main_list);
    printf("The new_main_list: Expecting 7 8 1 2 2 3 3 10\n");
    lst_print(new_main_list);
    printf("new_main_list, List size: %d\n",lst_length(new_main_list));
    int lst_eq = lst_are_equal(main_list, new_main_list);
    printf("lst_are_equal returned: %d\n Change a node in new_main_list 1 to 0\n ",lst_eq);
    new_main_list->front->next->next->val = 0;
    lst_print(new_main_list);
    printf("Compare again with main_list, returned value: %d\n",lst_are_equal(main_list, new_main_list));
    printf("Looks like lst_clone and lst_are_equal passed the test\n");
    
    
    
    
    
    printf("\n\n***Test lst_count and lst_pop_back***\n");
    printf("use lst_count to count how many 2 in the new_main_list, Expecting: 2, returned: %d\n",lst_count(new_main_list, 2));
    printf("use lst_count to count how many 3 in the new_main_list, Expecting: 2, returned: %d\n",lst_count(new_main_list, 3));
    lst_push_back(new_main_list, 3);
    printf("add one more three to the end of list then call lst_count,Expecting: 3, returned: %d\n",lst_count(new_main_list, 3));
    printf("count how many 10 in the new_main_list,  Expecting: 1, returned: %d\n",lst_count(new_main_list, 10));
    printf("pop_back two times, take out 10, 3, Then call lst_count on 3 and 10 again\n");
    lst_pop_back(new_main_list);
    lst_pop_back(new_main_list);
    printf("Expecting: lst_count(3) = 2\tlst_count(10) = 0 \n");
    printf("Returned:  lst_count(3) = %d\tlst_count(10) = %d\n",lst_count(new_main_list, 3),lst_count(new_main_list, 10));
    printf("The new list: ");
    lst_print(new_main_list);
    printf("Reverse print: ");
    lst_print_rev(new_main_list);
    
    printf("\n\n*** testing lst_from_array and lst_to_array***\n\n");
    
    ElemType* main_array = malloc(sizeof(int));
    main_array[0] = 90;
    ElemType main_array_length = 1;
    printf("Testing array with length 1, contains: 90\n");
    LIST* lst_main_array = lst_from_array(main_array, main_array_length);
    printf("Expecting: []  and lst_main_array size = 1\n");
    printf("Result: "); lst_print(lst_main_array); printf("lst_main_array size = %d\n",lst_length(lst_main_array));
    
    printf("use lst_to_array to populate main_array with new_main_list\n");
    free(main_array);
    main_array = lst_to_array(new_main_list);
    printf("Expecting the new array to be 7 8 0 2 2 3 3\n");
    int k;
    printf("The new array: ");
    for(k = 0; k < lst_length(new_main_list);k++)
    {
        printf(" %d",main_array[k]);
    }
    printf("\nUse lst_from_array to populate a list with main_array\n");
    FREE(lst_main_array);
    lst_main_array = lst_from_array(main_array, lst_length(new_main_list));
    printf("The new linked list is: \n");
    lst_print(lst_main_array);
    printf("Looks like lst_from_array and lst_to_array passed the test\n\n");
    
    printf("***new_main_list:");lst_print(new_main_list);
    printf("***List size: %d\n",lst_length(new_main_list));
    
    
    
    printf("\n***Test lst_prefix and lst_concat and lst_reverse***\n");
    
    LIST* prefix_new_main_list = lst_prefix(new_main_list, 4);
    printf("new prefix list should be: 7  8  0  2\n");
    printf("Result:");lst_print(prefix_new_main_list);
    printf("after lst_prefix old like should be:  2  3  3\n");
    printf("Result:");lst_print(new_main_list);
    //printf("***new_main_list:");lst_print(new_main_list);
    //printf("***List size: %d\n",lst_length(new_main_list));
    
    LIST* new_prefix_list = lst_prefix(prefix_new_main_list, 5);
    printf("call lst_prefix on the new list with k = 5, Expecting 7  8  0  2\n");
    printf("Result lst:");lst_print(new_prefix_list);
    printf("Expecting old lst to be: []");
    printf("Result old lst:");lst_print(prefix_new_main_list);
    
    printf("Reverse the result lst, Expecting 2 0 8 7\n");
    lst_reverse(new_prefix_list);
    printf("Result:");lst_print(new_prefix_list);
    printf("Now call lst_print_rev, Expecting: 7 8 0 2\n");
    printf("Result:");lst_print_rev(new_prefix_list);
    
    printf("call lst_prefix on new_main_list with k = 1: Expecting: [2]\n");
    LIST* prefix_1_new_main = lst_prefix(new_main_list, 1);
    printf("Result:");lst_print(prefix_1_new_main);
    printf("Result in reverse: Expecting: 2\n Result:");lst_print_rev(prefix_1_new_main);
    printf("Expecting old lst to be: 3  3\n");
    printf("Reculst:");lst_print(new_main_list);
    
    //printf("***new_main_list:");lst_print(new_main_list);
    //printf("***List size: %d\n",lst_length(new_main_list));
    
    
    printf("\nChange the second 3 to 6 then reverse, Expecting: 6  3\n");
    new_main_list->front->next->val = 6;
    lst_reverse(new_main_list);
    printf("Result:");lst_print(new_main_list);
    printf("call lst_print_rev on the list, Expecting: 3  6\n");
    printf("Result:");lst_print_rev(new_main_list);
    
    printf("\nconcat 2 0 8 7 to 2\n");
    printf("Expecting:  2  2  0  8  7\n");
    lst_concat(prefix_1_new_main, new_prefix_list);
    printf("Result:");lst_print(prefix_1_new_main);
    
    printf("concat 2 2 0 8 7 to 6 3, Expecting: 6  3  2  2  0  8  7  \n");
    lst_concat(new_main_list, prefix_1_new_main);
    printf("Result:");lst_print(new_main_list);
    printf("***new_main_list:");lst_print(new_main_list);
    printf("***List size: %d\n",lst_length(new_main_list));
    
    
    printf("\nconcate again with a list with length 0, Expecting  6  3  2  2  0  8  7 \n");
    lst_concat(new_prefix_list, new_main_list);
    printf("Result:");lst_print(new_prefix_list);
    printf("Result of list b:");lst_print(new_main_list);
    printf("change place new_main_list and new_prefix_list \n");
    printf("Expecting new_main_list to be:  6  3  2  2  0  8  7\n ");
    lst_concat(new_main_list, new_prefix_list);
    printf("new_main_list:");lst_print(new_main_list);
    printf("Expecting new_prefix_list to be: []\n");
    printf("new_prefix_list:");lst_print(new_prefix_list);
    
    
    printf("\n\n*** Test lst_filter_leq  and  remove all fast ***\n");
    printf("***new_main_list:");lst_print(new_main_list);
    printf("***List size: %d\n",lst_length(new_main_list));
    
    printf("Add five 5 to new_main_list 2 front, 3 back\n");
    lst_push_back(new_main_list, 5);
    lst_push_back(new_main_list, 5);
    lst_push_back(new_main_list, 5);
    lst_push_front(new_main_list, 5);
    lst_push_front(new_main_list, 5);
    lst_print(new_main_list);
    printf("List size: %d\n",lst_length(new_main_list));
    printf("filter cuttoff 5\n");
    lst_filter_leq(new_main_list, 5);
    lst_print(new_main_list);
    printf("List size: %d\n",lst_length(new_main_list));
    printf("Add five 5 to new_main_list 2 front, 3 back\n");
    lst_push_back(new_main_list, 5);
    lst_push_back(new_main_list, 5);
    lst_push_back(new_main_list, 5);
    lst_push_front(new_main_list, 5);
    lst_push_front(new_main_list, 5);
    printf("filter cuttoff at 4\n");
    lst_filter_leq(new_main_list, 4);
    lst_print(new_main_list);
    printf("call remove all fast  x= 5 \n");
    lst_remove_all_fast(new_main_list, 5);
    lst_print(new_main_list);
    printf("call remove all fast x = 10, result should not change\n");
    lst_remove_all_fast(new_main_list, 10);
    lst_print(new_main_list);
    printf("List size: %d\n",lst_length(new_main_list));
    
    printf("\nmain_list:");lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    printf("add three 2 with insert sorted, Expecting:  2  2  2  7  8  1  2  2  3  3  10\n");
    lst_insert_sorted(main_list, 2);
    lst_insert_sorted(main_list, 2);
    lst_insert_sorted(main_list, 2);
    printf("Result:");
    lst_print(main_list);
    
    printf("remove all fast, x = 2, Expecting:  7  8  1  3  3  10\n");
    lst_remove_all_fast(main_list, 2);
    printf("Result");
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    
    printf("remove all fast, x = 7, x = 8, Expecting 1  3  3  10\n");
    lst_remove_all_fast(main_list, 7);
    lst_remove_all_fast(main_list, 8);
    printf("Result:");
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    
    printf("\n\n ****  Test merge sorted *****\n");
    
    printf("new_main_list:");lst_print(new_main_list);
    printf("List size: %d\n",lst_length(new_main_list));
    
    printf("\nmain_list:");lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    
    printf("lst_insert_sorted: 0 , 1 , 2 , 3 , 4 , 7 , 8 to main_list\n");
    lst_insert_sorted(main_list, 0);
    lst_insert_sorted(main_list, 1);
    lst_insert_sorted(main_list, 2);
    lst_insert_sorted(main_list, 3);
    lst_insert_sorted(main_list, 4);
    lst_insert_sorted(main_list, 7);
    lst_insert_sorted(main_list, 8);
    lst_print(main_list);
    printf("List size: %d\n",lst_length(main_list));
    
    
    printf("Change new_main_list from 6  8  7  to 6  7  7\n");
    new_main_list->front->next->val = 7;
    printf("new main list:");
    lst_print(new_main_list);
    
    
    printf("Merge main_list to new_main_list\n");
    lst_merge_sorted(new_main_list, main_list);
    printf("Expecting:  0  1  1  2  3  3  4  6  7  7  7  8  10\n");
    printf("result:");
    lst_print(new_main_list);
    printf("Another test with merge 1  8  to 0  3 \n");
    LIST* list1 = lst_create();
    lst_push_back(list1, 0);
    lst_push_back(list1, 3);
    LIST* list2 = lst_create();
    lst_push_back(list2, 1);
    lst_push_back(list2, 8);
    lst_merge_sorted(list1, list2);
    lst_print(list1);


return 0;
}

