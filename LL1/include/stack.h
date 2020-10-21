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
    int type;
    int size;
    _StackNode_ *top;
};
typedef struct Stack Stack;

//get a new stack
extern Stack* new_stack(int type);
//push a node to stack
extern Stack* stack_push(Stack *st, void *value);
//push a node to stack, the node's value in a new space
extern Stack* stack_pushn(Stack *st, void *value);
//get the top node of stack, the value in a new space
extern void* stack_pop(Stack *st);
//get the top node of stack, the value in the value param
extern int stack_popp(Stack *st, void *value);
//get the stack size
extern int stack_size(Stack *st);
//destory the stack and stack node, retain the value
extern void stack_destory(Stack *st);
//destory the stack,stack node and value, include the value
extern void stack_destorya(Stack *st);

#endif