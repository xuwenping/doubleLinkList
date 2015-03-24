/*************************************************************************
	> File Name: darray.h
	> Author: 
	> Mail: 
	> Created Time: Mon Mar 23 01:23:30 2015
 ************************************************************************/

#ifndef _DARRAY_H
#define _DARRAY_H
#include "typedef.h"

struct _DArray;
typedef struct _DArray DArray;

DArray *darray_create();
Ret darray_destroy(DArray *thiz);

Ret darray_insert(DArray *thiz, size_t index, void *value);
Ret darray_prepend(DArray *thiz, void *value);
Ret darray_append(DArray *thiz, void *value);

Ret darray_delete(DArray *thiz, size_t index);
Ret darray_get_by_index(DArray *thiz, size_t index, void *value);
Ret darray_set_by_index(DArray *thiz, size_t index, void *value);

size_t darray_length(DArray *thiz);

Ret darray_froeach(DArray *thiz, DArrayDataVisitFunc visit, void *ctx);

Ret darray_sort(DArray *thiz, SortFunc sort, DataCompareFunc cmp);

#endif
