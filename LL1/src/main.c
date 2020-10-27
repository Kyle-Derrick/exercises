#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "queue.h"

typedef struct{
    char *str;
    size_t len;
} Word;

typedef struct{
    Word *left;
    Word *right;
} Produc;

const char *ARROW = "➜";
const char *EPSILON = "ε";

//open 
FILE *get_file(int argc, char *argv[]);
Word *queue_to_word(Queue *qe);
Word *get_infer(FILE *fp);
size_t scan_row(FILE *fp, size_t col);


int main(int argc, char *argv[])
{
    FILE *fp = get_file(argc, argv);
    Word *infer = get_infer(fp);

    
    // queue_destory(queue, DELETE_WITH_VALUE);

    //close all resource
    fclose(fp);
    free(infer->str);
    free(infer);
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

Word *queue_to_word(Queue *qe)
{
    if (!qe || !qe->size)
    {
        return NULL;
    }
    
    queue_add(qe, "\0", CREATE_NEW_VALUE);
    Word *word = malloc(sizeof(Word));
    word->str = queue_to_array_all(qe, CREATE_NEW_VALUE);
    word->len = qe->size;
    return word;
}

Word *get_infer(FILE *fp)
{
    int ch = -1;
    Queue *inferQueue = new_queue(sizeof(char));
    while ((ch = fgetc(fp)) != ',')
    {
        if (ch == EOF)
        {
            perror("Analysis table file is error!");
            exit(1);
        }
        
        queue_add(inferQueue, &ch, CREATE_NEW_VALUE);
    }
    Word *word = queue_to_word(inferQueue);
    queue_destory(inferQueue, DELETE_WITH_VALUE);
    
    return word;
}

size_t scan_row(FILE *fp, size_t col)
{
    long off = ftell(fp);

    char ch;
    size_t row = 0;
    size_t coltmp = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '\n')
        {
            row++;
            if (coltmp != col - 1)
            {
                perror("the analysis table file's struct is wrrong!");
                exit(1);
            }
            
            coltmp = 1;
        }else if (ch == ',')
        {
            coltmp++;
        }
    }
    if (coltmp == col - 1)
    {
        row++;
    }
    
    fseek(fp, off, SEEK_SET);
    return row;
}

void *table_head(FILE *fp)
{
    char ch;
    //获取表头
    Queue *colHead = new_queue(sizeof(Word));
    Queue *tmp = NULL;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == ',' || ch == '\n')
        {
            Word *word;
            if (word = queue_to_word(tmp))
            {
                queue_destory(tmp, DELETE_WITH_VALUE);
                queue_add(colHead, word, NONE_FLAGS);
                tmp = NULL;
            }
            
            if (ch == '\n')
            {
                break;
            }else
            {
                continue;
            }
            
        }else if (!tmp)
        {
            tmp = new_queue(sizeof(char));
        }
        queue_add(tmp, &ch, CREATE_NEW_VALUE);

        printf("%d\t%c\t", ch, ch);
    }

    size_t row = scan_row(fp, colHead->size);
    Produc table[row][colHead->size];
    Queue *rowHead = new_queue(sizeof(Word));
    for (size_t i = 0; i < row; i++)
    {
        //get the row head word
        Queue *rowHeadStr = new_queue(sizeof(char));
        while ((ch = fgetc(fp)) != ',')
        {
            queue_add(rowHeadStr, ch, CREATE_NEW_VALUE);
        }
        queue_add(rowHead, queue_to_word(rowHeadStr), NONE_FLAGS);

        while ((ch = fgetc(fp)) != EOF)
        {
            if (ch == ',' || ch == '\n')
            {
                Word *word;
                if (word = queue_to_word(tmp))
                {
                    queue_destory(tmp, DELETE_WITH_VALUE);
                    queue_add(colHead, word, NONE_FLAGS);
                    tmp = NULL;
                }
                
                if (ch == '\n')
                {
                    break;
                }else
                {
                    continue;
                }
                
            }else if (!tmp)
            {
                tmp = new_queue(sizeof(char));
            }
            queue_add(tmp, &ch, CREATE_NEW_VALUE);

            printf("%d\t%c\t", ch, ch);
        }
    }
    
}