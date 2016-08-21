#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstring>

using namespace std;

template <typename T>
class Matrix {
 public:
  Matrix(size_t = 0, size_t = 0);
  ~Matrix();

  T get(size_t, size_t) const;
  void set(const T value, size_t, size_t);

  void fill(const T* elements);

 private:
  T* matrix_;
  size_t rows_;
  size_t columns_;

  void check_bounds(size_t row, size_t column) const {
    assert(row < rows_);
    assert(column < columns_);
  }
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t columns) {
  // Hardcoding 32 byte alignment for AVX for now.
  rows_ = rows;
  columns_ = columns;
  matrix_ = (T*)aligned_alloc(32, sizeof(T) * rows_ * columns_);
  memset(matrix_, 0, sizeof(T) * rows_ * columns_);
}

template <typename T>
Matrix<T>::~Matrix() {
  free(matrix_);
}

template <typename T>
T Matrix<T>::get(size_t row, size_t column) const {
  check_bounds(row, column);
  return matrix_[row * rows_ + column];
}

template <typename T>
void Matrix<T>::set(const T value, size_t row, size_t column) {
  check_bounds(row, column);
  matrix_[row * rows_ + column] = value;
}

template <typename T>
void Matrix<T>::fill(const T* elements) {
  memcpy(matrix_, elements, sizeof(T) * rows_ * columns_);
}
