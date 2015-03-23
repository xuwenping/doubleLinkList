/*************************************************************************
	> File Name: darry.c
	> Author: 
	> Mail: 
	> Created Time: Mon Mar 23 01:22:18 2015
 ************************************************************************/

#include <stdio.h>
#include "darray.h"

struct _DArray {
  void **data;
  size_t size;
  size_t alloc_size;
};

/*
 * create a dynamic array
 */
DArray *darray_create()
{
  DArray *thiz = (DArray *)malloc(sizeof(DArray));
  ret_val_if_fail(NULL != thiz, NULL);

  thiz->data = NULL;
  thiz->size = 0;
  thiz->alloc_size = 0;

  return thiz;
}

/*
 * expand dynamic array when accutly size larger than alloced size
 */
#define MIN_PRE_ALLOCATE_NR 10
static Ret darray_expand(DArray *thiz, size_t need)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  if ((thiz->size + need) > thiz->alloc_size)
  {
    size_t alloc_size = thiz->alloc_size + (thiz->alloc_size >> 1) + MIN_PRE_ALLOCATE_NR;

    void **data = (void **)realloc(thiz->data, sizeof(void*) * alloc_size);
    thiz->data = data;
    thiz->alloc_size = alloc_size;
  }
  
  return ((thiz->size + need) <= thiz->alloc_size) ? Ret_OK : Ret_Fail;
}

/*
 * shrink dynamic array size when accutly size less than unused size(thiz->alloc_size >> 1),
 * 
 */
static Ret darray_shrink(DArray *thiz)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  if ((thiz->size < (thiz->alloc_size >> 1)) && (thiz->alloc_size > MIN_PRE_ALLOCATE_NR))
  {
    size_t alloc_size = thiz->size + (thiz->size >> 1);

    void **data = (void**)realloc(thiz->data, sizeof(void*) * alloc_size);
    thiz->data = data;
    thiz->alloc_size = alloc_size;
  }

  return Ret_OK;
}

/*
 * destroy dynamic array 
 */
Ret darray_destroy(DArray *thiz)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  if (NULL == thiz->data)
  {
    free(thiz);
    thiz = NULL;
  }
  else
  {
    free(thiz->data);
    thiz->data = NULL;

    free(thiz);
    thiz = NULL;
  }

  return Ret_OK;
}

/*
 * insert a value by specify index 
 * notion: the index start from 0
 */
Ret darray_insert(DArray *thiz, size_t index, void *value)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);
  
  Ret ret = Ret_OOM;

  size_t cursor = index;
  cursor = cursor < thiz->size ? cursor : thiz->size;

  if (darray_expand(thiz, 1)  == Ret_OK)
  {
    size_t i = 0;
    for (i = thiz->size; i > cursor; i--)
    {
      thiz->data[i] = thiz->data[i-1];
    }

    thiz->data[cursor] = value;
    thiz->size++;

    ret = Ret_OK;
  }

  return ret;
}

/*
 * add a value on the array head
 */
Ret darray_prepend(DArray *thiz, void *value)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  return darray_insert(thiz, 0, value);
}

/*
 * add a value on the array last
 */
Ret darray_append(DArray *thiz, void *value)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  return darray_insert(thiz, -1, value);
}

Ret darray_delete(DArray *thiz, size_t index)
{
  ret_val_if_fail(NULL != thiz && index < thiz->size, Ret_InvalidParams);

  size_t i = 0;

  for (i = index; (i+1) < thiz->size; ++i)
  {
    thiz->data[i] = thiz->data[i+1];
  }
  thiz->size--;
  darray_shrink(thiz);

  return Ret_OK;
}

Ret darray_get_by_index(DArray *thiz, size_t index, void **value)
{
  ret_val_if_fail(thiz != NULL && value != NULL && index < thiz->size, Ret_InvalidParams);

  *value = thiz->data[index];

  return Ret_OK;
}

Ret darray_set_by_index(DArray *thiz, size_t index, void *value)
{
  ret_val_if_fail(thiz != NULL && value != NULL && index < thiz->size, Ret_InvalidParams);

  thiz->data[index] = value;

  return Ret_OK;
}

size_t darray_length(DArray *thiz)
{
  ret_val_if_fail(NULL != thiz, 0);

  return thiz->size;
}

Ret darray_froeach(DArray *thiz, DArrayDataVisitFunc visit, void *ctx)
{
  ret_val_if_fail(NULL != thiz, Ret_InvalidParams);

  Ret ret = Ret_OK;
  size_t i = 0;
  for (i = 0; i < thiz->size; ++i)
  {
    ret = visit(ctx, thiz->data[i]); 
  }

  return ret;
}
