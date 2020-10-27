#ifndef _TOOLS_TOOLS_H_
#define _TOOLS_TOOLS_H_

#define NONE_FLAGS 0
#define INSERT_NODE 1
#define UPDATE_NODE 3
#define DELETE_NODE 2
#define CREATE_NEW_VALUE 4
#define DELETE_WITH_VALUE 8
#define DELETE_OLD_VALUE_CREATE_NEW 12
#define CLONE_NEW_QUEUE 16

//创建副本
extern void* create_replica(void *src, size_t size);
extern void* memcpy_free_src(void *target, void *src, size_t size);

#endif