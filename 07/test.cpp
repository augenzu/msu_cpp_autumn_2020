#include "test.hpp"
#include "vector.hpp"
#include <cassert>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <vector>

void
simple_create_test()
{
    Vector<int> v;
}

void
const_indexing_test()
{
    const Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    int i = v[2];
    assert (i == 2);
}

void
assign_indexing_test()
{
    std::string init{"some-string"};
    Vector<std::string> v{11, init};
    init = "stuff";
    assert(v[3] == "some-string");
    v[3] = "another-string";
    assert(v[3] == "another-string");
}

void
push_back_test()
{
    std::vector<int> init{0, 1, 2, 3};
    Vector<std::vector<int>> v{11, init};

    auto zero = init;
    init[0] = 100;
    v.push_back(init);

    auto hundred = init;
    init[0] = 200;

    assert(v.size() == 12);
    assert(v[0] == zero);
    assert(v[11] == hundred);
}

void
pop_back_test()
{
    Vector<std::string> v{"one", "two", "three"};
    v.pop_back();
    assert(v.size() == 2);
    assert(v[0] == "one");
    assert(v[1] == "two");
}

void
clear_empty_test()
{
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    v.clear();
    assert(v.empty());
    v.clear();
    assert(v.size() == 0);
    assert(v.capacity() != 0);
}

const std::vector<std::function<void()>> tests{
    simple_create_test,
    const_indexing_test,
    assign_indexing_test,
    push_back_test,
    pop_back_test,
    clear_empty_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}