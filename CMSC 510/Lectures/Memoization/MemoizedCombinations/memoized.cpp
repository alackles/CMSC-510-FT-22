#include <iostream>

#define MAX_N 40
#define MAX_K 40
int c[MAX_N+1][MAX_K+1];

void initTable()
{
  int n,k;
  for(n = 1;n <= MAX_N;n++)
    for(k = 1;k <= MAX_K;k++)
      c[n][k] = 0;
}

int C(int n,int k)
{
  int result = c[n][k];

  if(result == 0)
  {
    if(k == 1)
      result = n;
    else if(k == n)
      result = 1;
    else
      result = C(n-1,k-1)+C(n-1,k);

    c[n][k] = result;
  }
  
  return result;
}

int main (int argc, const char * argv[]) 
{ 
  int n,k;
  
  initTable();
  
  std::cout << "Enter n and k:";
  std::cin >> n >> k;
  
  while(n != 0)
  {
      std::cout << "C(" << n << "," << k << ")= " << C(n,k) << std::endl;

	std::cout << "Enter n and k: ";
	std::cin >> n >> k;
  }
  
  return 0;
}