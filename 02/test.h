#ifndef TEST_H
#define TEST_H

#include <cassert>
#include <functional>
#include <cstdint>
#include <iostream>
#include <vector>
#include "parser.h"

struct InOut
{
    std::string input{};
    std::pair<std::vector<uint64_t>, std::vector<std::string>> output{};
};
extern std::vector<InOut> test_in_outs;

// perform testing
void
testing();

#endif