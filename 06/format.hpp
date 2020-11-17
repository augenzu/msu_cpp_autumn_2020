#ifndef FORMAT_HPP
#define FORMAT_HPP

#include <iostream>

template<class... Args> std::string 
format(const std::string &, const Args &...);

#include "format.tpp"

#endif