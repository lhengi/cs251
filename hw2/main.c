//
//  main.c
//  hw2
//
//  Created by Heng Li on 9/26/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>

int findMissing(int* array,int min, int max)
{
    if(array[min] == min && array[max] == max)
    {
        return -1;
    }
    
    int copy_array[17];
    int i;
    for(i = 0; i < 17; i++)
    {
        copy_array[i] = array[i];
    }
    
    
    
    int medium = (max-min)/2;
    
    int next_max = max - medium-1;
    int next_min = min + medium;
    
    if(array[next_max] < next_max && array[next_max-1] == next_max -1)
    {
        return next_max;
    }
    
    if( max < array[max] && array[max-1] == max -1)
    {
        return max;
    }
    
    if(min!= 0 && min < array[min])
    {
        return min;
    }
    else if (min == 0 && array[min] != 0)
    {
        return min;
    }
    
    if(next_max < array[next_max])
    {
        return findMissing(array, min, next_max);
    }
    else
    {
        return findMissing(array, next_min, max);
    }
    
    return -1;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int arrary[] = {0,1,2,3,4,5,6,8,9,10,11,12,13,14,15,16,17,18 };
    
    int missing = findMissing(arrary, 0, 17);
    
    //printf("Expecting 13\n");
    printf("Result: %d\n",missing);
    
    
    
    return 0;
}
