#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "stack.h"
#include "queue.h"
#include "llbase.h"
#include "lltable.h"

const char *$ = "$";
const char *START = "E";

void analysis(const char* str, LLTable *table);
Stack *initStack();
Queue *sentence_to_queue(const char* str, LLTable *table);
void print_analysis_status(const Stack *stack, Queue *sentence, char *str, size_t index);

void analysis(const char* str, LLTable *table)
{
    Stack *stack = initStack();
    Queue *sentence = sentence_to_queue(str, table);
    for (size_t i = 0; stack->size > 0 && i < strlen(str); i++)
    {
        Word *word = stack_pop(stack);
        size_t row = queue_word_indexOf(table->rows, word);
        size_t row = queue_word_indexOf(table->cols, word);
        
    }
    
}

Queue *sentence_to_queue(const char* str, LLTable *table)
{
    size_t strlen = strlen(str);
    size_t colslen = table->cols->size;
    Word **cols = queue_to_array_all(table->cols, NONE_FLAGS);
    for (size_t i = 0; i < (colslen-1); i++)
    {
        size_t len = (*(cols+i)).len;
        for (size_t j = i + 1; j < colslen; j++)
        {
            if ((**(cols+j)).len > len)
            {
                Word *tmp = *(cols+i);
                *(cols+i) = *(cols+j);
                *(cols+j) = tmp;
            }
        }
    }
    
    size_t index = 0;
    Queue *strqe = new_queue(sizeof(Word));
    while (1)
    {
        for (size_t i = 0; i < colslen; i++)
        {
            char *strtmp = str+index;
            Word *tmp = *(cols+i);
            
            if ((index + tmp->len) > strlen)
            {
                continue;
            }
            
            if (!strncmp(tmp->str, strtmp, tmp->len))
            {
                queue_add(strqe, word_clone(tmp), NONE_FLAGS);
                i += tmp->len;
            }
        }
    }

    Word *$word = malloc(sizeof(Word));
    $word->len = strlen($);
    $word->str = malloc($word->len + 1);
    strcpy($word->str, $);
    
    return queue_add(strqe, $word, NONE_FLAGS);
}

Stack *initStack()
{
    Stack *stack = new_stack(sizeof(Word));
    Word *startWord = malloc(sizeof(Word));
    startWord->len = strlen(START);
    startWord->str = malloc(startWord->len + 1);
    strcpy(startWord->str, START);
    stack_push(stack, startWord);
    return stack;
}