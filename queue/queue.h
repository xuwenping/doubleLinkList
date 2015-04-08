/*************************************************************************
	> File Name: queue.h
	> Author: 
	> Mail: 
	> Created Time: Tue Apr  7 01:58:12 2015
 ************************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H
#include "dlist.h"

struct _Queue;
typedef struct _Queue Queue;

Queue *queue_create();
void queue_destroy(Queue *thiz);

DListRet queue_head(Queue *thiz, void **data);
DListRet queue_push(Queue *thiz, void *value);
DListRet queue_pop(Queue *thiz);

size_t queue_length(Queue *thiz);

DListRet queue_foreach(Queue *thiz, ListDataVisitFunc visit, void *ctx);

#endif
