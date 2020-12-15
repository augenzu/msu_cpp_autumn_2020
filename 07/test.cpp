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
    Vector<int> vi;
    Vector<std::string> vs{ 3, "str" };
    Vector<double> vd{ 0.1, 0.2, 0.3, 0.4 };
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
push_back_to_empty()
{
    Vector<int> v;
    v.push_back(0);
    assert(v.size() == 1);
    assert(v[0] == 0);
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

void
begin_end_test()
{
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        assert(*it == i++);
    }
}

void
begin_end_empty_test()
{
    Vector<int> v;
    int i = 0;
    for (auto it = v.begin(); it != v.end(); ++it) {
        assert(0 == 1);
    }
}

void
rbegin_rend_test()
{
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};
    int i = 7;
    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        assert(*it == i--);
    }
}

void
reserve_test()
{
    Vector<double> v = Vector<double>(11);

    v.reserve(0);
    assert(v.capacity() == 11);
    assert(v.size() == 11);

    v.reserve(111);
    assert(v.capacity() == 111);
    assert(v.size() == 11);
    for (auto it = v.begin(); it != v.end(); ++it) {
        assert(*it == 0.0);
    }
}

void
reserve_empty_test()
{
    Vector<int> v;
    v.reserve(16);
    assert(v.capacity() == 16);
    v.push_back(42);
    assert(v.size() == 1);
    assert(v[0] == 42);
}

void
resize_test()
{
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};

    v.resize(11);
    assert(v.size() == 11);
    v[8] = 8;
    v[9] = 9;
    for (size_t i = 0; i < 9; ++i) {
        assert(v[i] == i);
    }

    v.resize(4);
    assert(v.size() == 4);
}

void
emplace_back_pod_test()
{
    Vector<int> v{0, 1, 2, 3, 4, 5, 6, 7};

    int &new_elm = v.emplace_back(42);

    assert(new_elm == 42);
    assert(v.size() == 9);
    assert(v[8] == 42);

    new_elm = 100500;
    assert(v[8] == 100500);
}

void
emplace_back_non_pod_test()
{
    Vector<std::vector<std::string>> v{ { "1", "2" }, { "3" } };

    assert(v.size() == 2);

    std::vector<std::string> &new_elm = v.emplace_back(std::vector<std::string>{ "4", "5", "6", "7" });

    assert(new_elm == (std::vector<std::string>{ "4", "5", "6", "7" }));
    assert(v.size() == 3);
    assert(v[2] == (std::vector<std::string>{ "4", "5", "6", "7" }));

    new_elm[2] = "42";

    assert(new_elm == (std::vector<std::string>{ "4", "5", "42", "7" }));
    assert(v[2] == (std::vector<std::string>{ "4", "5", "42", "7" }));
}

void
emplace_back_to_empty()
{
    Vector<double> v;

    auto new_elm = v.emplace_back(3.14);

    assert(new_elm == 3.14);
    assert(v.size() == 1);
    assert(v[0] == 3.14);
}

const std::vector<std::function<void()>> tests{
    simple_create_test,
    const_indexing_test,
    assign_indexing_test,
    push_back_test,
    push_back_to_empty,
    pop_back_test,
    clear_empty_test,
    begin_end_test,
    begin_end_empty_test,
    rbegin_rend_test,
    reserve_test,
    reserve_empty_test,
    resize_test,
    emplace_back_pod_test,
    emplace_back_non_pod_test,
    emplace_back_to_empty
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}