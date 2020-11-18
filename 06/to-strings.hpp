#ifndef TO_STRINGS_HPP
#define TO_STRINGS_HPP

#include <iostream>
#include <vector>

template<class... Args> void
to_strings_inner(std::vector<std::string> &);

template<class Arg, class... Args> void
to_strings_inner(std::vector<std::string> &, const Arg &, const Args &...);

template<class... Args> std::vector<std::string>
to_strings(const Args &...);

#include "to-strings.tpp"

#endif