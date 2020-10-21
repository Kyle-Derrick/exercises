#include <stdlib.h>
#include <string.h>
#include "stack.h"

const int _STACK_TYPE_SIZE_ = sizeof(Stack);
const int _STACK_NODE_TYPE_SIZE_ = sizeof(_StackNode_);

Stack* new_stack(int type)
{
    Stack *stack = malloc(_STACK_TYPE_SIZE_);
    stack->size = 0;
    stack->type = type;
    stack->top = NULL;

    return stack;
}

Stack* stack_push(Stack *st, void *value)
{
    _StackNode_ *node = malloc(_STACK_NODE_TYPE_SIZE_);
    node->value = value;
    node->next = st->top;
    st->top = node;
    st->size++;

    return st;
}

Stack* stack_pushn(Stack *st, void *value)
{
    void *tmp = malloc(st->type);
    memcpy(tmp, value, st->type);
    return stack_push(st, tmp);
}

void* stack_pop(Stack *st)
{
    if (!st->top)
    {
        return NULL;
    }
    
    _StackNode_ *top = st->top;
    void *value = top->value;
    st->top = top->next;
    free(top);
    st->size--;

    return value;
}

int stack_popp(Stack *st, void *value)
{
    void *tmp;
    if (!(tmp = stack_pop(st)))
    {
        return -1;
    }
    memcpy(value, tmp, st->type);
    free(tmp);

    return 0;
}

int stack_size(Stack *st)
{
    return st->size;
}

int stack_rsize(Stack *st)
{
    if (!st->top)
    {
        return 0;
    }
    _StackNode_ *tmp = st->top;
    int size = 0;
    do
    {
        size++;
    }while (tmp = tmp->next);
    
    return st->size;
}

void stack_destory(Stack *st)
{
    while (stack_pop(st));
    free(st);
}

void stack_destorya(Stack *st)
{
    void *tmp = stack_pop(st);
    while (tmp)
    {
        free(tmp);
        tmp = stack_pop(st);
    }
    free(st);
}