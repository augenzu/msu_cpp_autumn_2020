#ifndef TO_STRINGS_HPP
#define TO_STRINGS_HPP

#include <iostream>
#include <vector>

template<class Arg, class... Args> std::vector<std::string>
to_strings_reversed(const Arg &, const Args &...);

template<class... Args> std::vector<std::string>
to_strings(const Args &...);

template<class... Args> std::vector<std::string>
to_strings_reversed();

#include "to-strings.tpp"

#endif