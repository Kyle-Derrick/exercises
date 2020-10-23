#ifndef _STACK_H_
#define _STACK_H_

//stack node struct
struct _StackNode_
{
    void *value;
    struct _StackNode_ *next;
};
typedef struct _StackNode_ _StackNode_;

//stack struct
struct Stack
{
    size_t type;
    size_t size;
    _StackNode_ *top;
};
typedef struct Stack Stack;

//get a new stack
extern Stack* new_stack(size_t type);
//push a node to stack
extern Stack* stack_push(Stack *st, void *value);
//push a node to stack, the node's value in a new space
extern Stack* stack_pushn(Stack *st, void *value);
//get the top node of stack, the value need free when not use
extern void* stack_pop(Stack *st);
//get the top node of stack, the value in the value param
extern int stack_popp(Stack *st, void *value);
//get the stack size
extern size_t stack_size(const Stack *st);
//destory the stack and stack node, retain the value
extern void stack_destory(Stack *st);
//destory the stack,stack node and value, include the value
extern void stack_destorya(Stack *st);

extern void *stack_each(Stack *st, void *fun(Stack*,
        _StackNode_*,_StackNode_*,
        _StackNode_**,size_t,void*));

extern void *stack_to_array(Stack *st, int flags);

#endif