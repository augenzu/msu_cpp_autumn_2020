#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <iostream>

template<class T>
class Allocator
{
public:
    using value_type = T;

    Allocator() = default;

    ~Allocator() = default;

    [[nodiscard]] T *
    allocate(size_t sz) const
    {
        if (sz > std::numeric_limits<size_t>::max() / sizeof(T)) {
            throw std::bad_alloc();
        }
        if (T *ptr = static_cast<T *>(std::calloc(sz, sizeof(T)))) {
            return ptr;
        }
        throw std::bad_alloc();
    }

    void
    deallocate(T *ptr, size_t sz) const noexcept
    {
        std::free(ptr);
    }
};

#endif