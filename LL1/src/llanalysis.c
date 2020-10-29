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

void analysis(LLTable *table);
void analysis_work(char* str, LLTable *table, Word **colstmp);
Stack *initStack();
void lltable_produc_handle(LLTable *lltable);
Queue *sentence_to_queue(char* str, Word **words, size_t wordslen);
void print_analysis_status(LLTable *table, Stack *stack, Produc *produc, char *str, size_t index, size_t len);
Word **words_sort(Word **words, size_t wordslen);

void analysis(LLTable *table)
{
    Word **colstmp = queue_to_array_all(table->cols, NONE_FLAGS);
    colstmp = words_sort(colstmp, table->cols->size);
    lltable_produc_handle(table);
    
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
            printf("Bye~\n");
            break;
        }
        
        analysis_work(sentence, table, colstmp);
    }

    free(colstmp);
}

void analysis_work(char* str, LLTable *table, Word **colstmp)
{
    printf("loading...\n");
    Queue *sentence = sentence_to_queue(str, colstmp, table->cols->size);
    //add $ symbol to sentence
    Word *$word = malloc(sizeof(Word));
    $word->len = strlen($);
    $word->str = malloc($word->len + 1);
    strcpy($word->str, $);
    queue_add(sentence, $word, NONE_FLAGS);

    //init analysis stack
    Stack *stack = initStack();
    Produc *produc;
    printf("Analysis starting...\n");
    for (size_t i = 0; stack->size > 0 && sentence->size > 1; )
    {
        Word *stackTop = stack->top->value;
        Word *queueFirst = sentence->first->value;
    printf("now: %s, %s\n", stackTop->str, queueFirst->str);
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
    printf("produc: %d, %d: %d\n", row, col, produc);
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
                for (size_t j = produc->size; j > 0; j--)
                {
                    stack_push(stack, word_clone(produc->right+j-1));
                }
            }
        }
        printf("----\n");
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
    words = words_sort(words, rowlen+collen);
    colqetmp->first = NULL;
    queue_destory(colqetmp, NONE_FLAGS);
    Produc ***table = lltable->table;
    printf("row: %d, col: %d\n", rowlen, collen);
    printf("table:\nrow,col\tcontent\t\t(right num)\n");
    for (size_t i = 0; i < rowlen; i++)
    {
        for (size_t j = 0; j < collen; j++)
        {
            Produc *p = table[i][j];
            if (p)
            {
                printf("%d,%d\t%s%s%s",
                    i+1,j+1,
                    p->left->str, 
                    lltable->infer->str, 
                    p->right?p->right->str : EPSILON
                    );
                if (p->right)
                {
                    Queue *tmp = sentence_to_queue(p->right->str, words, rowlen+collen);
                    destory_word(p->right);
                    p->right = queue_to_array_all(tmp, CREATE_NEW_VALUE);
                    p->size = tmp->size;
                    queue_destory(tmp, DELETE_WITH_VALUE);

                    printf("\t\t%d", p->size);
                }else
                {
                    p->size = 0;
                }
                
                printf("\n");
            }
        }
        
    }
    
    queue_destory(rowqetmp, NONE_FLAGS);
    free(words);
}

Queue *sentence_to_queue(char* str, Word **words, size_t wordslen)
{
    size_t slen = strlen(str);
    
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
                i = wordslen;
            }
        }
    }
    
    return strqe;
}

Word **words_sort(Word **words, size_t wordslen)
{
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
    
    return words;
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
    for (size_t i = stack->size; i > 0; i++)
    {
        printf(" %s", (*(words+i-1))->str);
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
