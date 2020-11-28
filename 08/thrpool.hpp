#ifndef THRPOOL_HPP
#define THRPOOL_HPP

#include <iostream>
#include <functional>
#include <future>
#include <mutex>
#include <thread>

class ThreadPool
{
private:
    size_t pool_sz_;
    size_t running_{};
    std::mutex mtx_{};

public:
    explicit ThreadPool(size_t);

    template <class Func, class ...Args>
    auto 
    exec(Func func, Args ...args) -> std::future<decltype(func(args...))>;
};

#include "thrpool.tpp"

#endif