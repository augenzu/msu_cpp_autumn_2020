#include "test.h"
#include <iostream>

void
simple_create_test()
{
    return;
}

std::vector<std::function<void()>> tests{
    simple_create_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}