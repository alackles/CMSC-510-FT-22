#include <iostream>

int C(int n,int k)
{
  if(k == 1)
    return n;
  if(k == n)
    return 1;
  return C(n-1,k-1)+C(n-1,k);
}

int main (int argc, const char * argv[]) 
{ 
  int n,k;
  
  std::cout << "Enter n and k: ";
  std::cin >> n >> k;

  while(n != 0) {
      std::cout << "C(" << n << "," << k << ")= " << C(n,k) << std::endl;

	std::cout << "Enter n and k: ";
	std::cin >> n >> k;
  }

  return 0;
}