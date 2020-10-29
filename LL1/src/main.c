#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "llbase.h"
#include "lltable.h"
#include "llanalysis.h"

//open 
FILE *get_file(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    FILE *fp = get_file(argc, argv);

    LLTable *lltable = get_lltable(fp);
    
    char sentence[4096];
    while (1)
    {
        printf("input:\n");
        fgets(sentence, 4096, stdin);

        size_t len = strlen(sentence);
        if (len < 1)
        {
            continue;
        }
        
        sentence[len-1] = '\0';
        if (!strcmp(sentence, "exit"))
        {
            break;
        }
        
        analysis(sentence, lltable);
    }
    
    // queue_destory(queue, DELETE_WITH_VALUE);

    //close all resource
    fclose(fp);
    destory_lltable(lltable);
}

FILE *get_file(int argc, char *argv[])
{
    if (argc < 2)
    {
        perror("Not file found!");
        exit(1);
    }
    char *fn = argv[1];
    FILE *fp = NULL;
    if (!(fp = fopen(fn, "r")))
    {
        perror("Error when open the file!");
        exit(1);
    }
    return fp;
}