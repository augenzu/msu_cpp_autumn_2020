#include "thrpool.hpp"
#include <cassert>
#include <functional>
#include <vector>

void
void_result_test()
{
    struct A {};

    ThreadPool pool(8);

    auto task = pool.exec([](const A&){}, A());
    task.get();
}

void
non_void_result_test()
{
    ThreadPool pool(8);

    auto task = pool.exec([]() 
    { 
        return 42; 
    });
    assert(task.get() == 42);
}

void
func_with_args_test()
{
    ThreadPool pool(8);

    int i{0};
    double d{3.14};
    std::string s{"str"};
    std::vector<int> v{0, 1, 2, 3};
    bool b{false};

    auto task = pool.exec([](int i, double d, const std::string &s, 
            const std::vector<int> &v, bool b)
    { 
        if (b) {
            return v[1];
        } else {
            return i + s[0];
        }
    }, i, d, s, v, b);

    assert(task.get() == i + s[0]);
}

void
ntasks_lt_nthreads_test()
{
    ThreadPool pool(8);

    auto duplicate = [](int i)
    {
        return i;
    };

    auto task0 = pool.exec(duplicate, 0);
    auto task1 = pool.exec(duplicate, 1);
    auto task2 = pool.exec(duplicate, 2);
    auto task3 = pool.exec(duplicate, 3);
    auto task4 = pool.exec(duplicate, 4);

    assert(task0.get() == 0);
    assert(task1.get() == 1);
    assert(task2.get() == 2);
    assert(task3.get() == 3);
    assert(task4.get() == 4);
}

void
ntasks_gt_nthreads_test()
{
    ThreadPool pool(2);

    auto duplicate = [](int i)
    {
        return i;
    };

    auto task0 = pool.exec(duplicate, 0);
    auto task1 = pool.exec(duplicate, 1);
    auto task2 = pool.exec(duplicate, 2);
    auto task3 = pool.exec(duplicate, 3);
    auto task4 = pool.exec(duplicate, 4);

    assert(task0.get() == 0);
    assert(task1.get() == 1);
    assert(task2.get() == 2);
    assert(task3.get() == 3);
    assert(task4.get() == 4);
}

const std::vector<std::function<void()>> tests{
    void_result_test,
    non_void_result_test,
    func_with_args_test,
    ntasks_lt_nthreads_test,
    ntasks_gt_nthreads_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}