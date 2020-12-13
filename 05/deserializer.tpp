#ifndef DESERIALIZER_T
#define DESERIALIZER_T

#include <type_traits>

template<class T> Error 
Deserializer::load(T &object)
{
    return object.deserialize(*this);
}

template<class ...Args> Error 
Deserializer::operator()(Args &...args)
{
    return process(args...);
}

template<class T, class ...Args> Error 
Deserializer::process(T &arg, Args &...args)
{
    static_assert((std::is_same_v<T, uint64_t> || std::is_same_v<T, bool>), 
            "Deserializer only accepts uint64_t and bool parameters.");

    if (std::is_same_v<T, uint64_t>) {
        std::string strval;
        _in >> strval;
        try {
            arg = stoull(strval);
        } catch (const std::exception &) {
            return Error::CorruptedArchive;
        }
    } else if (std::is_same_v<T, bool>) {
        std::string strval;
        _in >> strval;
        if (strval == "true") {
            arg = true;
        } else if (strval == "false") {
            arg = false;
        } else {
            return Error::CorruptedArchive;
        }
    }

    return process(args...);
}

template<class ...Args> Error 
Deserializer::process()
{
    return Error::NoError;
}

#endif