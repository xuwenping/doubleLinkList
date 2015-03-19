/*************************************************************************
    > File Name: dlist.c
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  2 04:48:30 2015
 ************************************************************************/

#include<stdio.h>
#include "dlist.h"
#include <stdlib.h>

node_t * createLinkList(int data)
{
  node_t * head = NULL;
  head = (node_t *)malloc(sizeof(node_t));
  ret_if_fail(NULL != head);
  head->data = data;
  head->next = NULL;
  return head;
}

Ret destroyLinkList(node_t** head)
{
  node_t * current;
  while ((*head) != NULL)
  {
    current = *head;
    *head = current->next;
    free(current);
    current = NULL;
  }

  return Ret_ok;
}

Ret pushFront(node_t** head, int data)
{
  node_t* current = (node_t*)malloc(sizeof(node_t));
  ret_val_if_fail(NULL != current, Ret_malloc_fail);
  current->data = data;
  current->next = *head;
  *head = current;
  
  return Ret_ok;
}

Ret pushBack(node_t* head, int data)
{
  ret_val_if_fail(NULL != head, Ret_invalid_params);
  node_t* current = head;
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  ret_val_if_fail(NULL != newNode, Ret_malloc_fail);
  newNode->data = data;
  newNode->next = NULL;
  
  while (NULL != current->next)
  {
    current = current->next;
  }
  current->next = newNode;

  return Ret_ok;
}

Ret popFront(node_t** head)
{
  ret_val_if_fail(NULL != *head, Ret_invalid_params);
  node_t* current = *head;
  *head = current->next;
  free(current);
  current = NULL;

  return Ret_ok;
}

Ret popBack(node_t* head)
{
  ret_val_if_fail(NULL != head, Ret_invalid_params);
  // if there is only a element
  if (NULL == head->next)
  {
    free(head);
    head = NULL;
    return Ret_ok;
  }

  node_t* current = head;
  
  while (NULL != current->next->next)
  {
    current = current->next;
  }
  free(current->next);
  current->next = NULL;

  return Ret_ok;
}

Ret removeByIndex(node_t* head, int index)
{
  ret_val_if_fail(NULL != head, Ret_invalid_params);

  // if the index is 0
  if (0 == index)
  {
    return popFront(&head);
  }

  node_t* current = head;
  int i = 0; 
  for(; i < index - 1; ++i)
  {
    if (NULL == current->next)
    {
      return Ret_fail;
    }
    current = current->next;
  }
  node_t* tempNode = current->next;
  current->next = tempNode->next;
  free(tempNode);
  tempNode = NULL;
}

Ret dispalyAllNode(node_t* head)
{
  ret_val_if_fail(NULL != head, Ret_invalid_params);

  node_t* current = head;
  while (NULL != current)
  {
    printf("The data is %d\n", current->data);
    current = current->next;
  }

}
