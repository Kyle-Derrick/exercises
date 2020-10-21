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
    size_t type;
    size_t size;
    _QueueNode_ *first;
    _QueueNode_ *last;
};
typedef struct Queue Queue;

//get a new queue
extern Queue* new_queue(size_t type);
//add a node to queue
extern Queue* queue_add(Queue *st, void *value);
//add a node to queue, the node's value in a new space
extern Queue* queue_addn(Queue *st, void *value);
//insert a node to queue
extern Queue* queue_insert(Queue *st, size_t index, void *value);
//insert a node to queue, the node's value in a new space
extern Queue* queue_insertn(Queue *st, size_t index, void *value);
//delete node of queue
extern void* queue_del(Queue *st, size_t index);
//delete node of queue, include the value
extern void queue_dela(Queue *st, size_t index);
//update node of queue
extern Queue* queue_update(Queue *st, size_t index, void *value);
//update node of queue, the node's value in a new space
extern Queue* queue_updaten(Queue *st, size_t index, void *value);
//search node of queue,return the index, if return -1, node not in queue
extern size_t queue_indexOf(Queue *st, void *value);
//search node of queue with cmp function,return the index, if return -1, node not in queue
extern size_t queue_indexOff(Queue *st, void *value, int fun(void*, void*));
//compared queue,return the first diffrent node index, if return -1, queue is identical
extern size_t queue_cmp(Queue *st);
//compared queue,return the first diffrent node index with cmp function, if return -1, queue is identical
extern size_t queue_cmpf(Queue *st, int fun(void*, void*));
//get node of queue
extern void* queue_get(Queue *st, size_t index);
//get the top node of queue, the value need free when not use
extern void* queue_shift(Queue *st);
//get the top node of queue, the value in the value param
extern int queue_shiftp(Queue *st, void *value);
//conversion queue to array,
extern void* queue_to_array(Queue *st);
//get the queue size
extern size_t queue_size(Queue *st);
//destory the queue and queue node, retain the value
extern void queue_destory(Queue *st);
//destory the queue,queue node and value, include the value
extern void queue_destorya(Queue *st);

#endif