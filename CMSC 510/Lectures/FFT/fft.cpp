#include <iostream>
#include <fstream>
#include <complex>
#include <vector>
#include <math.h>

using namespace std;

typedef complex<double> comp;

complex<double> twoPiI(0.0,6.2831853071795864769);

int nextPower(int x)
{
  int result = 2;
  while(result < x)
    result *= 2;
  return result;
}

int readNumbers(const char* fileName,vector<comp>& x,vector<comp>& y)
{
  // First count the number of digits in each number.
  int countX = 0;
  int countY = 0;
  {
    ifstream in;
    in.open(fileName);
    char ch;
    while(true) {
      in.get(ch);
      if(ch < '0' || ch > '9')
        break;
      else
        countX++;
    }
    // The input data file was created on windows and has cr/lf line breaks
    // Read and skip the lf character.
    in.get(ch);
    while(true) {
      in.get(ch);
      if(ch < '0' || ch > '9')
        break;
      else
        countY++;
    }
    cout << "Digits read: " << countX << ' ' << countY << endl;
    in.close();
  }

  // We need to create two arrays of digits. Each array should be as wide as
  // twice the widest number seen, so that we have enough places to accomodate
  // the digits in an eventual product. Further, our FFT algorithm will 
  // expect to get a list with size N where N is a power of 2. Increase
  // size to the next power of 2.
  int size = (countX > countY)?countX:countY;
  size = nextPower(2*size);
  x.resize(size);
  y.resize(size);
  // Pad the fronts of x and y with zeros
  int indexX = 0;
  int indexY = 0;
  while(indexX + countX < size)
    x[indexX++] = comp(0,0);
  while(indexY + countY < size)
    y[indexY++] = comp(0,0);
  // Now read the digits into the arrays.
  {
    ifstream in;
    in.open(fileName);
    char ch;
    while(indexX < size) {
      in.get(ch);
      x[indexX++] = comp((ch - '0'),0);
    }
    // Eat up the end line characters
    in.get(ch);in.get(ch);
    while(indexY < size) {
      in.get(ch);
      y[indexY++] = comp((ch - '0'),0);
    }
    in.close();
  }
  return size;
}

void doFFT(vector<comp>& a,vector<comp>& y,int sign)
{
  int n = a.size();
  if(n == 1)
    y[0] = a[0];
  else
  {
    comp N(n,0);
    comp sg(sign,0);
    int k;
    comp root = exp(sg*twoPiI/N);
    comp omega(1.0,0);
    vector<comp> a0(n/2);
    vector<comp> a1(n/2);
    vector<comp> y0(n/2);
    vector<comp> y1(n/2);
    for(k = 0;k < n/2;k++) {
      a0[k] = a[2*k];
      a1[k] = a[1 + 2*k];
    }
    doFFT(a0,y0,sign);
    doFFT(a1,y1,sign);
    for(k = 0;k < n/2;k++) {
      y[k] = y0[k] + omega*y1[k];
      y[k + n/2] = y0[k] - omega*y1[k];
      omega *= root;
    }
  }
}

void FFT(vector<comp>& a,vector<comp>& y)
{
  doFFT(a,y,-1);
}

void InverseFFT(vector<comp>& a,vector<comp>& y)
{
  doFFT(a,y,1);
  comp N(y.size(),0);
  for(vector<comp>::iterator itr = y.begin();itr != y.end();itr++)
    *itr = (*itr)/N;
}

void makeDigits(const vector<comp>& a,vector<int>& b)
{
  // First extract integers from a
  b.resize(a.size());
  vector<int>::iterator dest = b.begin();
  for(vector<comp>::const_iterator src = a.begin();src != a.end();src++)
    *dest++ = int((*src).real()+0.5);

  // Typically when you multiply two digit polynomials the product polynomial
  // has coefficients that may have more than a single digit. This has to
  // be fixed.
  // We do this by replacing each digit by the digit mod 10 and then
  // 'carrying' digit/10 over to the next place.
  for(int n = b.size() - 1;n > 0;n--) {
    b[n-1] += b[n]/10;
    b[n] = b[n]%10;
  }
}

void outputResult(const char* fileName,const vector<int>& digits)
{
  ofstream out;
  out.open(fileName);

  int n = 0;
  while(digits[n] == 0)
    n++;
  while(n < digits.size())
    out << digits[n++];
  out << endl;
  out.close();
}

template <class T>
void reverseList(vector<T>& v)
{
  int last = v.size() - 1;
  int m = last;
  for(int n = 0;n <= last/2;n++)
  {
    T temp = v[n];
    v[n] = v[m];
    v[m] = temp;
    m--;
  }
}

int main()
{
  vector<comp> x;
  vector<comp> y;

  int size = readNumbers("numbers.txt",x,y);
  // The lists now have to be reversed, because the coefficients of the
  // digit polynomials are listed from highest to lowest powers, with a0
  // at the end. FFT expects to have its data series organized with a0
  // as the very first term.
  reverseList(x);
  reverseList(y);

  vector<comp> a(size);
  vector<comp> b(size);

  FFT(x,a);
  FFT(y,b);

  // Now compute the termwise product of the two transformed lists.
  for(int n = 0;n < size;n++)
    a[n] = a[n]*b[n];

  vector<comp> z(size);
  InverseFFT(a,z);
  // Before evaluating the digit polynomial we have to reverse the list
  // again so that the coefficients are listed in order from highest to
  // lowest powers.
  reverseList(z);

  // The list that results is a list of complex coefficients for a digit
  // polynomial. Convert the complex numbers to integers and store the
  // integer digits in a result vector and further process the integer
  // coefficients so that they are all single digit numbers except for
  // possibly the first one.
  vector<int> result(size);
  makeDigits(z,result);

  // Now do the final output.
  outputResult("result.txt",result);

  return 0;
}