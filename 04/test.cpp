#include "test.h"
#include <iostream>

void
simple_create_test()
{
    Bigint b;
}

void
ostream_operator_test()
{
    Bigint b1{ 42 };
    Bigint b2{ "1234567891234567891234567891234" };
    Bigint b3{ -1 };
    Bigint b4{ "-8800555353588005553535" };

    std::stringstream ss;

    ss << b1;
    assert(ss.str() == "42");

    ss.str("");
    ss << b2;
    assert(ss.str() == "1234567891234567891234567891234");

    ss.str("");
    ss << b3;
    assert(ss.str() == "-1");

    ss.str("");
    ss << b4;
    assert(ss.str() == "-8800555353588005553535");
}

void
copy_constructor_test()
{
    Bigint b1{ "4321432143214321432143214321432143214321"};
    Bigint b2{ b1 };
    assert (b1 == b2);
}
void
move_constructor_test();


const std::vector<std::function<void()>> tests{
    simple_create_test,
    ostream_operator_test
};


void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}
