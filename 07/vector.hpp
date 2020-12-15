#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "allocator.hpp"
#include <cassert>
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

template<class T, class Allocator>
Vector<T, Allocator>::Vector() = default;

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t sz)
: alloc_{}, data_{alloc_.allocate(sz)}, capacity_{sz}, size_{sz}
{
    for (size_t i = 0; i < sz; ++i) {
        data_[i] = value_type{};
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t sz, const value_type &value)
: alloc_{}, data_{alloc_.allocate(sz)}, capacity_{sz}, size_{sz}
{
    for (size_t i = 0; i < sz; ++i) {
        data_[i] = value;
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> init)
: alloc_{}, data_{alloc_.allocate(init.size())}, 
    capacity_{init.size()}, size_{init.size()}
{
    auto it = init.begin();
    for (size_t i = 0; i < init.size(); ++i) {
        data_[i] = *it++;
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector()
{
    alloc_.deallocate(data_, capacity_);
    data_ = nullptr;
    capacity_ = 0;
    size_ = 0;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::value_type &
Vector<T, Allocator>::operator[](size_t idx)
{
    assert(idx < size_);
    return data_[idx];
}

template<class T, class Allocator>
const typename Vector<T, Allocator>::value_type &
Vector<T, Allocator>::operator[](size_t idx) const
{
    assert(idx < size_);
    return data_[idx];
}

template<class T, class Allocator>
void
Vector<T, Allocator>::push_back(const T &value)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ << 1 : 1);
        if (capacity_ == 0) {
            capacity_ = 1;
        }
        capacity_ <<= 1;
    }
    data_[size_++] = value;
}

template<class T, class Allocator>
void
Vector<T, Allocator>::pop_back() noexcept
{
    if (size_ == 0) {
        return;
    }
    --size_;
}

template<class T, class Allocator>
bool
Vector<T, Allocator>::empty() const noexcept
{
    return (size_ == 0);
}

template<class T, class Allocator>
size_t
Vector<T, Allocator>::size() const noexcept
{
    return size_;
}

template<class T, class Allocator>
void
Vector<T, Allocator>::clear() noexcept
{
    size_ = 0;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::begin() noexcept
{
    return data_;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator
Vector<T, Allocator>::end() noexcept
{
    return data_ + size_;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rbegin() noexcept
{
    return std::make_reverse_iterator(end());
}

template<class T, class Allocator>
typename Vector<T, Allocator>::reverse_iterator
Vector<T, Allocator>::rend() noexcept
{
    return std::make_reverse_iterator(begin());
}



template<class T, class Allocator>
template<class ...Args>
typename Vector<T, Allocator>::value_type &
Vector<T, Allocator>::emplace_back(Args ...args)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ << 1 : 1);
        if (capacity_ == 0) {
            capacity_ = 1;
        }
        capacity_ <<= 1;
    }
    value_type *ptr = data_[size_ + 1];
    value_type *new_obj = new (ptr) value_type(std::forward<Args>(args)...);
    ++size_;
    return *new_obj;
}



template<class T, class Allocator>
void
Vector<T, Allocator>::resize(size_t new_size, const value_type &value)
{
    if (new_size > size_) {
        if (new_size > capacity_) {
            reserve(new_size);
        }
        for (size_t i = size_; i < new_size; ++i) {
            data_[i] = value;
        }
    }
    size_ = new_size;
}

template<class T, class Allocator>
void
Vector<T, Allocator>::reserve(size_t new_cap)
{
    if (new_cap <= capacity_) {
        return;
    }
    auto new_data = alloc_.allocate(new_cap);
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    alloc_.deallocate(data_, capacity_);
    data_ = new_data;
    capacity_ = new_cap;
}

template<class T, class Allocator>
size_t
Vector<T, Allocator>::capacity() const noexcept
{
    return capacity_;
}

#endif