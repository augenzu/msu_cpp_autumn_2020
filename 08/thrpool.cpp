#include "thrpool.hpp"

ThreadPool::ThreadPool(size_t pool_sz)
: pool_sz_(pool_sz), end_flag_{false}
{        
    for (size_t i = 0; i < pool_sz_; ++i) {
        thrs_.emplace_back([this] 
        {
            executor(); 
        });
    }
}

ThreadPool::~ThreadPool()
{       
    {
        std::unique_lock lock{mtx_};
        end_flag_ = true;
    }
    condvar_.notify_all();
    for (auto &thr: thrs_) {
        thr.join();
    }
}