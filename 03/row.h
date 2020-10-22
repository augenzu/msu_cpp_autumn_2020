#ifndef ROW_H
#define ROW_H

#include <iostream>
#include <cassert>

class Row
{
private:
    size_t len_{};
    int *row_{};

public:
    Row(size_t, int *&);
    ~Row() = default;
    Row(const Row &) = default;
    Row &
    operator=(const Row &) = delete;
    int &
    operator[](size_t idx);
    int
    operator[](size_t idx) const;
};

#endif