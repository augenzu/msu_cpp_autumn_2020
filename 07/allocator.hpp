#ifndef ALLOCATOR_HPP
#define ALLOCATOR_HPP

#include <iostream>
#include <type_traits>

template<class T>
class Allocator
{
    static_assert(!std::is_same_v<T, void>, "Allocator type must be non-void.");
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

    template<typename U, typename... Args>
    U *
    construct(U *ptr, Args &&...args)
    {
        auto new_obj = new (reinterpret_cast<void *>(ptr)) U{ std::forward<Args>(args)... };
        return new_obj;
    }

    template<typename U>
    void 
    destroy(U *ptr)
    {
        ptr->~U();
    }
};

template <class T, class U>
bool 
operator==(const Allocator<T> &, const Allocator<U> &) 
{ 
    return true;
}

template <class T, class U>
bool 
operator!=(const Allocator<T> &, const Allocator<U> &) 
{ 
    return false;
}

#endif