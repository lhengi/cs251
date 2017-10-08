#include <stdio.h>
#include "io.h"
#include "list.h"


// unimplemented
LIST * shuffle(LIST *data) {

  return data;


}

LIST *my_msort(LIST *data) {
LIST *left, *right, *answer;

  if(lst_length(data) <= 1)
	return data;

  left = lst_prefix(data, lst_length(data)/2);

  right = data;

  left  = my_msort(left);
  right = my_msort(right);

  lst_merge_sorted(left, right);
  lst_free(right);  // right empty, no longer needed

  return left;
}

int main(){
LIST *data;


  data = read_ints();
  data = my_msort(data);
  print_and_destroy(data);
 
    return 1;
}

  
