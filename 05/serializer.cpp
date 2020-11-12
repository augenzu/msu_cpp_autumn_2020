// #ifndef SERIALIZER_CPP
// #define SERIALIZER_CPP

#include "serializer.hpp"

Serializer::Serializer(std::ostream &out) 
: _out(out)
{
}

template<> Error 
Serializer::process<bool>(bool arg)
{
    if (arg) {
        _out << "true";
    } else {
        _out << "false";
    }
    return Error::NoError;
}

template<> Error 
Serializer::process<uint64_t>(uint64_t arg)
{
    _out << arg;
    return Error::NoError;
}

// #endif