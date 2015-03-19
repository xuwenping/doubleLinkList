/*************************************************************************
    > File Name: main.c
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  9 05:02:53 2015
 ************************************************************************/

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include "dlist.h"

static DListRet printInt(void *ctx, void *value)
{
  printf("the value is %d\n", (int)value);

  return DList_Ret_OK;
}

static DListRet sum_cb(void *ctx, void *data)
{
  long long *sum = ctx;
  *sum += (int)data;

  return DList_Ret_OK;
}

static DListRet cmp(void *ctx, void *data)
{
  int *max = ctx;
  if (*max < (int)data)
  {
    *max = (int)data;
  }

  return DList_Ret_OK;
}

static DListRet str_toupper(void *ctx, void *data)
{
  char *p = (char *)data;
  if (NULL != p)
  {
    while (*p != '\0')
    {
      if (islower(*p))
      {
        *p = toupper(*p);
      }
      p++;
    }
  }

  return DList_Ret_OK;
}

static DListRet str_print(void *ctx, void *data)
{
  printf("the value is %s\n", data);

  return DList_Ret_OK;
}

int main()
{
  List *testList = List_create();
/*
  int i = 0;
  int n = 100;
  for (i = 0; i < n; i++)
  {
    assert(List_push(testList, (void *)i) == DList_Ret_OK);
  }

  List_foreach(testList, printInt, NULL);

  long long sum = 0;
  List_foreach(testList, sum_cb, &sum);
  printf("the sum is %ld\n", sum);

  int max = 0;
  List_foreach(testList, cmp, &max);
  printf("The max value is %d\n", max);

  List_destroy(testList);
*/

  //string
  List *testStr = List_create();
  //List_push(testStr, strdup())  
  char str[256] = {0};
  strcpy(str, "It");
  List_push(testStr, str);
  List_foreach(testStr, str_toupper, NULL);
  List_foreach(testStr, str_print, NULL);

  List_destroy(testStr);

  return 0;
}
