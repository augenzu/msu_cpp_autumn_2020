#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
#include <cstring>

class Allocator
{
private:
    char *mem_{nullptr};
    size_t capacity_{};
    size_t offset_{};
    bool allocator_is_created_{false};

public:
    Allocator();
    ~Allocator();
    void 
    make_allocator(size_t max_size);
    char *
    alloc(size_t size);
    void 
    reset();
};

#endif
