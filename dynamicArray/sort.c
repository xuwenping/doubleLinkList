/*************************************************************************
	> File Name: sort.c
	> Author: 
	> Mail: 
	> Created Time: Tue Mar 24 02:29:34 2015
 ************************************************************************/

#include <stdio.h>
#include "sort.h"

Ret bubble_sort(void **array, size_t nr, DataCompareFunc cmp, DataSwapFunc swap)
{
  printf("enter %s\n", __func__);
  int i = 0;
  int j = 0;
  for(i = 0; i < (nr-1); ++i)
  {
    for(j = 0; j < nr-1-i; ++j)
    {
      printf("bubble before: the array[%d]=%d, the array[%d]=%d\n", j, array[j], j+1, array[j+1]);
      if(cmp(array[j], array[j+1]) > 0)
      {
        swap(array[j], array[j+1]);
      }
      printf("bubble after: the array[%d]=%d, the array[%d]=%d\n", j, array[j], j+1, array[j+1]);
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
      void *temp = array[iMax];
      array[iMax] = array[i];
      array[i] = temp;
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
        void *temp = array[j-1];
        array[j-1] = array[j];
        array[j] = temp;
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
  
  if(save_left < left)
  {
    quick_sort_impl(array, save_left, left-1, cmp);
  }

  if(save_right > left)
  {
    quick_sort_impl(array, left+1, save_right, cmp);
  }
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

#ifdef SORT_TEST

#include <stdlib.h>

static int int_cmp(void *a, void *b)
{
  return (int)a - (int)b;
}

static int int_cmp_invert(void *a, void *b)
{
  return (int)b - (int)a;
}

static void int_swap(void *a, void *b)
{
  int *temp_a = a;
  int *temp_b = b;
  int temp = temp_a;
  temp_a = temp_b;
  temp_b = temp;
}

static int *create_int_array(int n)
{
  printf("enter %s\n", __func__);
  int i = 0;
  int *array = (int *)malloc(sizeof(int) * n);
  
  for(i = 0; i < n; ++i)
  {
    array[i] = rand();
  }

  printf("end %s\n", __func__);
  return (void **)array;
}

void sort_test_one_asc(SortFunc sort, int n)
{
  int i = 0;
  void **array = create_int_array(n);
  for(i = 0; i < n; ++i)
  {
    printf("the element is %d\n", (int)array[i]);
  }
  ret_if_fail(NULL != array);
  sort(array, n, int_cmp, int_swap);
  printf("the n value is %d\n", n);

  for(i=1; i < n; ++i)
  {
    printf("asc: the array[%d]=%d, the array[%d]=%d\n", i, array[i], i-1, array[i-1]);
    assert(array[i] >= array[i-1]);
  }


  printf("the n value is %p\n", array);
  free(array);
  array = NULL;
}

void sort_test_one_dec(SortFunc sort, int n)
{
  int i = 0;
  void **array = create_int_array(n);
  sort(array, n, int_cmp_invert, int_swap);

  for(i = 1; i < n; ++i)
  {
    printf("dec: the array[%d]=%d, the array[%d]=%d\n", i, array[i], i-1, array[i-1]);
    assert(array[i] <= array[i-1]);
  }

  free(array);
}

static void sort_test(SortFunc sort)
{
  int i = 0;
  for(i = 1; i < 100; ++i)
  {
    printf("the i is %d\n", i);
    sort_test_one_asc(sort, i);
    //sort_test_one_dec(sort, i);
  }
}

int main()
{
  srand(100);
  sort_test(bubble_sort);
  return 0;
}
#endif
