#include "row.h"

Row::Row(size_t len_, int *row_) : len_(len_), row_(row_)
{
}

int &
Row::operator[](size_t idx)
{
    if (idx >= len_) {
        throw std::out_of_range("Column index is out of range.");
    }
    return row_[idx];
}

int
Row::operator[](size_t idx) const
{
    if (idx >= len_) {
        throw std::out_of_range("Column index is out of range.");
    }
    return row_[idx];
}
