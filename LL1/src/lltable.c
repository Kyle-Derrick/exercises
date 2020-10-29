#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "llbase.h"
#include "lltable.h"

Word *get_infer(FILE *fp);
size_t scan_row(FILE *fp, size_t col);
LLTable *get_lltable(FILE *fp);
void destory_lltable(LLTable *lltable);

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

LLTable *get_lltable(FILE *fp)
{
    Word *infer = get_infer(fp);
    printf("Debug: infer: %s, %d\n", infer->str, infer->len);

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
            
        }else if (ch == '\r'||ch==' ')
        {
            continue;
        }else if (!tmp)
        {
            tmp = new_queue(sizeof(char));
        }
        queue_add(tmp, &ch, CREATE_NEW_VALUE);
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
                            produc->left = word_clone(queue_get(rowHead, i));
                        }
                        if (!strcmp(word->str, EPSILON))
                        {
                            destory_word(word);
                            word = NULL;
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
                
            }else if (ch == ' '||ch == '\r')
            {
                continue;
            }else if (!tmp)
            {
                tmp = new_queue(sizeof(char));
            }
            if (infer->str[match] == ch)
            {
                match++;
                if (match == infer->len)
                {
                    queue_update_diy(tmp, NULL, tmp->size-infer->len+1, tmp->size, DELETE_NODE|DELETE_WITH_VALUE);
                    Word *word;
                    if (tmp->size > 0)
                    {
                        word = queue_to_word(tmp);
                    }else
                    {
                        word = word_clone(queue_get(rowHead, i));
                    }
                    queue_destory(tmp, DELETE_WITH_VALUE);
                    produc = malloc(sizeof(Produc));
                    produc->left = word;
                    tmp = new_queue(sizeof(char));
                    match = 0;
                    continue;
                }
            }else
            {
                match = 0;
            }
            
            queue_add(tmp, &ch, CREATE_NEW_VALUE);
        }
    }
    
    LLTable *lltable = malloc(sizeof(LLTable));
    lltable->cols = colHead;
    lltable->rows = rowHead;
    lltable->table = (Produc***)table;
    lltable->infer = infer;
    return lltable;
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
        free(lltable->table[i]);
    }

    free(lltable->table);
    destory_word(lltable->infer);
    queue_each(lltable->cols, NULL, destory_word_queue);
    queue_each(lltable->rows, NULL, destory_word_queue);
}
