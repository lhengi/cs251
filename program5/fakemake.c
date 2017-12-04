//
//  main.c
//  program5
//
//  Created by Heng Li on 12/04/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>

typedef struct Node
{
    int timeStamp;
    char* filename;
    struct Node** dependencyFiles;
}Node;


int main(int argc, const char * argv[])
{
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
