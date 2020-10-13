// TODO: обернуть в умные указатели
// TODO: конструкторы & оператор присваивания
// TODO: double call of make_allocator - what will happen? (mem leak?!) - FIXED(?)
// TODO: install valgrind - FIXED
// TODO: check for leaks
// TODO: если в make_allocator new[] возвращает nullptr - что делать?  - FIXED

#include "allocator.h"

Allocator::Allocator() = default;

Allocator::~Allocator()
{
    if (allocator_is_created_) {
        delete[] mem_;
    }
    mem_ = nullptr;
}

void 
Allocator::make_allocator(size_t max_size)
{
    offset_ = 0;
    capacity_ = max_size;
    allocator_is_created_ = true;
    
    if (allocator_is_created_) {
        delete[] mem_;
    }

    if (!max_size) {
        mem_ = nullptr;
        allocator_is_created_ = false;
        return;
    }

    try {
        mem_ = new char[max_size];
    } catch(const std::bad_alloc &) {
        // If we are trying to use more memory than it is available
        // allocator will not be created and Allocator::alloc() will always return nullptr
        // Calling this method again with a smaller size can help.
        mem_ = nullptr;
        capacity_ = 0;
        allocator_is_created_ = false;
        return;
    }
}

char *
Allocator::alloc(size_t size)
{
    if (!allocator_is_created_ || offset_ + size > capacity_) {
        // If allocator has not been created yet
        // we can allocate no memory.
        // Also we cannot allocate more memory than allocator has.
        return nullptr;
    }
    char *mem_ptr = mem_ + offset_;
    offset_ += size;
    return mem_ptr;
}

void 
Allocator::reset()
{
    if (!allocator_is_created_) {
        // If allocator has not been created yet 
        // it is pointless to reset it.
        // We should call Allocator::make_allocator() before.
        return;
    }
    offset_ = 0;
}
