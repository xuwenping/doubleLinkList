/*************************************************************************
    > File Name: dlist.h
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  9 01:27:12 2015
 ************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include <stdio.h>

#define ret_if_fail(p) if(!(p))            \
  {printf("%s:%d Warning: "#p" failed.\n", \
__func__, __LINE__); return;}

#define ret_val_if_fail(p, ret) if(!(p))   \
  {printf("%s:%d Warning: "#p" failed.\n", \
__func__, __LINE__); return (ret);}

typedef enum _DListRet {
  DList_Ret_OK,
  DList_Ret_Fail,
  DList_Ret_MallocFail,
  DList_Ret_ListIsEmpty,
  DList_Ret_InvalidParams,
  DList_Ret_Index_Overstep
}DListRet;

struct _List;
typedef struct _List List;

List *List_create();
DListRet List_destroy(List *thiz);

DListRet List_push(List *thiz, void *value);
DListRet List_pop(List *thiz);

DListRet List_delete(List *thiz, size_t index);
DListRet List_get_by_index(List *thiz, size_t index, void** data);
DListRet List_set_by_index(List *thiz, size_t index, void *value);

size_t List_length(List *thiz);
#endif /*DLIST_H*/
