#include "s21_matrix_oop.h"

void S21Matrix::MallocMatrix() noexcept {
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::Free() noexcept {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix() noexcept : rows_(0), cols_(0), matrix_(nullptr) {}

S21Matrix::S21Matrix(int rows, int cols) noexcept : rows_(rows), cols_(cols) {
  if (rows_ < 0 || cols_ < 0) {
    std::length_error("Cols and rows must be greater or equal zero");
  }
  MallocMatrix();
}

S21Matrix::S21Matrix(const S21Matrix& other) noexcept
    : rows_(other.rows_), cols_(other.cols_) {
  MallocMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() noexcept { Free(); }

bool S21Matrix::EqMatrix(const S21Matrix& other) noexcept {
  int res = 1;
  if (rows_ != other.rows_ || cols_ != other.cols_ || matrix_ == nullptr ||
      other.matrix_ == nullptr) {
    res = 0;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          res = 0;
        }
      }
    }
  }
  return res;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    std::length_error("length matrix not equal");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    std::length_error("length matrix not equal");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) noexcept {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    std::length_error(
        "The number of columns of the first matrix is not equal to the number "
        "of rows of the second matrix.");
  }

  S21Matrix result{rows_, other.cols_};

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(result);
}

S21Matrix S21Matrix::GetMinor(int rows, int cols) noexcept {
  S21Matrix minor{rows_ - 1, cols_ - 1};
  int minor_i = 0, minor_j = 0;
  for (int i = 0; i < rows_; i++) {
    if (i == rows) continue;
    minor_j = 0;
    for (int j = 0; j < cols_; j++) {
      if (j == cols) continue;
      minor.matrix_[minor_i][minor_j] = matrix_[i][j];
      minor_j++;
    }
    minor_i++;
  }
  return minor;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    std::logic_error("rows not eq cols");
  }
  double det = 0.0;
  int rows = rows_;
  if (rows == 1) {
    det = matrix_[0][0];
  } else if (rows == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int p = 0; p < rows; p++) {
      S21Matrix minor = GetMinor(0, p);
      double minor_det = minor.Determinant();
      det += matrix_[0][p] * minor_det * ((p % 2 == 0) ? 1 : -1);
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    std::logic_error("rows not eq cols");
  }
  S21Matrix result{rows_, cols_};
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = GetMinor(i, j);
      result.matrix_[i][j] = pow(-1, i + j) * minor.Determinant();
    }
  }
  return result;
}

S21Matrix S21Matrix::Transpose() noexcept {
  S21Matrix result{cols_, rows_};
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  S21Matrix result{rows_, cols_};
  if (fabs(det) < 1e-07) {
    std::logic_error("Matrix determinant is 0");
  } else if (rows_ == 1) {
    result.matrix_[0][0] = 1.0 / det;
  } else {
    S21Matrix complements = CalcComplements();
    S21Matrix transpodet = complements.Transpose();
    transpodet.MulNumber(1.0 / det);
    result = transpodet;
  }
  return result;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetCols(int cols) {
  if (cols >= 0 && cols > cols_) {
    S21Matrix result{rows_, cols};
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols; j++) {
        if (j >= cols_) {
          result(i, j) = 0;
        } else {
          result(i, j) = matrix_[i][j];
        }
      }
    }
    *this = result;
  }
}

void S21Matrix::SetRows(int rows) {
  if (rows >= 0 && rows > rows_) {
    S21Matrix result{rows, cols_};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols_; j++) {
        if (i >= rows_) {
          result(i, j) = 0;
        } else {
          result(i, j) = matrix_[i][j];
        }
      }
    }
    *this = result;
  }
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SumMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix res(*this);
  res.SubMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix res(*this);
  res.MulMatrix(other);
  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator=(const S21Matrix& other) {
  this->Free();
  rows_ = other.rows_;
  cols_ = other.cols_;
  MallocMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || col < 0 || row < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row][col];
}