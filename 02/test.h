#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <functional>
#include <cstdint>
#include <iostream>
#include <vector>
#include "parser.h"

// struct for possible results of test callback functions
struct Output
{
    std::vector<int> start_v{};
    std::vector<int> end_v{};
    std::vector<uint64_t> num_v{};
    std::vector<std::string> str_v{};
};

// parsing strings (inputs) and their corresponding results (outputs)
struct InOut
{
    std::string input{};
    Output output{};
};

extern std::vector<InOut> test_in_outs;

// perform testing
void
testing();

#endif