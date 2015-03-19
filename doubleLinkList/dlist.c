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

DListRet List_delete(List *thiz, size_t index)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);
  ret_val_if_fail(thiz->count > index, DList_Ret_Index_Overstep);

  if (0 == index)
  {
    ListNode_destroy(thiz->first);
    thiz->count -= 1;
    thiz->first = NULL;
    thiz->last = NULL;
    return DList_Ret_OK;
  }

  ListNode *iter = thiz->first;
  int i = 0;
  for (; i < index-1; ++i)
  {
    iter = iter->next;
  }
  ListNode *needDestroyNode = iter->next;
  iter->next = needDestroyNode->next;
  if (iter->next != NULL)
  {
    iter->next->prev = iter;
  }
  else
  {
    thiz->last = iter;
  }
  thiz->count -= 1;
  ListNode_destroy(needDestroyNode);

  return DList_Ret_OK;
}

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

  return DList_Ret_Fail;
}

size_t List_length(List *thiz)
{
  ret_val_if_fail(NULL != thiz, DList_Ret_InvalidParams);

  return thiz->count;
}
