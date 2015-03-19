/*************************************************************************
    > File Name: reverse.cpp
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Tue Mar 10 21:35:14 2015
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

void reverse(const char *pInputStr, char *pOutputStr)
{
  size_t inputStrLen = strlen(pInputStr);
  std::cout << "the inputStr len is: " << inputStrLen << std::endl;
  int i = 0;
  int j = inputStrLen - 1;
  while (j >= 0)
  {
    pOutputStr[i] = pInputStr[j];
    i++;
    j--;
  }
  pOutputStr[inputStrLen] = '\0';
}

void reverse1(char *pInputStr)
{
  size_t inputStrLen = strlen(pInputStr);
  std::cout << "the inputStr len is: " << inputStrLen << std::endl;
  int i = 0;
  int j = inputStrLen - 1;
  while (i < j) 
  {
    char temp =pInputStr[i];
    pInputStr[i] = pInputStr[j];
    pInputStr[j] = temp;
    i++;
    j--;
  }
}

int main()
{
  char str[] = "abcd";
  char outputStr[5];
  reverse1(str);
  std::cout << "str: " << str << std::endl;
/*  std::cout << "before str: " << str << " outputStr: " << outputStr << std::endl;
  reverse(str, outputStr);
  std::cout << "after str: " << str << " outputStr: " << outputStr << std::endl;
  */
  return 0;
}
