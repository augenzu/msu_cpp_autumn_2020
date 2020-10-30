#ifndef TEST_H
#define TEST_H

#include "bigint.h"
#include <cassert>
#include <functional>
#include <sstream>
#include <vector>

extern const std::vector<std::function<void()>> tests;

void
simple_create_test();
void
ostream_operator_test();
void
copy_constructor_test();
void
move_constructor_test();

// perform testing
void
testing();

#endif
