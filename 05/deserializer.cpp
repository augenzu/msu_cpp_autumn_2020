// #ifndef DESERIALIZER_CPP
// #define DESERIALIZER_CPP

#include "deserializer.hpp"

Deserializer::Deserializer(std::istream &in)
: _in(in)
{
}

template<> Error 
Deserializer::process<bool>(bool &arg)
{
    std::string strval;

    _in >> strval;
    if (strval == "true") {
        arg = true;
    } else if (strval == "false") {
        arg = false;
    } else {
        return Error::CorruptedArchive;
    }
    
    return Error::NoError;
}

template<> Error 
Deserializer::process<uint64_t>(uint64_t &arg)
{
    std::string strval;

    _in >> strval;
    try {
        arg = stoull(strval);
    } catch (const std::exception &) {
        return Error::CorruptedArchive;
    }

    return Error::NoError;
}

// #endif