//
//  main.c
//  test
//
//  Created by Heng Li on 9/30/17.
//  Copyright © 2017 Heng Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>




int main ()
{
    char str[] ="This\n";
    char * pch;
    char* pch2;
    //printf ("Splitting string \"%s\" into tokens:\n\n`",str);
    printf("string: %s",str);
    pch = strtok (str,"\n");
    pch2 = strtok(NULL, "");
    
    printf("pch %s",pch);
    int i;
    while (pch[i] != '\0')
    {
        printf("%c",pch[i]);
        i++;
    }
    printf("pch2 %strt",pch2);
    
    while (pch != NULL)
    {
        printf ("%s\n",pch);
        pch = strtok (NULL, " ");
    }
    
    if(strcmp("this\n", "this") == 0)
    {
        printf("Same\n");
    }
    printf("===========================\n\n\n");
    char** twoD;
    twoD = malloc(sizeof(char*)*3);
    char* index0 = malloc(sizeof(char)*8);
    index0 = "1234567\0";
    char* index1 = malloc(sizeof(char)*5);
    index1 = "1234\0";
    twoD[0] = "abcdef";
    twoD[1] = "zbcd";
    printf("index0 %s\n",twoD[0]);
    printf("index1 %s\n",twoD[1]);
    
    
    
    
    return 0;
}


