/*************************************************************************
    > File Name: dlist.h
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  2 01:44:27 2015
 ************************************************************************/

#ifndef __DLIST__H
#define __DLIST__H

#define ret_if_fail(p) if(!(p))               \
  {printf("%s:%d Warning: "#p" filed.\n",     \
__func__, __LINE__);}

#define ret_val_if_fail(p, ret) if(!(p))      \
  {printf("%s:%d Warning: "#p" failed.\n",    \
__func__, __LINE__); return (ret);}

typedef enum _Ret{
  Ret_ok,
  Ret_fail,
  Ret_invalid_params,
  Ret_malloc_fail
} Ret;

typedef struct _NODE {
  int data;
  struct _NODE *next;
} node_t;

node_t * createLinkList();
Ret destroyLinkList(node_t** head);

Ret pushFront(node_t** head, int data);
Ret pushBack(node_t* head, int data);

Ret popFront(node_t** head);
Ret popBack(node_t* head);

Ret removeByIndex(node_t* head, int index);

Ret dispalyAllNode(node_t* head);

Ret reversalLinkList(node_t** head);
#endif //__DLIST__H
