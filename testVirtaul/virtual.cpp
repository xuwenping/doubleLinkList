/*************************************************************************
    > File Name: virtual.cpp
    > Author: DevinXu
    > Mail: xuwenping3211@gmail.com
    > Created Time: Tue Mar 10 02:00:28 2015
 ************************************************************************/

#include<iostream>
using namespace std;

class Base {
  public:
    virtual void f() {
      std::cout << "Base::f" << std::endl;
    } 
    
    virtual void g() {
      std::cout << "Base::g" << std::endl;
    }
    
    virtual void h() {
      std::cout << "Base::h" << std::endl;
    }
};
void func1() 
{
  int a = 2;
}
int main()
{
  typedef void (*Func)(void);

  Base b;

  Func pFunc = NULL;
  std::cout << "virtual table: " << (int*)(&b) << std::endl;
  std::cout << "virtual table---the first func addr: " << (int*)*(int*)(&b) << endl;
  pFunc = func1;
  pFunc = (Func)*((int*)*(int*)(&b));
  pFunc();
  return 0;
}
