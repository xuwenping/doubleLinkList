/*************************************************************************
	> File Name: sort.c
	> Author: 
	> Mail: 
	> Created Time: Tue Mar 24 02:29:34 2015
 ************************************************************************/

#include <stdio.h>
#include "sort.h"

static void swap(void *a, void *b)
{
  void *temp = *a;
  *a = *b;
  *b = temp;
}

Ret bubble_sort(void **array, size_t nr, DataCompareFunc cmp)
{
  int i = 0;
  int j = 1;
  for(i = 0; i < nr-1; ++i)
  {
    for(j = 1; j < nr; ++j)
    {
      if(cmp(array[i], array[j]) > 0)
      {
        swap(&array[i], &array[j]);
      }
    }
  }

  return Ret_OK;
}

Ret change_sort(void **array, size_t nr, DataCompareFunc cmp)
{
  int i = 0;
  int j = 1;
  int iMax = 0;
  for(i = 0; i < (nr-1); ++i)
  {
    iMax = i;
    for(j = 1; j < nr; ++j)
    {
      if(cmp(array[iMax], array[j]) > 0)
      {
        iMax = j;
      }
    }

    if(iMax != i)
    {
      swap(&array[iMax], &array[i]);
    }
  }

  return Ret_OK;
}

Ret insert_sort(void **array, size_t nr, DataCompareFunc cmp)
{
  int i = 0;
  int j = 0;
  for(i = 0; i < (nr-1); ++i)
  {
    j = j + 1;
    while(j > 0)
    {
      if(cmp(array[j-1], array[j]) > 0)
      {
        swap(&array[j-1], &array[j]);
      }
      --j;
    }
  }

  return Ret_OK;
}

static void quick_sort_impl(void **array, size_t left, size_t right, DataCompareFunc cmp)
{
  size_t save_left = left;
  size_t save_right = right;
  void *x = array[left];

  while(left < right)
  {
    while((cmp(array[right], x) >= 0) && (left < right)) {--right;} 
    if(left != right)
    {
      array[left] = array[right];
      ++left;
    }

    while((cmp(array[left], x) <= 0) && (left < right)) {++left;}
    if(left != right)
    {
      array[right] = array[left];
      --right;
    }
  }
  array[left] = x;


}

Ret quick_sort(void **array, size_t nr, DataCompareFunc cmp)
{
  ret_val_if_fail((NULL != array) && (NULL != cmp), Ret_InvalidParams);

  Ret ret = Ret_OK;
  if(nr > 1)
  {
    quick_sort_impl(array, 0, (nr-1), cmp);  
  }

  return ret;
}
