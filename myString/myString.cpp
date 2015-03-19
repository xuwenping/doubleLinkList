/*************************************************************************
    > File Name: myString.cpp
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Wed Mar 11 21:44:59 2015
 ************************************************************************/

#include<iostream>
#include <string.h>
using namespace std;

class myString {
public:
  myString();
  myString(char *str);
  myString(const myString &other);
  myString & operator=(const myString &other);
  ~myString();

  void showString();

private:
  char *m_str;
};

myString::myString()
{
  m_str = new char[1];
  char a[] = "";
  strcpy(m_str, a);
}

myString::myString(char *str)
{
  if (NULL == str)
  {
    m_str = new char[1];
    *m_str = '\0';
  }
  else
  {
    int len = strlen(str);
    m_str = new char[len+1];
    strcpy(m_str, str);
  }
}

myString::myString(const myString &other)
{
  int len = strlen(other.m_str);
  m_str = new char[len+1];
  strcpy(m_str, other.m_str);
}

myString & myString::operator=(const myString &other)
{
  if (this == &other)
    return *this;

  delete []m_str;
  int len = strlen(other.m_str);
  m_str = new char[len+1];
  strcpy(m_str, other.m_str);

  return *this;
}

myString::~myString()
{
  delete []m_str;
}

void myString::showString()
{
  std::cout << "the str is: " << m_str << std::endl;
}

int main()
{
  char a[] = "abcd";
  myString str(a);
  str.showString();
  myString str1;
  str1 = str;
  str1.showString();
  return 0;
}
