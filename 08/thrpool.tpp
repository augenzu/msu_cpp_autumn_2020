#include "thrpool.hpp"

template <class Func, class ...Args>
auto 
ThreadPool::exec(Func func, Args ...args) -> std::future<decltype(func(args...))>
{
    auto wrapper = [=](std::promise<decltype(func(args...))> &promise_)
            {
                promise_.set_value(func(args...));
            };

    std::promise<decltype(func(args...))> promise_;
    std::future<decltype(func(args...))> future_{promise_.get_future()};
    
    while (true) {
        if (running_ < pool_sz_) {
            std::lock_guard lock{mtx_};
            if (running_ == pool_sz_) {
                continue;
            }
            ++running_;
            break;
        }
    }

    std::thread thr(wrapper, std::ref(promise_));
    thr.join();
    {
        std::lock_guard lock{mtx_};
        --running_;
    }

    return future_;
}