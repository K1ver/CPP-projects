#ifndef S21_MATRIX_PLUS_H
#define S21_MATRIX_PLUS_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <utility>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated
  void MallocMatrix() noexcept;
  S21Matrix GetMinor(int rows, int cols) noexcept;
  void Free() noexcept;

 public:
  S21Matrix() noexcept;  // Default constructor
  S21Matrix(int rows, int cols) noexcept;
  S21Matrix(const S21Matrix& other) noexcept;
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix() noexcept;  // Destructor

  bool EqMatrix(const S21Matrix& other) noexcept;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num) noexcept;
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose() noexcept;
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*=(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*=(const double num);
  bool operator==(const S21Matrix& other);
  S21Matrix operator=(const S21Matrix& other);
  double& operator()(int row, int col);
};

#endif