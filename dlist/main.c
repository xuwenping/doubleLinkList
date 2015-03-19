/*************************************************************************
    > File Name: main.c
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Mon Mar  2 22:24:57 2015
 ************************************************************************/

#include<stdio.h>
#include "dlist.h"

int main()
{
  node_t* head = createLinkList(0);
  int i;
  for (i = 1; i < 10; ++i)
  {
    if (Ret_ok != pushFront(&head, i))
    {
      printf("the push operate fail\n");
    }
  }

  dispalyAllNode(head);
  return 0;
}
