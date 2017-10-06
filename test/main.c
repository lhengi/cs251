//
//  main.c
//  test
//
//  Created by Heng Li on 9/30/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>

int f(int n)
{
    if(n == 0)
    {
        return 0;
        
    }
    if(n == 1)
        return 1;
    
    return f(n - 1) + f(n - 2);
}


int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    char line[] = {'1','2','\0'};
    int i = 0;
    int number = 0;
    int first_pro;
    int place = 1;
    while(line[i] >= 48 && line[i] <= 57)
    {
        first_pro = line[i] - 48;
        //printf("first_pro%d\n",first_pro);
        number += first_pro * place;
        place *= 10;
        i++;
    }
    //printf(" %d ",number);
    
    int reverse = 0;
    int remain;
    while(number != 0)
    {
        remain = number%10;
        reverse = reverse * 10 + remain;
        number /= 10;
        
    }
    printf("%d\n",reverse*reverse);
    return 0;
}
