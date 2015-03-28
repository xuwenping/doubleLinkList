/*************************************************************************
    > File Name: dlist.h
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  9 01:27:12 2015
 ************************************************************************/

#ifndef DLIST_H
#define DLIST_H

#include "typedef.h"

List *List_create();
DListRet List_destroy(List *thiz);

DListRet List_push(List *thiz, void *value);
DListRet List_pop(List *thiz);

DListRet List_delete(List *thiz, size_t index);
DListRet List_get_by_index(List *thiz, size_t index, void **data);
DListRet List_set_by_index(List *thiz, size_t index, void *value);

size_t List_length(List *thiz);

#endif /*DLIST_H*/
