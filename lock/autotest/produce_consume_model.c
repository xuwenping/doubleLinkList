/*************************************************************************
	> File Name: produce_consume_model.c
	> Author: 
	> Mail: 
	> Created Time: Fri 27 Mar 2015 09:48:36 PM CST
 ************************************************************************/
#include "produce_consume_model.h"
#include <ctype.h>


void consume_create(List *thiz)
{
  ret_if_fail(NULL != thiz);
  printf("enter the consume_create func\n");
  List_pop(thiz);
}

void produce_create(List *thiz)
{
  ret_if_fail(NULL != thiz);
  int a = 1;

  printf("enter the produce_create func\n");
  List_push(thiz, a);
}

#ifdef LOCK_TEST

void lock_test(List *thiz)
{
  pthread_t t1 = 0;
  pthread_t t2 = 0;
  
  pthread_create(&t1, NULL, produce_create, (void *)thiz);
  pthread_create(&t2, NULL, consume_create, (void *)thiz);
  
  pthread_join(t2, NULL);
  pthread_join(t1, NULL);
}

int main()
{
  List *thiz = List_create();
  lock_test(thiz); 

  List_destroy(thiz);
  return 0;
}
#endif
