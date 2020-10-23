#include <stdlib.h>
#include <string.h>
#include "tools.h"

void *create_replica(void *src, size_t size)
{
    void *tmp = malloc(size);
    memcpy(tmp, src, size);
    return tmp;
}
void *memcpy_free_src(void *target, void *src, size_t size)
{
    memcpy(target, src, size);
    free(src);
    return target;
}