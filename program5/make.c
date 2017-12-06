//
//  make.c
//  program5
//
//  Created by Heng Li on 12/06/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmap.h"


typedef struct target
{
    int file_size;
    int file_cap;
    char* target_name;
    char** files;
}Target;

Target* createTarget(char* filename)
{
    Target* tar;
    tar = malloc(sizeof(Target));
    tar->file_size = 0;
    tar->file_cap = 16;
    tar->target_name = filename;
    tar->files = (char**)malloc(sizeof(char*)*16);
    return tar;
}

typedef struct Node
{
    char* filename;
    int basic; // if it is a basic file then = 1, 0 otherwise
    int outdegree;
    int last_time;
    struct Node** edges;
}Node;

typedef struct Graph
{
    int total_vertexs;
    int clock;
    HMAP* map;
}Graph;

Node* createNode(char* filename,int basic)
{
    Node* newNode;
    newNode = malloc(sizeof(Node));
    newNode->filename = filename;
    newNode->basic = basic;
    
    newNode->outdegree = 0;
    newNode->edges = NULL;
    
    return newNode;
}

void insertEdge(Node* vertex, Node* edge)
{
    if(vertex->basic == 1)
    {
        fprintf(stderr, "You are trying to insert an edge to a basic file\n***Are you out of your mind\n");
        return;
    }
    vertex->edges[vertex->outdegree] = edge;
    vertex->outdegree++;
}

void updateClock(Graph* graph)
{
    graph->clock++;
}
int getTime(Graph* graph)
{
    return graph->clock;
}

void touch(Graph* graph, char* filename )
{
    Node* vertex = hmap_get(graph->map, filename);
    if(vertex->basic == 0)
    {
        fprintf(stderr, "*** You cannot touch a non basic file\n");
        return;
    }
    vertex->last_time = graph->clock;
    // as of now auto update the clock
    updateClock(graph);
}

// n is the capacity
void growChar2dArray(char** array, int n)
{
    char** newArray;
    newArray = (char**)malloc(sizeof(char*)*n*2);
    int i;
    for(i = 0; i < n*2; i++)
    {
        newArray[i] = malloc(sizeof(char)*81);
        newArray[i][80] = '\0';
    }
    
    for(i = 0; i < n; i++)
    {
        strcpy(newArray[i], array[i]);
        free(array[i]);
    }
    free(array);
    array = newArray;
}

void growArrayInTar(Target* tar)
{
    int i;
    char** newArray;
    newArray = (char**)malloc(sizeof(char*)*tar->file_cap*2);
    for(i = 0; i < tar->file_cap; i++)
    {
        newArray[i] = tar->files[i];
    }
    tar->file_cap *= 2;
    free(tar->files);
    tar->files = newArray;
}

void growTar2dArray(Target** array, int n)
{
    Target** newArray;
    newArray = (Target**)malloc(sizeof(Target*)*n*2);
    int i;
    for(i = 0; i<n;i++)
    {
        newArray[i] = array[i];
    }
    free(array);
    array = newArray;
    
}

int main(int argc, const char * argv[] )
{
    int basic_length =0;
    int basic_cap = 1024;
    char** basic_files;
    basic_files = malloc(sizeof(char*)*basic_cap);
    
    int target_length = 0;
    int target_cap = 1024;
    Target** target_files;
    target_files = malloc(sizeof(Target*)*target_cap);
    
    FILE* input_file;
    input_file = fopen(argv[1], "r");
    if (input_file == NULL)
    {
        fprintf(stderr, "Can't find the file\n");
        return 0;
    }
    
    char* line;
    char* token;
    char* token2;
    Target* tempTar;
    int tar_index;
    while (fscanf(input_file, "%s",line) != EOF)
    {
        line = strtok(line, "\n");// strip out the carrige return first
        token = strtok(line, " ");
        token2 = strtok(NULL, " ");
        if(strcmp(token2, "\0") != 0 && strcmp(token2, ":") != 0)// then this is a undertermined file with no colon but mutiple files on same line
        {
            fprintf(stderr, "Unrecognized file type, skipping this file\n");
            continue;
        }
        
        if(strcmp(token2, ":") != 0)
        {
            if(basic_length + 2 >= basic_cap)// + 2 just to be sure
            {
                growChar2dArray(basic_files, basic_cap);
                basic_cap *= 2;
            }
            basic_files[basic_length] = token;
            basic_length++;
            continue; // determined this file is a basic file
        }
        
        // the rest is correct target file
        
        tar_index = 0;
        token = strtok(NULL, " ");
        if(strcmp(token, "\0") == 0)
        {
            fprintf(stderr, "Faulty target file, no dependent file\n");
            continue;
        }
        tempTar = createTarget(token);
        if(tempTar->file_size + 2 >= tempTar->file_cap)
        {
            growChar2dArray(tempTar->files, tempTar->file_cap);
            tempTar->file_cap *= 2;
        }
        
        tempTar->files[tar_index] = token;
        tempTar->file_size++;
        tar_index++;
        while(token != NULL)
        {
            token = strtok(NULL, " ");
            if(tempTar->file_size + 2 >= tempTar->file_cap)
            {
                growChar2dArray(tempTar->files, tempTar->file_cap);
                tempTar->file_cap *= 2;
            }
            
            tempTar->files[tar_index] = token;
            tempTar->file_size++;
            tar_index++;
        }
        
        //add the new target to the target array
        if(target_length + 2 >= target_cap)
        {
            growTar2dArray(target_files, target_cap);
            target_cap *= 2;
        }
        target_files[target_length] = tempTar;
        target_length++;
    }
    fclose(input_file);// we already have all the files
    
    // Node it's time to add to the graph
    
    
    return 0;
}
