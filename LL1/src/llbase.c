#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "llbase.h"

const char *EPSILON = "ε";

int word_equals(const void *v1, const void *v2, size_t len);
size_t queue_word_indexOf(Queue *qe, Word *word);
Word *queue_to_word(Queue *qe);
Word *word_clone(Word *word);
void destory_word(Word *word);
void *destory_word_queue(Queue* qe,_QueueNode_ *last,_QueueNode_ *now,_QueueNode_ **next,size_t index,void *arg,void *result);

int word_equals(const void *v1, const void *v2, size_t len)
{
    Word *w1 = (Word*)v1, *w2 = (Word*)v2;
    if (!w1 || !w2 || w1->len!=w2->len)
    {
        return -1;
    }
    
    return strcmp(w1->str, w2->str);
}

size_t queue_word_indexOf(Queue *qe, Word *word)
{
    return queue_indexOff(qe, word, word_equals);
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

void destory_word(Word *word)
{
    if (word)
    {
        free(word->str);
        free(word);
    }
    
}

void *destory_word_queue(Queue* qe,_QueueNode_ *last,_QueueNode_ *now,_QueueNode_ **next,size_t index,void *arg,void *result)
{
    destory_word((Word*)now);
    qe->first = *next;
}