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
    Bigint b1{ "42" }, b2{ "42" };
    assert(b1 == b2);
    Bigint b3{ "98936913561937591991369175" }, b4{ "-98936913561937591991369175" };
    assert(b3 != b4);
    Bigint b5{ "111111111111111111" }, b6{ "111111" };
    assert(b5 != b6);
    Bigint b7{ "0" }, b8{ "-0" };
    assert(b7 == b8);
    Bigint b9{ "000000000000000000000000000000000000000000000000000000000000000000001" }, b10{ "1" };
    assert(b9 == b10);
    Bigint b11{ "0123456789123456789" }, b12{ "123456789123456789" };
    assert(b11 == b12);
    Bigint b13{ "00042" }, b14{ 42 };
    assert(b13 == b14);
}

void
less_comapare_test()
{
    Bigint b1{ "123123123123123123" }, b2{ "456456456456456456" };
    assert(b1 < b2);
    Bigint b3{ 999 }, b4{ "111111111111111" };
    assert(b3 < b4);
    Bigint b5{ "-11111111" }, b6{ 111 };
    assert(b5 < b6);
    Bigint b7{ 42 };
    assert(b7 < 43);
}

void
copy_constructor_test()
{
    Bigint b{ "4321432143214321432143214321432143214321" };
    Bigint copy_b{ b };
    assert (copy_b == b);
}

void
move_constructor_test()
{
    Bigint b{ "4321432143214321432143214321432143214321" };
    Bigint copy_b{ b };
    Bigint move_b{ std::move(b) };
    assert(move_b == copy_b);
}

void
assignment_operator_test()
{
    Bigint b1, b2{ "4321432143214321432143214321432143214321" };
    b1 = b2;
    assert(b1 == b2);
    b2 = { 42 };
    assert(b1 != b2);
}

void
multiple_assignment_test()
{
    Bigint b1, b2, b3{ "4321432143214321432143214321432143214321" };
    b1 = b2 = b3;
    assert(b1 == b3);
}

void
self_assignment_test()
{
    Bigint b{ "4321432143214321432143214321432143214321" };
    Bigint copy_b{ b };
    b = b;
    assert(b == copy_b);
}

void
move_test()
{
    Bigint b{ "4321432143214321432143214321432143214321" };
    Bigint copy_b{ b }, move_b;
    move_b = std::move(b);
    assert(move_b == copy_b);
}

void
self_move_test()
{
    Bigint b{ "4321432143214321432143214321432143214321" };
    Bigint copy_b{ b };
    b = std::move(b);
    assert(b == copy_b);
}

void
unsigned_add_assign_test()
{
    Bigint b1{ "4321432143214321432143214321432143214321" };
    b1 += Bigint{ "1" };
    assert(b1 == Bigint{ "4321432143214321432143214321432143214322" });

    Bigint b2{ "4321432143214321432143214321432143214321" };
    b2 += Bigint{ "72935872857925925992875928579" };
    assert(b2 == Bigint{ "4321432143287257305001140247425019142900" });

    Bigint b3{ "4321432143214321432143214321432143214321" };
    b3 += 88005553535;
    assert(b3 == Bigint{ "4321432143214321432143214321520148767856" });

    Bigint b4{ "4321432143214321432143214321432143214321" };
    b4 += 0;
    assert(b4 == Bigint{ "4321432143214321432143214321432143214321" });
}

void
unsigned_sub_assign_test()
{
    Bigint b1{ "4321432143214321432143214321432143214321" };
    b1 -= 1;
    assert(b1 == Bigint{ "4321432143214321432143214321432143214320" });

    Bigint b2{ "4321432143214321432143214321432143214321" };
    b2 -= Bigint{ "72935872857925998696969692756927569225992875928579" };
    assert(b2 == Bigint{ "-72935872853604566553755371324784354904560732714258" });

    Bigint b3{ "4321432143214321432143214321432143214321" };
    b3 -= Bigint{ "4321432143214321432193214321432143214321" };
    assert(b3 == Bigint{ "-50000000000000000000" });

    Bigint b4{ 42 };
    b4 -= 0;
    assert(b4 == 42);
}

void
mul_assign_test()
{
    Bigint b1{ "4321432143214321432143214321432143214321" };
    b1 *= Bigint{ "1" };
    assert(b1 == Bigint{ "4321432143214321432143214321432143214321" });

    Bigint b2{ "4321432143214321432143214321432143214321" };
    b2 *= Bigint{ -1 };
    assert(b2 == Bigint{ "-4321432143214321432143214321432143214321" });

    Bigint b3{ 0 };
    b3 *= Bigint{ "4321432143214321432143214321432143214321" };
    assert(b3 == 0);

    Bigint b4{ "-4321432143214321432143214321432143214321" };
    b4 *= Bigint{ "-4321432143214321432143214321432143214321" };
    assert(b4 == Bigint{ "18674775768405923500640893172225513380417215430713988490558226739765685739491041" });

    Bigint b5{ "74298729892864924629649269662" };
    b5 *= Bigint{ "-876876837583275832758275827582758275827568" };
    assert(b5 == Bigint{ "-65150835304909397528633238675410560575679527042056922663146539845642016" });

    Bigint b6{ 42 };
    b6 *= 911;
    assert(b6 == Bigint{ 38262 });
}

void
arithmetic_operations_test()
{
    Bigint b1{ 42 };
    Bigint b2{ "1234567891234567891234567891234" };
    Bigint b3{ -1 };
    Bigint b4{ "-8800555353588005553535" };

    Bigint a1 = (3 + -b1) * (b2 - b4);
    assert(a1 == Bigint{ "-48148148101369806548080364345991" });

    Bigint a2 = b3 * (4 * -b2 - b3 * 911 * b4 * b2 * b2 - b1);
    assert(a2 == Bigint{ "12219639989694128084259972901838976150575553419742554188727203414663259459617226146038" });

    Bigint a3 = (1 - b1) * (2 - b2) - (3 - b3) * (4 - b4);
    assert(a3 == Bigint{ "50617283505415062126265261326356" });
}


const std::vector<std::function<void()>> tests{
    simple_create_test,
    ostream_operator_test,
    equal_compare_test,
    less_comapare_test,
    copy_constructor_test,
    move_constructor_test,
    assignment_operator_test,
    multiple_assignment_test,
    self_assignment_test,
    move_test,
    self_move_test,
    unsigned_add_assign_test,
    unsigned_sub_assign_test,
    mul_assign_test,
    arithmetic_operations_test
};


void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}
