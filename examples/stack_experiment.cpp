#include <iostream>
#include "..\src\zero.cpp"

void f(int *a)
{
  int b = 0x45; // hey look a new local variable inside a function

  // compare the two addresses
  if (a < &b)
    std::cout << "Stack grows up";
  else
    std::cout << "Stack grows down";
}

int main()
{
  int a = 0x45;                          // hey look a local variable
  f(&a);                          // passing address (ptr)
  zero::disassemble(f, 20, true);
  std::cin.get();
}