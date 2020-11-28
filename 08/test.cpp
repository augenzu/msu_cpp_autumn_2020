#include "thrpool.hpp"
#include <cassert>
#include <vector>

struct A {};

void foo(const A&) {}

void
simple_create_test()
{
    ThreadPool pool(8);

    auto task1 = pool.exec(foo, A());
    task1.get();

    int chg = 1;
    auto task2 = pool.exec([](int chg) { chg = 3; return 42; }, chg);
    std::cout << "task2.get(): " << task2.get() << std::endl;
    std::cout << "chg: " << chg << std::endl;
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