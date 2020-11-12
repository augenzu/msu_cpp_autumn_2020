#include "test.hpp"
#include <iostream>

void
simple_create_test()
{
    Serializer s{std::cout};
    Deserializer d{std::cin};
}

const std::vector<std::function<void()>> tests{
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