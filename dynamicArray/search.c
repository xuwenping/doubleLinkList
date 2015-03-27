/*************************************************************************
	> File Name: search.c
	> Author: 
	> Mail: 
	> Created Time: Thu Mar 26 23:51:28 2015
 ************************************************************************/

#include<stdio.h>
#include "search.h"

int qsearch(void **array, size_t nr, void *data, DataCompareFunc cmp)
{
  int low = 0;
  int high = nr-1;
  int mid = 0;
  int result = 0;

  while(low <= high)
  {
    mid = low + ((high - low) >> 1);
    result = cmp(array[mid], data);

    if(0 == result)
    {
      return mid;
    }

    if(0 > result)
    {
      low = mid + 1;
    }
    else
    {
      high = mid - 1;
    }
  }

  return -1;
}

#ifdef QSEARCH_TEST
#include <assert.h>

static int int_cmp(void *a, void *b)
{
  return (int)a - (int)b;
}

static void qsearch_test(size_t nr)
{
  void **array = (void **)malloc(sizeof(void *) * nr);   
  size_t i = 0;
  for(i = 0; i < nr; ++i)
  {
    array[i] = i;
  }
  
  for(i = 0; i < nr; ++i)
  {
    int ret =  qsearch(array, nr, (void *)i, int_cmp);
    printf("the ret is %d, the i is %d\n", ret, i);
    assert(ret == i);
  }
}

int main()
{
  int i = 0;
  for(i = 1; i < 1000; ++i)
  {
    qsearch_test(i);  
  }
  return 0;
}

#endif
