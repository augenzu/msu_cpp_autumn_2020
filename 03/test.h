#ifndef TEST_H
#define TEST_H

#include <functional>
#include <vector>

extern std::vector<std::function<void()>> tests;

void
simple_create_test();

void
testing();

#endif