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

void analysis(const char* str, LLTable *table)
{
    Stack *stack = initStack();
    for (size_t i = 0; stack->size > 0 && i < strlen(str); i++)
    {
        Word *word = stack_pop(stack);
        size_t row = queue_word_indexOf(table->rows, word);
        size_t row = queue_word_indexOf(table->cols, word);
        
    }
    
}

void str_to_queue(const char* str, LLTable *table)
{
    Queue *cols = table->cols;
    int strlen = strlen(str);
    
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