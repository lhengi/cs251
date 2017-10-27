//
//  main.c
//  hw3
//
//  Created by Heng Li on 10/18/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    double x;
    double y;
}Point;

int compare_by_x(Point* a, Point* b)
{
    if(a->x < b->x)
    {
        return -1;
    }
    
    if(a->x > b->x)
        return 1;
    
    if(a->y < b->y)
        return -1;
    return 1;
    
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    Point points[] = {{2.9,1.1},{0.8,2.3},{2.9,0.6},{1.1,3.14},{0.8,4.6} };
    
    int i;
    for(i = 0; i < 5; i++)
    {
        printf("%lf\t%lf\n",points[i].x,points[i].y);
    }
    printf("\n\nSorted\n\n");
    qsort(points, 5, sizeof(Point), compare_by_x);
    for(i = 0; i < 5; i++)
    {
        printf("%lf\t%lf\n",points[i].x,points[i].y);
    }
    
    
    
    return 0;
}
