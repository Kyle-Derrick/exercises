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

void analysis(char* str, LLTable *table);
Stack *initStack();
void lltable_produc_handle(LLTable *lltable);
Queue *sentence_to_queue(char* str, Word **words, size_t wordslen);
void print_analysis_status(LLTable *table, Stack *stack, Produc *produc, char *str, size_t index, size_t len);

void analysis(char* str, LLTable *table)
{
    Stack *stack = initStack();
    Word **colstmp = queue_to_array_all(table->cols, NONE_FLAGS);
    Queue *sentence = sentence_to_queue(str, colstmp, table->cols->size);
    free(colstmp);

    lltable_produc_handle(table);
printf("------\n");

    Produc *produc;
    for (size_t i = 0; stack->size > 0 && sentence->size > 1; )
    {
        Word *stackTop = stack->top->value;
        Word *queueFirst = sentence->first->value;
        if (!strcmp(stackTop->str, queueFirst->str))
        {
            destory_word(stack_pop(stack));
            destory_word(queue_shift(sentence));
            i++;
        }else
        {
            size_t row = queue_word_indexOf(table->rows, stackTop);
            size_t col = queue_word_indexOf(table->cols, queueFirst);
            produc = table->table[row][col];
            if (!produc)
            {
                perror("Grammer is wrong: ");
                printf("\"%s\"\n", str+i);
                goto end;
            }
            if (!produc->right)
            {
                destory_word(stack_pop(stack));
            }else
            {
                destory_word(stack_pop(stack));
                stackTop = stack->top->value;
                for (size_t j = produc->size-1; j >= 0; j++)
                {
                    stack_push(stack, word_clone(produc->right+j));
                }
            }
        }
        print_analysis_status(table, stack, produc, str, i, sentence->size);
    }
    
    end:
    stack_destorya(stack);
    queue_destory(sentence, DELETE_WITH_VALUE);
}

void lltable_produc_handle(LLTable *lltable)
{
    size_t rowlen = lltable->rows->size;
    size_t collen = lltable->cols->size;
    Queue *rowqetmp = queue_clone_all(lltable->rows, NONE_FLAGS);
    Queue *colqetmp = queue_clone_all(lltable->cols, NONE_FLAGS);
    Word **words = queue_to_array_all(
        queue_concat(rowqetmp, colqetmp, NONE_FLAGS), NONE_FLAGS
        );
    colqetmp->first = NULL;
    queue_destory(colqetmp, NONE_FLAGS);
    Produc ***table = lltable->table;
    for (size_t i = 0; i < rowlen; i++)
    {
        for (size_t j = 0; j < collen; j++)
        {
            Produc *p = table[i][j];
            if (p)
            {
                printf("%s,%s,%s\n", p->left, lltable->infer->str, p->right);
                Queue *tmp = sentence_to_queue(p->right->str, words, rowlen+collen);
                destory_word(p->right);
                p->right = queue_to_array_all(tmp, CREATE_NEW_VALUE);
                p->size = tmp->size;
                queue_destory(tmp, DELETE_WITH_VALUE);
            }
        }
        
    }
    
    queue_destory(rowqetmp, NONE_FLAGS);
    free(words);
}

Queue *sentence_to_queue(char* str, Word **words, size_t wordslen)
{
    size_t slen = strlen(str);
    for (size_t i = 0; i < (wordslen-1); i++)
    {
        size_t len = (*(words+i))->len;
        for (size_t j = i + 1; j < wordslen; j++)
        {
            if ((**(words+j)).len > len)
            {
                Word *tmp = *(words+i);
                *(words+i) = *(words+j);
                *(words+j) = tmp;
            }
        }
    }
printf("+------\n");
    
    size_t index = 0;
    Queue *strqe = new_queue(sizeof(Word));
    while (index < slen)
    {
        for (size_t i = 0; i < wordslen; i++)
        {
            char *strtmp = str+index;
            Word *tmp = *(words+i);
            
            if ((index + tmp->len) > slen)
            {
                continue;
            }
            
            if (!strncmp(tmp->str, strtmp, tmp->len))
            {
                queue_add(strqe, word_clone(tmp), NONE_FLAGS);
                index += tmp->len;
            }
// printf("+-----%d-%s\t%s\n", tmp->len, tmp->str, str);
        }
// printf("+-----%d-%d\t%s\n", index, slen, str);
    }

printf("+------\n");
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

void *stack_words_each(Stack *st,
        _StackNode_ *last,_StackNode_ *now,
        _StackNode_ **next,size_t index,void *arg,void *result)
{
    Word **words = arg;
    words[index] = now->value;
}
void print_analysis_status(LLTable *table, Stack *stack, Produc *produc, char *str, size_t index, size_t len)
{
    Word **words = malloc(sizeof(Word*)*stack->size);
    stack_each(stack, words, stack_words_each);
    printf("$");
    for (size_t i = stack->size-1; i >= 0; i++)
    {
        printf(" %s", (*(words+i))->str);
    }
    printf("\t|\t%s$", str + index);
    printf("\t|\t");
    if (produc)
    {
        printf("%s%s%s", produc->left, table->infer, produc->right);
    }
    
    char tmp[len];
    strncpy(tmp, str, index-1);
    tmp[index] = '\0';
    printf("\t|\t%s", tmp);
    for (size_t i = 0; i < stack->size; i++)
    {
        printf(" %s", (*(words+i))->str);
    }

    free(words);
}
