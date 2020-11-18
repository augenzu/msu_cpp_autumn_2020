#ifndef TO_STRINGS_TPP
#define TO_STRINGS_TPP

#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

template<class... Args> void
to_strings_inner(std::vector<std::string> &str_args)
{
    return;
}

template<class Arg, class... Args> void
to_strings_inner(std::vector<std::string> &str_args, const Arg &arg, const Args &... args)
{
    std::stringstream stream;
    stream << arg;
    std::string str_arg = stream.str();
    
    str_args.push_back(str_arg);

    to_strings_inner(str_args, args...);
}

template<class... Args> std::vector<std::string>
to_strings(const Args &... args)
{
    std::vector<std::string> str_args;
    to_strings_inner(str_args, args...); 
    return str_args;
}

#endif