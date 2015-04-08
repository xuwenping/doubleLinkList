/*************************************************************************
	> File Name: queue.c
	> Author: 
	> Mail: 
	> Created Time: Tue Apr  7 01:58:41 2015
 ************************************************************************/

#include "queue.h"

struct _Queue
{
  List *list;
};

/*
 * create a queue
 */
Queue *queue_create()
{
  Queue *thiz = (Queue *)malloc(sizeof(Queue));
  ret_val_if_fail(NULL != thiz, NULL);

  thiz->list = List_create(NULL);
  if(NULL == thiz->list)
  {
    free(thiz);
    thiz = NULL;
  }

  return thiz;
}

void queue_destroy(Queue *thiz)
{
  if(NULL != thiz)
  {
    List_destroy(thiz->list);
    thiz->list = NULL;

    free(thiz);
    thiz = NULL;
  }
}

DListRet queue_head(Queue *thiz, void **data)
{
  ret_val_if_fail(NULL != thiz && NULL != data, DList_Ret_InvalidParams); 

  return List_get_by_index(thiz->list, 0, data);
}

DListRet queue_push(Queue *thiz, void *value)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return List_append(thiz->list, value);
}

DListRet queue_pop(Queue *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return List_pop(thiz->list);
}

size_t queue_length(Queue *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return List_length(thiz->list);
}

DListRet queue_foreach(Queue *thiz, ListDataVisitFunc visit, void *ctx)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return List_foreach(thiz->list, visit, ctx);
}

#ifdef QUEUE_TEST
#include <assert.h>

static void test_int_queue(void)
{
  void **covert;

  int i = 0;
  int data = 0;
  Queue *thiz = queue_create();
  ret_if_fail(NULL != thiz);
  List *dlist = thiz->list;
  for(; i < 100; ++i)
  {
    assert(DList_Ret_OK == queue_push(thiz, (void *)i));
    assert((i+1) == queue_length(thiz));
    assert(DList_Ret_OK == queue_head(thiz, (void **)&data));
    assert(0 == (int)data);
  }
  
  for(i = 0; i < 100; ++i)
  {
    assert(DList_Ret_OK == queue_pop(thiz));
  }
  assert(0 == queue_length(thiz));

  queue_destroy(thiz);
}

int main()
{
  test_int_queue(); 
  return 0;
}


#endif

