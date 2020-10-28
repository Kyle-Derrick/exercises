#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "llbase.h"
#include "lltable.h"


const char *ARROW = "➜";
const char *EPSILON = "ε";

//open 
FILE *get_file(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    FILE *fp = get_file(argc, argv);
    Word *infer = get_infer(fp);

    LLTable *lltable = get_lltable(fp, infer);
    
    // queue_destory(queue, DELETE_WITH_VALUE);

    //close all resource
    fclose(fp);
    free(infer->str);
    free(infer);
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