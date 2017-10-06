//
//  main.c
//  game
//
//  Created by Heng Li on 9/25/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
int total_swap = 0;
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    
    total_swap++;
}

int is_sort(int* array)
{
    int size = 200;
    int i;
    for(i = 0; i< 199; i++)
    {
        if(array[i] > array[i+1])
        {
            return 0;
        }
    }
    return 1;
}

void recur(int* array)
{
    
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    
    int array[] = {180,37,114,25,96,111,57,110,47,72,11,106,20,55,107,163,185,144,178,113,168,198,76,36,2,199,186,99,200,102,84,147,44,104,32,50,43,155,176,125,30,34,13,150,79,129,21,58,3,103,131,197,91,67,135,115,53,42,142,193,191,23,1,120,70,29,80,82,86,124,61,149,66,162,108,137,26,136,152,93,119,10,138,154,41,117,112,56,182,9,174,173,127,60,166,196,45,116,18,123,16,5,88,190,27,59,184,194,94,71,97,6,183,181,122,98,140,51,92,38,28,78,177,160,22,192,132,188,87,69,189,65,64,52,171,40,133,169,75,8,73,187,195,48,89,151,54,63,90,33,68,81,118,24,159,7,146,15,4,156,31,134,35,109,62,158,95,143,12,74,77,17,126,139,128,101,39,100,14,172,167,49,175,141,145,19,130,170,148,179,165,157,83,161,153,121,105,46,85,164};
    
    int a = 0;
    int b = 1;
    swap(&a, &b);
    printf("a%d, b%d\n",a,b);
    
    int index = -1;
    int inde = 0;
    
    while(!is_sort(array))
    {
        index++;
        if(array[index] > array[index+1])
        {
            swap(&array[index], &array[index+1]);
        }
        
        if(index > 199)
        {
            index = -1;
        }
        if(index%20 == 0)
        {
            for(inde = 0; inde < 200; inde++)
            {
                printf(" %d",array[inde]);
            }
            printf("\nNum Swap, %d\n",total_swap);
        }
        
    }
    
    for(inde = 0; inde < 200; inde++)
    {
        printf(" %d",array[inde]);
    }
    printf("\nNum Swap, %d\n",total_swap);
    
    
    
    
    return 0;
}
