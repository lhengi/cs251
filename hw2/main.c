//
//  main.c
//  hw2
//
//  Created by Heng Li on 9/26/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
int total_missing_called = 0;
int findMissing(int* array,int min, int max)
{
    total_missing_called++;
    if(array[min] == min && array[max] == max)
    {
        return -1;
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
        printf("Here\n");
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

int total_swap = 0;

void swap(int* a, int* b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
    
}

int ceiling(double a)
{
    if(a > (int)a)
    {
        return a + 1;
    }
    return (int)a;
}

void silly_sort(int* array, int n)
{
    if(n <= 2)
    {
        if(n == 2)
        {
            if(array[0] > array[1])
                swap(&array[0],&array[1]);
        }
        total_swap++;
        return;
    }
    
    silly_sort(&array[n/3], ceiling((2.0*n)/3));
    silly_sort(array, ceiling((2.0*n)/3));
    silly_sort(&array[n/3], ceiling((2.0*n)/3));

               
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int arrary[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,14,15,16 };
    int missing = findMissing(arrary, 0, 15);
    
    
    //printf("Expecting 13\n");
    printf("Result: %d\nRun Time: %d\n\n",missing,total_missing_called);
    
    printf("begin silly_sort\n\n");
    
    int silly_array[] = {999,43,6,2,1,5,7,3,3,2,5,6,2,1,4,3,6,2,435,35,8,1,9,5,2};
    
    silly_sort(silly_array, 25);
    int i;
    for(i = 0; i < 25; i++)
    {
        printf(" %d ",silly_array[i]);
    }
    
    printf("\ntotal_swap %d\n",total_swap);
    
    total_swap = 0;
    
    int silly_2[] = {6,5,4,3,2,1};
    silly_sort(silly_2, 14);
    printf("total_swap %d\n",total_swap);
    
    
    
    return 0;
}
