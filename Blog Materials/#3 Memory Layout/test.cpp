#include <iostream>

int main(void)
{
  int* p1 = new int;
  int sumPow2 = 0;
  
  for(unsigned int i = 0; i < 16; ++i)
    sumPow2 += (1 << i);
  
  //std::cout << pow2 << std::endl;
  
  *p1 = sumPow2;
  
  std::cout << *p1 << std::endl;
  std::cout << static_cast<int>(*(reinterpret_cast<unsigned char*>(p1))) << std::endl;
  std::cout << static_cast<int>(*(reinterpret_cast<unsigned char*>(p1) + 1)) << std::endl;
  std::cout << static_cast<int>(*(reinterpret_cast<unsigned char*>(p1) + 2)) << std::endl;
  std::cout << static_cast<int>(*(reinterpret_cast<unsigned char*>(p1) + 3)) << std::endl;
  
  int* p2 = reinterpret_cast<int*>(100);
  int* p3 = p2 + 1;
  
  std::cout << p3 << std::endl;
  std::cout << p3 - p2 << std::endl;
  
  delete p1;
  
  return 0;
}