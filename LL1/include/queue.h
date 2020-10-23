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
extern Queue* queue_add(Queue *qe, void *value);
//add a node to queue, the node's value in a new space
extern Queue* queue_addn(Queue *qe, void *value);
//insert a node to queue
extern Queue* queue_insert(Queue *qe, size_t index, void *value);
//insert a node to queue, the node's value in a new space
extern Queue* queue_insertn(Queue *qe, size_t index, void *value);
//delete node of queue
extern void* queue_del(Queue *qe, size_t index);
//delete node of queue, include the value
extern void queue_dela(Queue *qe, size_t index);
//update node of queue
extern Queue* queue_update(Queue *qe, size_t index, void *value);
//update node of queue, the node's value in a new space
extern Queue* queue_updaten(Queue *qe, size_t index, void *value);
//search node of queue,return the index, if return -1, node not in queue
extern ssize_t queue_indexOf(Queue *qe, void *value);
//search node of queue with cmp function,return the index, if return -1, node not in queue
extern ssize_t queue_indexOff(Queue *qe, void *value, int fun(void*, void*, size_t));
//compared queue,return the first diffrent node index, if return -1, queue is identical
extern int queue_cmp(Queue *qe, Queue *qe2);
//compared queue,return the first diffrent node index with cmp function, if return -1, queue is identical
extern int queue_cmpf(Queue *qe, Queue *qe2, int fun(void*, void*, size_t));
//get node of queue
extern void* queue_get(Queue *qe, size_t index);
extern void queue_getn(Queue *qe, size_t index, void *value);
//get the top node of queue, the value need free when not use
extern void* queue_shift(Queue *qe);
//get the top node of queue, the value in the value param
extern int queue_shiftp(Queue *qe, void *value);
//conversion queue to array,
extern void* queue_to_array(Queue *qe);
extern void* queue_to_arrayn(Queue *qe);
//get the queue size
extern size_t queue_size(Queue *qe);
//destory the queue and queue node, retain the value
extern void queue_destory(Queue *qe);
//destory the queue,queue node and value, include the value
extern void queue_destorya(Queue *qe);

#endif