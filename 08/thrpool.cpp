#include "thrpool.hpp"

ThreadPool::ThreadPool(size_t pool_sz)
: pool_sz_(pool_sz), running_(0), mtx_()
{
}