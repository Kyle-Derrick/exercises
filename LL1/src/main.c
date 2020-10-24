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
    char *ss = "hello";
    Queue *queue = string_to_queue(ss);
    printf("%d\n", queue->size);
    printf("%d\n", queue->type);
    printf("%d\n", queue->first);
    printf("%d\n", queue->last);
    char *s = queue_to_array_all(queue, CREATE_NEW_VALUE);

    printf("%d\n", s);
    printf("%s\n", s);
    free(s);
    queue_destory(queue, DELETE_WITH_VALUE);
}