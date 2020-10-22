#include "row.h"

Row::Row(size_t len_, int *&row_) : len_(len_), row_(row_)
{
}

int &
Row::operator[](size_t idx)
{
    assert(idx < len_);
    return row_[idx];
}

int
Row::operator[](size_t idx) const
{
    assert(idx < len_);
    return row_[idx];
}