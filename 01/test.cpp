#include <cassert>
#include <functional>
#include "allocator.h"

void
allctr_with_size_0_alloc_0_test()
{
    Allocator a;
    a.make_allocator(0);
    char *mem_ptr = a.alloc(0);
    assert(mem_ptr == nullptr);
}

void
allctr_with_size_0_alloc_1_test()
{
    Allocator a;
    a.make_allocator(0);
    char *mem_ptr = a.alloc(1);
    assert(mem_ptr == nullptr);
}

void
allctr_with_size_1_alloc_0_test()
{
    Allocator a;
    a.make_allocator(1);
    char *mem_ptr = a.alloc(0);
    assert(mem_ptr != nullptr);
}

void
allctr_with_size_1_alloc_1_test()
{
    Allocator a;
    a.make_allocator(1);
    char *mem_ptr = a.alloc(1);
    assert(mem_ptr != nullptr);
}

void
allctr_with_size_1_alloc_2_test()
{
    Allocator a;
    a.make_allocator(1);
    char *mem_ptr = a.alloc(2);
    assert(mem_ptr == nullptr);
}

void
allctr_with_size_16_alloc_3_and_7_and_6_test()
{
    Allocator a;
    a.make_allocator(16);
    char *mem_ptr = a.alloc(3);
    mem_ptr = a.alloc(7);
    mem_ptr = a.alloc(6);
    assert(mem_ptr != nullptr);
}

void
allctr_with_size_16_alloc_3_and_14_test()
{
    Allocator a;
    a.make_allocator(16);
    char *mem_ptr = a.alloc(3);
    mem_ptr = a.alloc(14);
    assert(mem_ptr == nullptr);
}

void
allctr_with_size_inf_alloc_1_test()
{
    Allocator a;
    a.make_allocator(-1);
    char *mem_ptr = a.alloc(1);
    assert(mem_ptr == nullptr);
}

void
allctr_reset_test()
{
    Allocator a;
    a.make_allocator(16);
    char *mem_ptr = a.alloc(15);
    a.reset();
    mem_ptr = a.alloc(15);
    assert(mem_ptr != nullptr);
}

void
allctr_double_make_allctr_with_smaller_size_test()
{
    Allocator a;
    a.make_allocator(16);
    a.make_allocator(10);
    char *mem_ptr = a.alloc(15);
    assert(mem_ptr == nullptr);
}

void
allctr_double_make_allctr_with_bigger_size_test()
{
    Allocator a;
    a.make_allocator(16);
    a.make_allocator(20);
    char *mem_ptr = a.alloc(18);
    assert(mem_ptr != nullptr);
}

std::function<void()> tests[] = { 
        allctr_with_size_0_alloc_0_test, 
        allctr_with_size_0_alloc_1_test, 
        allctr_with_size_1_alloc_0_test,
        allctr_with_size_1_alloc_1_test,
        allctr_with_size_1_alloc_2_test,
        allctr_with_size_16_alloc_3_and_7_and_6_test,
        allctr_with_size_16_alloc_3_and_14_test,
        allctr_with_size_inf_alloc_1_test,
        allctr_reset_test,
        allctr_double_make_allctr_with_smaller_size_test,
        allctr_double_make_allctr_with_bigger_size_test
    };

int
main()
{
    for (auto &test : tests) {
        test();
    }

    std::cout << "All tests passed successfully." << std::endl;
    
    return 0;
}