#ifndef _TOOLS_TOOLS_H_
#define _TOOLS_TOOLS_H_

#define CREATE_NEW_VALUE 1
#define NOT_CREATE_NEW_VALUE 0

//创建副本
extern void* create_replica(void *src, size_t size);
extern void* memcpy_free_src(void *target, void *src, size_t size);

#endif