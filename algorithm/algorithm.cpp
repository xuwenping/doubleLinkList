/*************************************************************************
    > File Name: algorithm.cpp
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Tue Mar 10 23:01:45 2015
 ************************************************************************/

#include<iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

void swap(int &a, int &b)
{
  int temp = a;
  a = b;
  b = temp;
}

void insertSort(int *a, int len)
{
  int i;
  int j;
  for (i = 1; i < len; ++i)
  {
    j = i;
    while ((j > 0) && (a[j-1] > a[j]) )
    {
      swap(a[j-1], a[j]);
      j--;
    }
  }
}

void choiceSort(int *a, int len)
{
  int i;
  int j;
  int min;
  for (i = 0; i < (len - 1); ++i) 
  {
    min = i;
    for (j = (i + 1); j < len; ++j)
    {
      if (a[min] > a[j])
      {
        min = j;
      }
    }

    if (min != i)
    {
      swap(a[i], a[min]);
    }
  }
}

void quickSort(int *a, int left, int right)
{
  int save_left = left;
  int save_right = right;
  int x = a[left];
  while (left < right) 
  {
    while ((a[right] >= x) && (left < right))
      right--;
    if (left != right)
    {
      a[left] = a[right];
      left++;
    }

    while ((a[left] <= x) && (left < right))
      left++;
    if (left != right)
    {
      a[right] = a[left];
      right--;
    }
  }
  a[left] = x;

  if (save_left < left)
  {
    quickSort(a, save_left, left - 1);
  }
  if (save_right > left)
  {
    quickSort(a, left + 1, save_right);
  }
}

int main()
{
  int a[] = {6, 9, 4, 10, 2, 2, 1, 5, 3, 8, 7};
  int len = sizeof(a)/sizeof(int);
  std::cout << "before: " << std::endl; 
  for (int i = 0; i < len; ++i)
  {
    std::cout << a[i] << ", ";
  }
  std::cout << std::endl;
  //insertSort(a, len);
  //choiceSort(a, len);
  quickSort(a, 0, len - 1);
  std::cout << "after: " << std::endl;
  for (int i = 0; i < len; ++i)
  {
    std::cout << a[i] << ", ";
  }
  std::cout << std::endl;
  
  return 0;
}
