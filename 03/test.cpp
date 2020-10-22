#include "matrix.h"
#include "test.h"
#include <iostream>

void
simple_create_test()
{
    Matrix m;
}

void
right_const_indexing_test()
{
    Matrix m(2, 3);
    int i = m[0][0];
    assert(i == m[0][0]);
}

void
right_assign_indexing_test()
{
    Matrix m(2, 3);
    m[1][2] = 1;
    assert(m[1][2] == 1);
}

std::vector<std::function<void()>> tests{
    simple_create_test,
    right_const_indexing_test,
    right_assign_indexing_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}