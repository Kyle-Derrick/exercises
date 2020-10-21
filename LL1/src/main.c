#include <stdio.h>
#include "stack.h"

typedef struct{
    char *left;
    char *symbol;
    char *right;
} Produc;

int main(int argc, char *argv[])
{
    Stack *stack = new_stack(sizeof(Produc));

    printf("%d\n", stack_size(stack));
    printf("%d\n", stack_rsize(stack));

    Produc p1;
    p1.left = "E";
    p1.symbol = "->";
    p1.right = "ET";

    stack_push(stack, &p1);

    printf("%d\n", stack_size(stack));
    printf("%d\n", stack_rsize(stack));

    {
        {
            Produc p1;
            p1.left = "T";
            p1.symbol = "->";
            p1.right = "TF";

            stack_pushn(stack, &p1);
        }
    }

    printf("%d\n", stack_size(stack));
    printf("%d\n", stack_rsize(stack));
    printf("----------\n");

    Produc *t = stack_pop(stack);
    printf("%d\n", t);
    printf("%s\t%s\t%s\n", t->left, t->symbol, t->right);
    printf("%d\n", stack_rsize(stack));
    t = stack_pop(stack);
    printf("%s\t%s\t%s\n", t->left, t->symbol, t->right);
    printf("%d\n", stack_rsize(stack));

    stack_destorya(stack);
}