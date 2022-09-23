#include <iostream>

#define MAX_N 40
#define MAX_K 40
int c[MAX_N+1][MAX_K+1];

void initTable()
{
  int n, k;
  
  // Fill in the base cases
  for(n = 1;n <= MAX_N;n++) {
    c[n][n] = 1;
    c[n][1] = n;
    c[n][0] = 1;
  }
  // Fill in the remaining entries
  for(n = 2;n <= MAX_N;n++){
    for(k = 2;k < n;k++)
      c[n][k] = c[n-1][k-1]+c[n-1][k];
    for(k = n+1;k <= MAX_K;k++)
      c[n][k] = 0;
  }
}

int C(int n,int k)
{
  if(k <= n)
    return c[n][k];
  else
    return 0;
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
