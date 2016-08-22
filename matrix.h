#pragma once

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <immintrin.h>

using namespace std;

namespace MatrixMath {

enum Impl { CPU, CPU_SIMD, GPU };

template <typename T>
class Matrix {
 public:
  Matrix(size_t = 0, size_t = 0);
  Matrix(const Matrix<T>& matrix);
  ~Matrix();

  void fill(const T* elements);

  T get(size_t, size_t) const;
  void set(const T value, size_t, size_t);

  template <typename S, Impl I>
  friend Matrix<S>* add(const Matrix<S>& a, const Matrix<S>& b);

  template <typename S, Impl I>
  friend Matrix<S>* sub(const Matrix<S>& a, const Matrix<S>& b);

 private:
  T* data_;
  size_t rows_;
  size_t columns_;

  T* matrix_alloc(size_t, size_t, size_t);

  void check_bounds(size_t row, size_t column) const {
    assert(row < rows_);
    assert(column < columns_);
  }
};

template <typename T, Impl I>
Matrix<T>* add(const Matrix<T>& a, const Matrix<T>& b);

template <typename T, Impl I>
Matrix<T>* sub(const Matrix<T>& a, const Matrix<T>& b);

using Md = Matrix<float>;
using Mf = Matrix<float>;
using Mi = Matrix<int>;

template <>
Mf* add<float, Impl::CPU>(const Md& a, const Md& b) {
  assert(a.rows_ == b.rows_ && a.columns_ == b.columns_);

  Mf* c = new Md(a.rows_, a.columns_);

  for (int i = 0; i < a.rows_ * a.columns_; ++i) {
    c->data_[i] = a.data_[i] + b.data_[i];
  }

  return c;
}

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) {
  // Hardcoding 32 byte alignment for AVX for now.
  rows_ = rows;
  columns_ = columns;
  data_ = matrix_alloc(rows_, columns_, 32);
  memset(data_, 0, sizeof(T) * rows_ * columns_);
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& matrix) {
  // Hardcoding 32 byte alignment for AVX for now.
  rows_ = matrix.rows_;
  columns_ = matrix.columns_;
  data_ = matrix_alloc(rows_, columns_, 32);
  memcpy(data_, matrix.data_, sizeof(T) * rows_ * columns_);
}

template <typename T>
T* Matrix<T>::matrix_alloc(size_t rows, size_t columns, size_t align) {
  size_t ratio = align / sizeof(T);
  // TODO other ratios don't work, right?
  assert(ratio == 4 || ratio == 8);
  size_t blocks = rows * columns;
  blocks += ratio - blocks % ratio;
  return (T*)aligned_alloc(align, blocks * sizeof(T));
}

template <typename T>
Matrix<T>::~Matrix() {
  free(data_);
}

template <typename T>
T Matrix<T>::get(size_t row, size_t column) const {
  check_bounds(row, column);
  return data_[row * rows_ + column];
}

template <typename T>
void Matrix<T>::set(const T value, size_t row, size_t column) {
  check_bounds(row, column);
  data_[row * rows_ + column] = value;
}

template <typename T>
void Matrix<T>::fill(const T* elements) {
  memcpy(data_, elements, sizeof(T) * rows_ * columns_);
}
