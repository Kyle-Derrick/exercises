#ifndef _LLBASE_H_
#define _LLBASE_H_

typedef struct{
    char *str;
    size_t len;
} Word;

typedef struct{
    Word *left;
    Word *right;
} Produc;

extern Word *queue_to_word(Queue *qe);
extern Word *word_clone(Word *word);
extern void destory_word(Word *word);
extern void *destory_word_queue(Queue* qe,_QueueNode_ *last,_QueueNode_ *now,_QueueNode_ **next,size_t index,void *arg,void *result);

#endif