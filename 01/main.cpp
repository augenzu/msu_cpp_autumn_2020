#include <ctime>
#include <iomanip>
#include "allocator.h"

enum { ITERATIONS_CNT = 10000000 };
enum { ALLOC_SZ = 16 };
enum { MSG_WIDTH = 60 };
enum { SEC_NUM_WIDTH = 10 };
enum { SEC_NUM_PRECISION = 6 };

void
malloc_speed_test()
{
    clock_t start = clock();

    for (int i = 0; i < ITERATIONS_CNT; ++i) {
        char *mem_ptr = static_cast<char *>(malloc(ALLOC_SZ));
        free(mem_ptr);
    }

    clock_t end = clock();
    double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << std::left << std::setw(MSG_WIDTH) << "malloc & free functions took"
            << std::left << std::setw(SEC_NUM_WIDTH) << std::setprecision(SEC_NUM_PRECISION) << seconds 
            << " seconds for " << ITERATIONS_CNT << " iterations" << std::endl;
}

void
new_speed_test()
{
    clock_t start = clock();

    for (int i = 0; i < ITERATIONS_CNT; ++i) {
        char *mem_ptr = new char[ALLOC_SZ];
        delete[] mem_ptr;
    }

    clock_t end = clock();
    double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << std::left << std::setw(MSG_WIDTH) << "new[] & delete[] operators took" 
            << std::left << std::setw(SEC_NUM_WIDTH) << std::setprecision(SEC_NUM_PRECISION) << seconds 
            << " seconds for " << ITERATIONS_CNT << " iterations" << std::endl;
}

void
allocator_speed_test()
{
    Allocator a;
    a.make_allocator(ALLOC_SZ);
    
    clock_t start = clock();

    for (int i = 0; i < ITERATIONS_CNT; ++i) {
        a.alloc(ALLOC_SZ);
        a.reset();
    }

    clock_t end = clock();
    double seconds = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << std::left << std::setw(MSG_WIDTH) << "Allocator::alloc() & Allocator::reset() methods took " 
            << std::left << std::setw(SEC_NUM_WIDTH) << std::setprecision(SEC_NUM_PRECISION) << seconds 
            << " seconds for " << ITERATIONS_CNT << " iterations" << std::endl;
}

int
main()
{
    std::cout << "Running speed tests..." << std::endl;
    
    malloc_speed_test();
    new_speed_test();
    allocator_speed_test();

    return 0;
}