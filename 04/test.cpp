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
equal_compare_test()
{
    Bigint b1{"42"}, b2{"42"};
    assert(b1 == b2);
    Bigint b3{"98936913561937591991369175"}, b4{"-98936913561937591991369175"};
    assert(b3 != b4);
    Bigint b5{"111111111111111111"}, b6{"111111"};
    assert(b5 != b6);
    Bigint b7{"0"}, b8{"-0"};
    assert(b7 == b8);
    Bigint b9{"000000000000000000000000000000000000000000000000000000000000000000001"}, b10{"1"};
    assert(b9 == b10);
    Bigint b11{"0123456789123456789"}, b12{"123456789123456789"};
    assert(b11 == b12);
}

void
less_comapare_test()
{
    Bigint b1{"123123123123123123"}, b2{"456456456456456456"};
    assert(b1 < b2);
    Bigint b3{"999"}, b4{"111111111111111"};
    assert(b3 < b4);
    Bigint b5{"-11111111"}, b6{"111"};
    assert(b5 < b6);
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
    ostream_operator_test,
    equal_compare_test,
    less_comapare_test
};


void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}
