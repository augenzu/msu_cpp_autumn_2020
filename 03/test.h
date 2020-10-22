#ifndef TEST_H
#define TEST_H

#include <functional>
#include <vector>

extern std::vector<std::function<void()>> tests;

void
simple_create_test();
void
right_const_indexing_test();
void
right_assign_indexing_test();

void
testing();

#endif