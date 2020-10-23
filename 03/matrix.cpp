#include "matrix.h"

void
Matrix::swap(Matrix &rhs)
{
    std::swap(data_, rhs.data_);
    std::swap(rows_, rhs.rows_);
    std::swap(cols_, rhs.cols_);
}

void
Matrix::fill(int filler)
{
    for (size_t i = 0; i < rows_; ++i) {
        std::fill(data_[i], data_[i] + cols_, filler);
    }
}

void
Matrix::fill(const Matrix &rhs)
{
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            data_[i][j] = rhs.data_[i][j];
        }
    }
}

Matrix::Matrix(size_t rows_, size_t cols_) : rows_(rows_), cols_(cols_)
{
    assert(rows_ > 0 && cols_ > 0);

    data_ = new int *[rows_];
    assert(data_ != nullptr);

    for (size_t i = 0; i < rows_; ++i) {
        data_[i] = new int[cols_];
        assert(data_[i] != nullptr);
    }

    fill(0);
}

Matrix::Matrix(const Matrix &rhs) : Matrix(rhs.rows_, rhs.cols_)
{
    fill(rhs);
}

Matrix::~Matrix()
{
    for (size_t i = 0; i < rows_; ++i) {
        delete[] data_[i];
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

Row
Matrix::operator[](size_t idx) const
{
    if (idx >= rows_) {
        throw std::out_of_range("Row index is out of range.");
    }
    Row row{cols_, data_[idx]};
    return row;
}

std::ostream &
operator<<(std::ostream &out, const Matrix &m)
{
    for (size_t i = 0; i < m.rows(); ++i) {
        for (size_t j = 0; j < m.columns(); ++j) {
            out << m[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}