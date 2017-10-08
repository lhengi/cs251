#include <stdio.h>
#include "list.h"




void print_and_destroy(LIST *data) {

  while(!lst_is_empty(data)) {
	printf("%i\n", lst_pop_front(data));
  }
  lst_free(data);
}

LIST * read_ints() {
int x;
LIST *data;

  data = lst_create();
    printf("Enter number until letters:\n");
  while(scanf("%i", &x) == 1) {
	lst_push_back(data, x);
  }
  return data;
}

