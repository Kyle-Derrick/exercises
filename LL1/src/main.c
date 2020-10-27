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

typedef struct{
    Queue *cols;
    Queue *rows;
    Produc ***table;
} LLTable;

const char *ARROW = "➜";
const char *EPSILON = "ε";

//open 
FILE *get_file(int argc, char *argv[]);
Word *queue_to_word(Queue *qe);
Word *get_infer(FILE *fp);
size_t scan_row(FILE *fp, size_t col);
Word *word_clone(Word *word);
LLTable *get_lltable(FILE *fp, Word *infer);
void destory_word(Word *word);
void *destory_word_queue(Queue* qe,_QueueNode_ *last,_QueueNode_ *now,_QueueNode_ **next,size_t index,void *arg,void *result);
void destory_lltable(LLTable *lltable);

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
            if (coltmp != col)
            {
                perror("the analysis table file's struct is wrrong!");
                exit(1);
            }
            
            coltmp = 0;
        }else if (ch == ',')
        {
            coltmp++;
        }
    }
    if (coltmp == col)
    {
        row++;
    }
    
    fseek(fp, off, SEEK_SET);
    return row;
}

Word *word_clone(Word *word)
{
    Word *w = NULL;
    if (word)
    {
        w = malloc(sizeof(Word));
        w->len = word->len;
        w->str = malloc(w->len+1);
        memcpy(w->str, word->str, w->len+1);
    }
    return w;
}

LLTable *get_lltable(FILE *fp, Word *infer)
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

        printf("%d\t%c\t\n", ch, ch);
    }

    size_t row = scan_row(fp, colHead->size);
    // Produc *table[row][colHead->size];
    Produc ***table = malloc(sizeof(Produc**)*row);
    for (size_t i = 0; i < colHead->size; i++)
    {
        *(table+i) = malloc(sizeof(Produc*)*colHead->size);
    }
    
    Queue *rowHead = new_queue(sizeof(Word));
    for (size_t i = 0; i < row; i++)
    {
        //get the row head word
        Queue *rowHeadStr = new_queue(sizeof(char));
        while ((ch = fgetc(fp)) != ',')
        {
            queue_add(rowHeadStr, &ch, CREATE_NEW_VALUE);
        }
        queue_add(rowHead, queue_to_word(rowHeadStr), NONE_FLAGS);

        Queue *tmp = NULL;
        int match = 0;
        Produc *produc = NULL;
        int col = 0;
        while (1)
        {
            ch = fgetc(fp);
            if (ch == ',' || ch == '\n' || ch == EOF)
            {
                if (tmp)
                {
                    Word *word;
                    if (word = queue_to_word(tmp))
                    {
                        queue_destory(tmp, DELETE_WITH_VALUE);
                        if (!produc)
                        {
                            produc = malloc(sizeof(Produc));
                            produc->left = word_clone(rowHead->last->value);
                        }
                        produc->right = word;
                        table[i][col] = produc;
                        produc = NULL;
                        tmp = NULL;
                    }
                }
                col++;
                
                if (ch == '\n' || ch == EOF)
                {
                    break;
                }else
                {
                    continue;
                }
                
            }else if (ch == ' ')
            {
                continue;
            }else if (!tmp)
            {
                tmp = new_queue(sizeof(char));
            }
            if (infer->str[match] == ch)
            {
                if (match == infer->len)
                {
                    queue_update_diy(tmp, NULL, tmp->size-3, tmp->size, DELETE_NODE|DELETE_WITH_VALUE);
                    Word *word;
                    if (tmp->size > 0)
                    {
                        word = queue_to_word(tmp);
                    }else
                    {
                        word = word_clone(rowHead->last->value);
                    }
                    queue_destory(tmp, DELETE_WITH_VALUE);
                    produc = malloc(sizeof(Produc));
                    produc->left = word;
                    match = 0;
                    continue;
                }else
                {
                    match++;
                }
            }
            
            queue_add(tmp, &ch, CREATE_NEW_VALUE);

            printf("%d, %d\t%c\t\n", i, ch, ch);
        }
    }
    
    LLTable *lltable = malloc(sizeof(LLTable));
    lltable->cols = colHead;
    lltable->rows = rowHead;
    lltable->table = (Produc***)table;
    return lltable;
}

void destory_word(Word *word)
{
    if (word)
    {
    printf("--------\n");
        free(word->str);
        free(word);
    }
    
}

void *destory_word_queue(Queue* qe,_QueueNode_ *last,_QueueNode_ *now,_QueueNode_ **next,size_t index,void *arg,void *result)
{
    destory_word((Word*)now);
    qe->first = *next;
}

void destory_lltable(LLTable *lltable)
{
    for (size_t i = 0; i < lltable->rows->size; i++)
    {
        for (size_t j = 0; j < lltable->cols->size; j++)
        {
            Produc *p = lltable->table[i][j];
            if (p)
            {
                destory_word(p->left);
                destory_word(p->right);
                free(p);
            }
    
        }
    }

    queue_each(lltable->cols, NULL, destory_word_queue);
    queue_each(lltable->rows, NULL, destory_word_queue);
}
