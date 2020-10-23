#ifndef MARTRIX_H
#define MATRIX_H

#include "row.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <stdexcept>

class Matrix
{
private:
    size_t rows_{}, cols_{};
    int **data_{};
    void
    swap(Matrix &);
    void
    fill(int filler);
    void
    fill(const Matrix &);

public:
    Matrix(size_t rows_ = 1, size_t cols_ = 1);
    Matrix(const Matrix &);
    ~Matrix();
    Matrix &
    operator=(const Matrix &);
    size_t
    rows() const;
    size_t
    columns() const;
    Matrix &
    operator*=(int);
    bool
    operator==(const Matrix &) const;
    bool
    operator!=(const Matrix &) const;
    Row
    operator[](size_t idx) const;
};

#endif
