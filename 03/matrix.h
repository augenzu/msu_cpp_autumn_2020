// TODO: REMOVE ALL THE TODOS
// TODO: smart pointers?

#ifndef MARTRIX_H
#define MATRIX_H

#include "row.h"
#include <algorithm>
#include <iostream>

class Matrix
{
private:
    size_t rows_{}, cols_{};
    int **data_{};
    void
    swap(Matrix &);
    Row &
    operator[](size_t idx);
    Row
    operator[](size_t idx) const;

public:
    Matrix(size_t, size_t);
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
};

#endif