#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "stack.h"

const size_t _STACK_TYPE_SIZE_ = sizeof(Stack);
const size_t _STACK_NODE_TYPE_SIZE_ = sizeof(_StackNode_);

Stack* new_stack(size_t type)
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
    return stack_push(st, create_replica(value, st->type));
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
    memcpy_free_src(value, tmp, st->type);

    return 0;
}

size_t stack_size(const Stack *st)
{
    if (!st->top)
    {
        return 0;
    }
    _StackNode_ *tmp = st->top;
    size_t size = 0;
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
    void *tmp;
    while (tmp = stack_pop(st))
    {
        free(tmp);
    }
    free(st);
}

void *stack_each(Stack *st, void *arg, void *fun(Stack*,_StackNode_*,_StackNode_*,_StackNode_**,size_t,void*,void*))
{
    if (!st->top)
    {
        return NULL;
    }

    _StackNode_ *tmplast = NULL;
    _StackNode_ *tmp = st->top;
    _StackNode_ *tmpnext = NULL;
    size_t index = 0;
    void *result = NULL;
    do
    {
        tmpnext = tmp->next;
        result = fun(st, tmplast, tmp, &tmpnext, index, arg, result);
        tmplast = tmp;
        tmp = tmpnext;
        index++;
    } while (tmp);
    
    return result;
}

void *__stack_to_array__(Stack* st, _StackNode_* last,
            _StackNode_* now, _StackNode_** next,
            size_t index, void *arg, void* result)
{
    if (!result)
    {
        result = calloc(st->size, sizeof(void*));
    }
    *((void**)result+index*st->type) = now->value;
    return result;
}

void *stack_to_array(Stack *st, int flags)
{
    return stack_each(st, NULL, __stack_to_array__);
}

Stack *stack_clone(Stack *st)
{
    _StackNode_ *tmp = st->top;
    Stack *stcp = malloc(_STACK_TYPE_SIZE_);
    stcp->type = st->type;
    stcp->size = st->size;
    stcp->top = NULL;
    
    if (!st->top)
    {
        return stcp;
    }

    _StackNode_ *tmpnew = malloc(_STACK_NODE_TYPE_SIZE_);
    memcpy(tmpnew->value, tmp->value, st->type);
    tmpnew->next = NULL;
    stcp->top = tmpnew;
    while (tmp = tmp->next)
    {
        tmpnew->next = malloc(_STACK_NODE_TYPE_SIZE_);
        tmpnew = tmpnew->next;
        memcpy(tmpnew->value, tmp->value, st->type);
        tmpnew->next = NULL;
    }
    
    return stcp;
}