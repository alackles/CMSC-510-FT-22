#include <iostream>
#include <fstream>
#include <iomanip>

int counts[101][101];

void initCounts(int maxN,int maxK)
{
  int n,k;
  for(n = 1;n <= maxN;n++)
    for(k = 1;k <= maxK;k++)
      counts[n][k] = 0;
}

int C(int n,int k)
{
  counts[n][k]++;

  if(k == 1)
    return n;
  if(k == n)
    return 1;
  return C(n-1,k-1)+C(n-1,k);
}

void saveCounts(int maxN,int maxK)
{
  std::ofstream out;
  int n,k;

  out.open("/Users/greggj/Desktop/CountCalls/CountCalls/counts.txt");
  for(n = 1;n <= maxN;n++)
  {
    for(k = 1;k <= maxK;k++)
      out << std::setw(5) << counts[n][k];
    out << std::endl;
  }
  out.close();
}

int main (int argc, const char * argv[]) 
{ 
  int n,k;
  
  std::cout << "Enter n and k:";
  std::cin >> n >> k;
  
  initCounts(n,k);
    std::cout << "C(" << n << "," << k << ")= " << C(n,k) << std::endl;
  saveCounts(n,k);
  
  return 0;
}