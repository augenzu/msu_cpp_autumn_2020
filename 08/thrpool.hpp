#ifndef THRPOOL_HPP
#define THRPOOL_HPP

#include <condition_variable>
#include <iostream>
#include <functional>
#include <future>
#include <mutex>
#include <stdexcept>
#include <thread>
#include <queue>
#include <vector>

class ThreadPool
{
private:
    size_t pool_sz_;
    std::vector<std::thread> thrs_{};
    std::mutex mtx_{};
    std::queue<std::function<void()>> tasks_{};
    std::condition_variable condvar_{};
    bool end_flag_{false};

    void
    executor()
    {
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock lock{mtx_};
                condvar_.wait(lock, [this]()
                { 
                    return end_flag_ || !tasks_.empty(); 
                });
                if (end_flag_ && tasks_.empty()) {
                    return;
                }
                task = std::move(tasks_.front());
                tasks_.pop();
            }

            task();
        }
    }

public:
    explicit ThreadPool(size_t);
    ~ThreadPool();

    template <class Func, class ...Args>
    auto 
    exec(Func func, Args ...args) -> std::future<decltype(func(args...))>;
};

template <class Func, class ...Args>
auto 
ThreadPool::exec(Func func, Args ...args) -> std::future<decltype(func(args...))>
{    
    using ret_t = std::result_of_t<Func(Args...)>;
    
    auto task = std::make_shared<std::packaged_task<ret_t()>>(
            std::bind(std::forward<Func>(func), std::forward<Args>(args)...));
    std::future<ret_t> future = task->get_future();

    {
        std::unique_lock lock{mtx_};
        if (end_flag_) {
            throw std::runtime_error("Adding task while task queue is destroing.");
        }
        tasks_.emplace([task]()
        {
            (*task)(); 
        });
    }

    condvar_.notify_one();
    return future;
}

#endif