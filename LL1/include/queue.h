#ifndef _QUEUE_H_
#define _QUEUE_H_

//queue node struct
struct _QueueNode_
{
    void *value;
    struct _QueueNode_ *next;
};
typedef struct _QueueNode_ _QueueNode_;

//queue struct
struct Queue
{
    int type;
    int size;
    _QueueNode_ *top;
};
typedef struct Queue Queue;

//get a new queue
extern Queue* newqueue(int type);
//push a node to queue
extern Queue* push(Queue *st, void *value);
//push a node to queue, the node's value in a new space
extern Queue* pushn(Queue *st, void *value);
//get the top node of queue, the value in a new space
extern void* pop(Queue *st);
//get the top node of queue, the value in the value param
extern int popp(Queue *st, void *value);
//get the queue size
extern int queuesize(Queue *st);
//get the queue with a loop
extern int queuersize(Queue *st);
//destory the queue and queue node, retain the value
extern void destory(Queue *st);
//destory the queue,queue node and value, include the value
extern void destorya(Queue *st);

#endif