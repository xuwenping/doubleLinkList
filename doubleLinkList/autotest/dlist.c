/*************************************************************************
    > File Name: dlist.c
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  9 01:36:43 2015
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
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
 * define a structure that store linklist's first node and last node, 
 * and malloc space to the structure.
 */
List *List_create()
{
  List *thiz = (List *)malloc(sizeof(List));
  ret_val_if_fail(NULL != thiz, NULL);
  thiz->count = 0;
  thiz->first = NULL;
  thiz->last = NULL;

  return thiz;
}

/*
 * destory linklist and destory the structure that store linklist's 
 * first node and last node 
 */
DListRet List_destroy(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  // if the count is equal to zero, represent that only free the structure
  // that store linklist's first node and last node
  if (0 == thiz->count)
  {
    free(thiz);
    return DList_Ret_OK;
  }

  ListNode *current = thiz->first;
  while (NULL != current)
  {
    thiz->first = current->next;
    ListNode_destroy(current);
    current = thiz->first;
  }

  free(thiz);
  return DList_Ret_OK;
}

/*
 * push a node on linklist
 */
DListRet List_push(List *thiz, void *value)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  ListNode *node = ListNode_create(value);
  ret_val_if_fail(NULL != node, DList_Ret_InvalidParams);

  if (0 == thiz->count)
  {
    thiz->first = node;
    thiz->last = node;
    thiz->count += 1;
    return DList_Ret_OK;
  }

  ListNode *iter = thiz->first;
  node->next = iter;
  iter->prev = node;
  thiz->first = node;
  thiz->count += 1;
  return DList_Ret_OK;
}

/*
 * pop a node from linklist
 */
DListRet List_pop(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  ret_val_if_fail(0 == thiz->count, DList_Ret_ListIsEmpty);

  if (1 == thiz->count)
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

  return DList_Ret_OK;
}

/*
 * get specify node value from linklist
 */
DListRet List_get_by_index(List *thiz, size_t index, void **value)
{
  ListNode *cursor = ListNode_get_node(thiz, index, 0);
  ret_val_if_fail(NULL != cursor, DList_Ret_Fail);

  *value = cursor->value;

  return DList_Ret_OK;
}

DListRet List_set_by_index(List *thiz, size_t index, void *value)
{
  ListNode *cursor = ListNode_get_node(thiz, index, 0);
  ret_val_if_fail(NULL != cursor, DList_Ret_Fail);

  cursor->value = value;

  return DList_Ret_OK;
}

size_t List_length(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return thiz->count;
}

DListRet List_foreach(List *thiz, ListDataVisitFunc visit, void *ctx)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  ListNode *iter = thiz->first;
  while (NULL != iter)
  {
    visit(ctx, iter->value);
    iter = iter->next;
  }

  return DList_Ret_OK;
}

#ifdef DLIST_TEST

#include <assert.h>

void test_int_dlist(void)
{
  int s = 0;
  int i = 0;
  int n = 100;
  int data = 0;
  List *dlist = List_create();

  for (i = 0; i < n; ++i)
  {
    assert(List_push(dlist, (void *)i) == DList_Ret_OK);
    assert(List_length(dlist) == i + 1);
    assert(List_get_by_index(dlist, 0, (void **)&data) == DList_Ret_OK);
    assert(data == i); 
    assert(List_set_by_index(dlist, 0, (void *)(2*i)) == DList_Ret_OK);
    assert(List_get_by_index(dlist, 0, (void **)&data) == DList_Ret_OK);
    assert(data == 2*i);
    assert(List_set_by_index(dlist, 0, (void *)i) == DList_Ret_OK);
  }

  for (i = 0; i < n; ++i)
  {
    assert(List_get_by_index(dlist, 0, (void **)&data) == DList_Ret_OK);
    assert(data == (n - i - 1));
    assert(List_length(dlist) == (n - i));
    assert(List_delete(dlist, 0) == DList_Ret_OK);
    assert(List_length(dlist) == (n - i - 1));
  }

  assert(List_length(dlist) == 0);
}

void test_invalid_params()
{
  printf("=========warning is normal begin========\n");
  assert(List_length(NULL) == DList_Ret_InvalidParams);
  assert(List_push(NULL, 0) == DList_Ret_InvalidParams);
  assert(List_delete(NULL, 0) == DList_Ret_InvalidParams);
  assert(List_pop(NULL) == DList_Ret_InvalidParams);
  printf("=========warning is normal end========\n");
}

int main()
{
  test_int_dlist();
  test_invalid_params();
  return 0;
}

#endif
