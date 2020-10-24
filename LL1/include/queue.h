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

extern Queue *string_to_queue(char *str);
extern Queue *string_to_queue_l(char *str, size_t len);

//创建新队列
extern Queue* new_queue(size_t type);
//添加元素到尾部
extern Queue* queue_add(Queue *qe, void *value, int flags);
//克隆队列，全部
extern Queue *queue_clone_all(Queue *qe, int flags);
//克隆队列
extern Queue *queue_clone(Queue *qe, size_t start, size_t end, int flags);
//对比队列
extern int queue_cmp(Queue *qe, Queue *qe2);
//对比队列，指定对比方法
extern int queue_cmpf(Queue *qe, Queue *qe2, int fun(const void*, const void*, size_t));
//追加元素集到末尾
extern Queue* queue_concat_arr(Queue *qe, void *value, size_t len, int flags);
//拼接队列
extern Queue* queue_concat(Queue *q1, Queue *q2, int flags);
//删除元素
extern void* queue_del(Queue *qe, size_t index, int flags);
//销毁队列
extern void queue_destory(Queue *qe, int flags);
//遍历队列
extern void *queue_each(Queue *qe, void *arg, void *fun(Queue*,_QueueNode_*,_QueueNode_*,_QueueNode_**,size_t,void*,void*));
//获取元素
extern void* queue_get(Queue *qe, size_t index);
//获取元素，放到传入参数value中
extern void queue_getn(Queue *qe, size_t index, void *value);
//查找元素，获取位置
extern ssize_t queue_indexOf(Queue *qe, void *value);
//查找元素，获取位置，指定对比方法
extern ssize_t queue_indexOff(Queue *qe, void *value, int fun(const void*, const void*, size_t));
//插入
extern Queue* queue_insert_all_arr(Queue *qe, size_t index, void *value, size_t len, int flags);
//插入
extern Queue* queue_insert_all(Queue *q1, Queue *q2, size_t index, int flags);
//插入
extern Queue* queue_insert(Queue *qe, size_t index, void *value, int flags);
//获取队列首部，并从队列删除
extern void* queue_shift(Queue *qe);
//获取队列首部，并从队列删除
extern int queue_shiftp(Queue *qe, void *value);
//获取队列大小
extern size_t queue_size(Queue *qe);
//队列转数组
extern void* queue_to_array_all(Queue *qe, int flags);
//队列转数组
extern void* queue_to_array(Queue *qe, size_t start, size_t end, int flags);
//队列多功能更新
extern Queue *queue_update_arr_diy(Queue *qe, size_t start, size_t end, void *value, size_t len, int flags);
//队列多功能更新拼接
extern Queue *queue_update_diy(Queue *q1, Queue *q2, size_t start, size_t end, int flags);
//更新元素
extern Queue* queue_update(Queue *qe, size_t index, void *value, int flags);

#endif