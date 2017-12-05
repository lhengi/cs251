//
//  main.c
//  program5
//
//  Created by Heng Li on 12/04/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "hmap.h"

typedef struct Node
{
    int basicFile;
    int timeStamp;
    int outDegree;
    char* filename;
    struct Node** dependencyFiles;
}Node;

typedef struct Graph
{
    int num_vertex;
    // hash map of vertexiesc
    HMAP* hmap;
}Graph;

Graph* graphCreate()
{
    
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertex = 0;
    graph->hmap = hmap_create(2048,0.75);
    return graph;
    
}





int main(int argc, const char * argv[])
{
    // insert code here...
    printf("Hello, World!\n");
    
    int index = 1;
    char* word;
    
    return 0;
}
