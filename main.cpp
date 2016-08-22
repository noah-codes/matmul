#include "matrix.h"
#include <iostream>

using namespace std;

template <typename T>
using Matrix = MatrixMath::Matrix<T>;

int test();

int main(int argc, char* argv[]) {
  float a[6] = {1, 0, 2, 2, 3, 4};
  Matrix<float>* mA = new Matrix<float>(2, 2);
  Matrix<float>* mB = new Matrix<float>(2, 2);
  Matrix<float>* q;
  q = MatrixMath::add<float, MatrixMath::Impl::CPU>(*mA, *mB);
  return 0;
}

int test() {
  float a[6] = {1,2,3,4,5,6};
  for (int i = 0; i < 6; ++i) {
    cout << a[i];
  }
  cout<<endl;
  return 0;
}
