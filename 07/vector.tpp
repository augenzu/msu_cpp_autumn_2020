#ifndef VECTOR_TPP
#define VECTOR_TPP

#include "allocator.hpp"
#include <cassert>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <iterator>
#include <utility>

template<class T, class Allocator>
Vector<T, Allocator>::Vector() = default;

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t sz)
: alloc_{}, data_{alloc_.allocate(sz)}, capacity_{sz}, size_{sz}
{
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_t sz, const value_type &value)
: alloc_{}, data_{alloc_.allocate(sz)}, capacity_{sz}, size_{sz}
{
    for (size_t i = 0; i < sz; ++i) {
        alloc_.construct(&data_[i], value);
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> init)
: alloc_{}, data_{alloc_.allocate(init.size())}, 
    capacity_{init.size()}, size_{init.size()}
{
    auto it = init.begin();
    for (size_t i = 0; i < init.size(); ++i) {
        alloc_.construct(&data_[i], *it++);
    }
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector()
{
    for (size_t i = 0; i < size_; ++i) {
        alloc_.destroy(&data_[i]);
    }
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
    }
    alloc_.construct(&data_[size_++], value);
}

template<class T, class Allocator>
void
Vector<T, Allocator>::push_back(T &&value)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ << 1 : 1);
    }
    alloc_.construct(&data_[size_++], std::move(value));
}

template<class T, class Allocator>
void
Vector<T, Allocator>::pop_back() noexcept
{
    if (size_ == 0) {
        return;
    }
    alloc_.destroy(&data_[size_--]);
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
    for (size_t i = 0; i < size_; ++i) {
        alloc_.destroy(&data_[i]);
    }
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
Vector<T, Allocator>::emplace_back(Args &&...args)
{
    if (size_ == capacity_) {
        reserve(capacity_ ? capacity_ << 1 : 1);
    }
    auto new_elm = alloc_.construct(&data_[size_++], std::forward<Args>(args)...);
    return std::ref(*new_elm);
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
            alloc_.construct(&data_[i], value);
        }
    } else {
        for (size_t i = new_size; i < size_; ++i) {
            alloc_.destroy(&data_[i]);
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
        alloc_.construct(&new_data[i], std::move(data_[i]));
    }
    for (size_t i = 0; i < size_; ++i) {
        alloc_.destroy(&data_[i]);
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