#include <iostream>
#include <immintrin.h>

int main(int argc, char *argv[]) {

  // AVX
  // __m256 one = _mm256_set_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
  // __m256 two = _mm256_set_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
  
  float* vec = new float[8];
//  float* ved = new float[8];
  for (int i = 0; i < 8; ++i) {
    vec[i] = 1.0 * i;
//    ved[i] = 2.0 * i;
  }

  __m256 one = _mm256_load_ps(vec);
//  __m256 two = _mm256_loadu_ps(ved);
//  __m256 sum = _mm256_add_ps(one, two);

//  float* output = (float*)&sum;
//  for (int i = 0; i < 8; ++i) {
//    std::cout << sum[i] << std::endl;
//  }
  return 0;
}
