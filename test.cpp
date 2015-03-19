/*************************************************************************
    > File Name: test.cpp
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Thu Mar 12 01:09:38 2015
 ************************************************************************/

#include<iostream>
using namespace std;

int test(int *& a)
{
  int m = 6;
  int *p = &m;
  a = p;
}

int main()
{
  int a = 5;
  int *p = &a;

  int *& ptr = p;
  test(ptr);
  std::cout << "*p = " << *p << std::endl;
  return 0;
}
