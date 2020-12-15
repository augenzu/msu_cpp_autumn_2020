#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "allocator.hpp"
#include <initializer_list>
#include <iostream>
#include <iterator>

template<class T, class Allocator = Allocator<T>>
class Vector
{
public:
    using value_type = T;
    using iterator = T *;
    using reverse_iterator = std::reverse_iterator<iterator>;

private:
    Allocator alloc_{};
    value_type *data_{nullptr};
    size_t capacity_{};
    size_t size_{};

public:
    Vector();
    explicit Vector(size_t);
    Vector(size_t, const value_type &);
    Vector(std::initializer_list<value_type>);
    ~Vector();

    value_type &
    operator[](size_t);
    const value_type &
    operator[](size_t) const;
    void
    push_back(const value_type &);
    void
    pop_back() noexcept;
    bool
    empty() const noexcept;
    size_t
    size() const noexcept;
    void
    clear() noexcept;
    iterator

    begin() noexcept;
    iterator
    end() noexcept;
    reverse_iterator
    rbegin() noexcept;
    reverse_iterator
    rend() noexcept;

    template<class ...Args>
    value_type &
    emplace_back(Args ...args);

    void 
    resize(size_t, const value_type & = value_type{});
    void 
    reserve(size_t);
    size_t
    capacity() const noexcept;
};

#include "vector.tpp"

#endif