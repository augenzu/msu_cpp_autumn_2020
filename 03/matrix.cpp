#include "matrix.h"

void
Matrix::swap(Matrix &rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(rows_, rhs.rows_);
    std::swap(cols_, rhs.cols_);
}

Matrix::Matrix(size_t rows_ = 1, size_t cols_ = 1) : rows_(rows_), cols_(cols_)
{
    data_ = new int *[rows_];
    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        std::fill(data_[i], data_[i] + cols_, 0);
    }
}

Matrix::Matrix(const Matrix &rhs) : Matrix(rhs.rows_, rhs.cols_)
{
}

// Matrix::Matrix(const Matrix &rhs) : rows_(rhs.rows_), cols_(rhs.cols_)
// {
//     data_ = new int *[rows_];
//     for (size_t i = 0; i < rows_; ++i) {
//         data_[i] = new int[cols_];
//         std::fill(data_[i], data_[i] + cols_, 0);
//     }
// }

Matrix::~Matrix()
{
    for (size_t i = 0; i < rows_; ++i) {
        delete[] data_[i];
        // data_[i] = nullptr;
    }
    delete[] data_;
    data_ = nullptr;
}

Matrix &
Matrix::operator=(const Matrix &rhs)
{
    Matrix rhs_{rhs};
    swap(rhs_);
    return *this;
}

size_t
Matrix::rows() const
{
    return rows_;
}

size_t
Matrix::columns() const
{
    return cols_;
}

Matrix &
Matrix::operator*=(int mul)
{
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] *= mul;
        }
    }
    return *this;
}

bool
Matrix::operator==(const Matrix &rhs) const
{
    if (rows_ != rhs.rows_ || cols_ != rhs.cols_) {
        return false;
    }
    
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (data_[i][j] != rhs.data_[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool
Matrix::operator!=(const Matrix &rhs) const
{
    return !(*this == rhs);
}

// Row &   // do we really need this??? (+ reference to inner object...)
// Matrix::operator[](size_t idx)
// {
//     Row row{cols_, data_[idx]};
//     return row;
// }

Row
Matrix::operator[](size_t idx) const
{
    Row row{cols_, data_[idx]};
    return row;
}