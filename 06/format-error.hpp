#ifndef FORMAT_ERROR_HPP
#define FORMAT_ERROR_HPP

#include <stdexcept>

class FormatError : public std::runtime_error
{
public:
    FormatError(const std::string &what_arg)
    : std::runtime_error(what_arg)
    {
    }
    FormatError(const char *what_arg)
    : std::runtime_error(what_arg)
    {
    }
    ~FormatError() = default;
};

#endif