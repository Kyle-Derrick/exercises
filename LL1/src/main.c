#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"
#include "queue.h"
#include "queue.h"

typedef struct{
    char *left;
    char *symbol;
    char *right;
} Produc;

char* test()
{
    char *t = "abcdef";
    return t;
}
int test2()
{
    int t = 123;
    return t;
}
char* test3()
{
    char *t = "abf";
    return t;
}

int main(int argc, char *argv[])
{
    Queue *queue = new_queue(sizeof(Produc));

    printf("%d\n", test());
    printf("%s\n", test());
    printf("%d\n", sizeof(size_t));
    printf("%d\n", sizeof(_QueueNode_*));
    printf("%d\n", queue_size(queue));
    printf("%d\n", queue_size(queue));

    Produc p1;
    p1.left = "E";
    p1.symbol = "->";
    p1.right = "ET";

    queue_add(queue, &p1, 0);

    printf("%d\n", queue_size(queue));
    printf("%d\n", queue_size(queue));

    {
        {
            Produc p1;
            p1.left = "T";
            p1.symbol = "->";
            p1.right = "TF";

            queue_add(queue, &p1, 0);
        }
    }

    printf("%d\n", queue_size(queue));
    printf("%d\n", queue_size(queue));
    printf("----------\n");

    Produc *t = queue_shift(queue);
    printf("%d\n", t);
    printf("%s\t%s\t%s\n", t->left, t->symbol, t->right);
    printf("%d\n", queue_size(queue));
    t = queue_shift(queue);
    printf("%s\t%s\t%s\n", t->left, t->symbol, t->right);
    printf("%d\n", queue_size(queue));

    queue_destory(queue, DELETE_WITH_VALUE);

    char (*f)() = test;
    printf("%d\n", f);
    int (*f2)() = test2;
    printf("%d\n", f2);
    char (*f3)() = test3;
    printf("%d\n", f3);
    printf("%d\n", sizeof(*f));
    printf("*:%d\n", f2());

    printf("----------\n");
    int (*f4)() = malloc(16);
    printf("----------\n");
    memcpy(f4, f2, 16);
    printf("----------\n");

    // char (*f4)() = tt;
    printf("**:%d\n", f4());
    free(f4);
}