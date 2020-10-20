#include <cassert>
#include <functional>
#include "parser.h"

int
main()
{
    TokenParser tp;
    std::string input = "  asd 1    32er";

    tp.parse(input);

    return 0;
}