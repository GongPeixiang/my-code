#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEFINE_QUEUE(T)\
\
typedef struct node_##T {\
	T val;\
	struct node_##T *next;\
} Node_##T;\
\
static Node_##T *create_node_##T(T val)\
{\
	Node_##T *node = malloc(sizeof(Node_##T));\
	if (!_node)\
		exit(1);\
	node->val = val;\
	node->next = NULL;\
	return _node;\
}\
\
typedef struct queue##T {\
	Node_##T *front;\       /* front节点为哑节点 */
	Node_##T *end;\
	size_t size;\
} Queue_##T;\
\
static bool is_empty_##T(Queue_##T *q) { return q->size == 0; }\
\
static void queue_init_##T(Queue_##T *q)\
{\
	q->front = q->end = create_node_##T((T)0);\
	q->size = 0;\
}\
\
static void enqueue_##T(Queue_##T *q, T ele)\
{\
	Node_##T *new_node = create_node_##T(ele);\
	q->end->next = new_node;\
	q->end = new_node;\
	q->size++;\
}\
\
static T dequeue_##T(Queue_##T *q)\
{\
	if (is_empty_##T(q))\
		exit(1);\
	T ret = q->front->next->val;\
	Node_##T *tmp = q->front;\
	q->front = q->front->next;\
	free(tmp);\
	q->size--;\
	return ret;\
}\
\
static void clear_queue_##T(Queue_##T *q)\
{\
	while (!is_empty_##T(q))\
		dequeue_##T(q);\
	free(q->front);\
    q->front = NULL;\
    q->end = NULL;\
    q->size = 0;\
}\

#endif