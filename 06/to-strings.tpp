#ifndef TO_STRINGS_TPP
#define TO_STRINGS_TPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template<class... Args> std::vector<std::string>
to_strings_reversed()
{
    return std::vector<std::string>{};
}

template<class Arg, class... Args> std::vector<std::string>
to_strings_reversed(const Arg &arg, const Args &... args)
{
    std::stringstream stream;
    stream << arg;
    std::string str_arg = stream.str();

    std::vector<std::string> rev_str_args = to_strings_reversed(args...);
    rev_str_args.push_back(str_arg);

    return rev_str_args;
}

template<class... Args> std::vector<std::string>
to_strings(const Args &... args)
{
    std::vector<std::string> rev_str_args = to_strings_reversed(args...);
    std::reverse(rev_str_args.begin(), rev_str_args.end());
    return rev_str_args;
}

#endif