/*************************************************************************
    > File Name: dlist.c
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  9 01:36:43 2015
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "dlist.h"

typedef struct _ListNode {
  struct _ListNode *next;
  struct _ListNode *prev;
  void *value;
}ListNode;

struct _List {
  int count;
  ListNode *first;
  ListNode *last;
  Locker *locker;
};

/*
 * create a node of linklist by input a value
 */
static ListNode *ListNode_create(void *value)
{
  ListNode *node = (ListNode *)malloc(sizeof(ListNode));
  ret_val_if_fail(NULL != node, NULL);
  node->value = value;
  node->next = NULL;
  node->prev = NULL;

  return node;
}

/*
 * destroy node
 */
static void ListNode_destroy(ListNode *node)
{
  ret_if_fail(NULL != node);
  node->next = NULL;
  node->prev = NULL;
  free(node);
}

/*
 * add lock for list
 */
static void List_lock(List *thiz)
{
  if((NULL != thiz) && (NULL != thiz->locker))
  {
    Locker_lock(thiz->locker);
  }
}

/*
 * unlock for list
 */
static void List_unlock(List *thiz)
{
  if((NULL != thiz) && (NULL != thiz->locker))
  {
    Locker_unlock(thiz->locker);
  }
}

/*
 * destroy lock
 */
static void List_destroy_locker(List *thiz)
{
  if((NULL != thiz) && (NULL != thiz->locker))
  {
    Locker_destroy(thiz->locker);
  }
}

/*
 * define a structure that store linklist's first node and last node, 
 * and malloc space to the structure.
 */
List *List_create(Locker *locker)
{
  List *thiz = (List *)malloc(sizeof(List));
  ret_val_if_fail(NULL != thiz, NULL);
  thiz->count = 0;
  thiz->first = NULL;
  thiz->last = NULL;
  thiz->locker = locker;

  return thiz;
}

/*
 * destory linklist and destory the structure that store linklist's 
 * first node and last node 
 */
DListRet List_destroy(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  DListRet ret = DList_Ret_OK;

  List_lock(thiz);

  do
  {
    // if the count is equal to zero, represent that only free the structure
    // that store linklist's first node and last node
    if (0 == thiz->count)
    {
      ret = DList_Ret_OK;
      break;
    }

    ListNode *current = thiz->first;
    while (NULL != current)
    {
      thiz->first = current->next;
      ListNode_destroy(current);
      current = thiz->first;
    }

  }while(0);

  List_destroy_locker(thiz);
  free(thiz);

  return DList_Ret_OK;
}

/*
 * push a node on linklist
 */
DListRet List_push(List *thiz, void *value)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  DListRet ret= DList_Ret_OK;
  
  List_lock(thiz);

  do{
    ListNode *node = ListNode_create(value);
    ret_val_if_fail(NULL != node, DList_Ret_InvalidParams);

    if (0 == thiz->count)
    {
      thiz->first = node;
      thiz->last = node;
      thiz->count += 1;
      ret = DList_Ret_OK;
      break;
    }

    ListNode *iter = thiz->first;
    node->next = iter;
    iter->prev = node;
    thiz->first = node;
    thiz->count += 1;
  }while(0);

  List_unlock(thiz);

  return ret;
}

/*
 * pop a node from linklist
 */
DListRet List_pop(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  List_lock(thiz);

  if(0 == thiz->count)
  {

  }
  else if (1 == thiz->count)
  {
    ListNode_destroy(thiz->first);
    thiz->count -= 1;
    thiz->first = NULL;
    thiz->last = NULL;
  }
  else
  {
    ListNode *iter = thiz->first;
    thiz->first = iter->next;
    thiz->count -= 1;
    ListNode_destroy(iter);
  }

  List_unlock(thiz);

  return DList_Ret_OK;
}

/*
 * get specify index node
 * the param fail_return_last: when index overlap, need return a value
 * note: the index value start from 0
 */
static ListNode *ListNode_get_node(List *thiz, size_t index, size_t fail_return_last)
{
  ret_val_if_fail(NULL != thiz, NULL);
  ret_val_if_fail(thiz->count > index, NULL);
  
  // find specify index node via loop
  ListNode *iter = thiz->first;
  int i = 0;
  for (i = index; (i > 0) && (NULL != iter->next); --i)
  {
    iter = iter->next;
  }

  if (!fail_return_last)
  {
    iter = i > 0 ? NULL : iter;
  }

  return iter;
}

/*
 * delete specify node from linklist
 */
DListRet List_delete(List *thiz, size_t index)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);
  ret_val_if_fail(thiz->count > index, DList_Ret_Index_Overstep);

  List_lock(thiz);

  ListNode *cursor = ListNode_get_node(thiz, index, 0);
  ret_val_if_fail(NULL != cursor, DList_Ret_InvalidParams);

  // when there is only a node
  if (thiz->first == cursor && thiz->last == cursor)
  {
    thiz->first = NULL;
    thiz->last = NULL;
  }
  // when the specify node is the first node
  else if (thiz->first == cursor)
  {
    cursor->next->prev = NULL;
    thiz->first = cursor->next;
  }
  // when the specify node is the last node
  else if (thiz->last == cursor)
  {
    cursor->prev->next = NULL;
    thiz->last = cursor->prev;
  }
  else
  {
    cursor->next->prev = cursor->prev;
    cursor->prev->next = cursor->next;
  }
  thiz->count -= 1;
  ListNode_destroy(cursor);

  List_unlock(thiz);

  return DList_Ret_OK;
}

/*
 * get specify node value from linklist
 */
DListRet List_get_by_index(List *thiz, size_t index, void **value)
{
  List_lock(thiz);

  ListNode *cursor = ListNode_get_node(thiz, index, 0);
  ret_val_if_fail(NULL != cursor, DList_Ret_Fail);

  *value = cursor->value;

  List_unlock(thiz);

  return DList_Ret_OK;
}

DListRet List_set_by_index(List *thiz, size_t index, void *value)
{
  List_lock(thiz);

  ListNode *cursor = ListNode_get_node(thiz, index, 0);
  ret_val_if_fail(NULL != cursor, DList_Ret_Fail);

  cursor->value = value;

  List_unlock(thiz);

  return DList_Ret_OK;
}

size_t List_length(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  List_lock(thiz);
  
  size_t len = thiz->count;

  List_unlock(thiz);

  return len;
}

DListRet List_foreach(List *thiz, ListDataVisitFunc visit, void *ctx)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  List_lock(thiz);

  ListNode *iter = thiz->first;
  while (NULL != iter)
  {
    visit(ctx, iter->value);
    iter = iter->next;
  }

  List_unlock(thiz);

  return DList_Ret_OK;
}

#ifdef DLIST_TEST

#include <assert.h>

static void test_int_dlist(void)
{
  int s = 0;
  int i = 0;
  int n = 100;
  int data = 0;
  List *dlist = List_create(NULL);

  for (i = 0; i < n; ++i)
  {
    assert(List_push(dlist, (void *)i) == DList_Ret_OK);
    assert(List_length(dlist) == i + 1);
    void **covert = (void **)&data;
    assert(List_get_by_index(dlist, 0, covert) == DList_Ret_OK);
    printf("before: the data is %d, the i is %d\n", data, i);
    assert((int)data == i); 
    printf("after: the data is %d, the i is %d\n", data, i);
    assert(List_set_by_index(dlist, 0, (void *)(2*i)) == DList_Ret_OK);
    assert(List_get_by_index(dlist, 0, (void **)&data) == DList_Ret_OK);
    assert(data == 2*i);
    assert(List_set_by_index(dlist, 0, (void *)i) == DList_Ret_OK);
  }

  for (i = 0; i < n; ++i)
  {
    void **covert = (void **)&data;
    assert(List_get_by_index(dlist, 0, covert) == DList_Ret_OK);
    assert(data == (n - i - 1));
    assert(List_length(dlist) == (n - i));
    assert(List_delete(dlist, 0) == DList_Ret_OK);
    assert(List_length(dlist) == (n - i - 1));
  }

  assert(List_length(dlist) == 0);
  assert(List_destroy(dlist) == DList_Ret_OK);
}

static void test_invalid_params()
{
  printf("=========warning is normal begin========\n");
  assert(List_length(NULL) == DList_Ret_InvalidParams);
  assert(List_push(NULL, 0) == DList_Ret_InvalidParams);
  assert(List_delete(NULL, 0) == DList_Ret_InvalidParams);
  assert(List_pop(NULL) == DList_Ret_InvalidParams);
  printf("=========warning is normal end========\n");
}
static void single_thread_test()
{
  test_int_dlist();
  test_invalid_params();
}

static void *produce(void *param)
{
  int i = 0;
  List *thiz = (List *)param;
  for(i = 0; i < 100; ++i)
  {
    assert(List_push(thiz, (void *)i) == DList_Ret_OK);
  }

  return NULL;
}

static void *consume(void *param)
{
  List *thiz = (List *)param;
  int i = 0;
  for(i = 0; i < 100; ++i)
  {
    assert(List_pop(thiz) == DList_Ret_OK);
  }

  return NULL;
}

static void multi_thread_test()
{
  pthread_t t1 = 0;
  pthread_t t2 = 0;

  Locker *locker = locker_pthread_create();
  List *dlist = List_create(locker);
  assert(NULL != dlist);
  pthread_create(&t1, NULL, produce, dlist);
  pthread_create(&t2, NULL, consume, dlist);

  pthread_join(&t2, NULL);
  pthread_join(&t2, NULL);

  //assert(List_destroy(dlist) == DList_Ret_OK);
}

int main()
{
//  single_thread_test();
  multi_thread_test();
  return 0;
}

#endif
