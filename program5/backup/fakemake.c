//
//  main.c
//  program5
//
//  Created by Heng Li on 12/04/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmap.h"

typedef struct Node
{
    int basicFile;
    int timeStamp;
    int outDegree;
    int outCapacity;
    char* filename;
    struct Node** dependencyFiles;
}Node;

typedef struct Graph
{
    int num_vertex;
    // hash map of vertexiesc
    HMAP* hmap;
}Graph;

typedef struct dependentFile
{
    int num_dependents;
    int num_cap;
    char** files;
}Target;




Graph* graphCreate()
{
    
    Graph* graph = malloc(sizeof(Graph));
    graph->num_vertex = 0;
    graph->hmap = hmap_create(2048,0.75);
    return graph;
    
}

// when creating the file, initiallize to a basic File
Node* createNode(char* fileanme)
{
    Node* node;
    node = malloc(sizeof(Node));
    node->filename = fileanme;
    node->basicFile = 1;
    node->outDegree = 0;
    node->outCapacity = 0;
    node->dependencyFiles = NULL;
    
    return node;
}

void setNotBasic(Node* node)
{
    node->basicFile = 0;
}

/*
int growArray(Node** array, int n)
{
    int i;
    if(array == 0)
    {
        array = (Node**)malloc(sizeof(Node*)*16);
        for(i = 0; i < 16; i++)
        {
            array[i] = malloc(sizeof(Node));
        }
        n = 16;
    }
    
    Node** newArray;
    
    if(node->outCapacity > node->outDegree )
        return;
    
    newArray = (Node**)malloc(sizeof(Node*)*node->outCapacity*2);
    for(i = 0; i < node->outCapacity;i++)
    {
        newArray[i] = array[i];
    }
    
    free(array);
    array = newArray;
    
}*/

Target* createTarget(char* filename)
{
    Target* tar;
    tar = malloc(sizeof(Target));
    tar->num_dependents = 0;
    tar->num_cap = 16;// space for 16 files
    tar->files = malloc(sizeof(char*)*16);
    return tar;
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

void growTarget(Target* tar)
{
    char** newArray = (char**)malloc(sizeof(char*)*tar->num_cap*2);
    int i;
    for(i = 0; i < tar->num_cap;i++)
    {
        newArray[i] = tar->files[i];
    }
    free(tar->files);
    tar->files = newArray;
    
}




// now assuming all the dependent files are already exist
void setEdges(Node* node, Node* edge)
{
    if(node->basicFile == 1)
    {
        fprintf(stderr, "This is a basic file\n");
        return;
    }
    
    //growArray(node);
    
    node->dependencyFiles[node->outDegree] = edge;
    node->outDegree++;
    

    
}



int main(int argc, const char * argv[])
{
    
    //Plan to how to read input
    //1. read all the basic and target file and store them in sperate 2d arra
    //2. then see if the file will be rejected or not
    
    
    int basic_length = 0;
    int basic_cap = 1024;
    int target_length = 0;
    int target_cap = 1024;
    
    char** basic_files = (char**)malloc(sizeof(char*)*1024);
    Target** target_files = (Target**)malloc(sizeof(Target*)*1024);
    
    FILE* files;
    files = fopen(argv[1],"r");
    if(files == NULL)
    {
        fprintf(stderr, "***Error File not found\n");
        return 0;
    }
    char* word;
    char* token;
    char* token_col;
    char* token_newline;
    while (fscanf(files, "%s",word)!= EOF)
    {
        token_newline = strtok(word, "\n");// this strips off the carriage return
        token = strtok(token_newline, " ");
        token_col = strtok(NULL, " ");
        
        
        
        if(strcmp(token_col, ":") != 0)
        {
            if(strcmp(token_col, "\0") !=0)
            {
                fprintf(stderr, "****Error This file does not have a :, and it has depend files\n Skip this file...\n");
                continue;
            }
            
            if(basic_length > basic_cap - 1)// grow the array
            {
                growChar2dArray(basic_files, basic_cap);
                basic_cap *= 2;
            }
            basic_files[basic_length] = token;
            basic_length++;
            continue;// we already know this is a basic file, because there is no ':'
        }

        while (token != NULL)
        {
            printf ("%s\n",token);
            token = strtok (NULL, " ");
        }
    }
    return 0;
}


/*
int main(int argc, const char * argv[])
{
    // insert code here...
    printf("Hello, World!\n");
    HMAP* hmap;
    hmap = hmap_create(2048, 0.75);
    
    int index = 1;
    char* word = malloc(sizeof(char)*81);
    //char* filename = argv[1];
    FILE* filesList;
    filesList = fopen(argv[1], "r");
    if(filesList == NULL)
    {
        fprintf(stderr, "Can't find the file!\n");
        return 0;
    }
    char* token;
    Node* pTemp;
    Node* edge;
    while (fscanf(filesList, "%s",word)!= EOF)
    {
        token = strtok(word, " ");
        pTemp = createNode(token);
        hmap_set(hmap, token, pTemp);
        while(token != NULL)
        {
            token = strtok(word, " ");
            if(strcmp(token, ":") == 0)
            {
                setNotBasic(pTemp);
                continue;
            }
            edge = hmap_get(hmap, token);
            setEdges(pTemp, edge);
        }
        
        free(word);
        word = malloc(sizeof(char)*81);
    }
    fclose(filesList);
    
    return 0;
}*/
