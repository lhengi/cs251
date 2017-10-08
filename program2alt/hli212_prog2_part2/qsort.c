//
//  qsort.c
//  program2alt
//
//  Created by Heng Li on 10/07/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include "io.h"
#include "list.h"

LIST *my_qsort(LIST *data)
{
    if(lst_length(data) <= 1)
    {
        return data;
    }
    
    int pivit = lst_pop_front(data);
    LIST* less_pivit = lst_filter_leq(data, pivit);
    
    // Now
    // less_pivit has everyting less than or equal to pivit, But excluding pivit
    // data has everything greater than pivit
    
    less_pivit = my_qsort(less_pivit);
    data = my_qsort(data);
    
    lst_push_back(less_pivit, pivit);
    lst_concat(less_pivit, data);
    return less_pivit;
    
}

int main(){
    LIST *data;
    
    
    data = read_ints();
    data = my_qsort(data);
    print_and_destroy(data);
    
}
