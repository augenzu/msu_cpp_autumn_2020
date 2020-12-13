#ifndef SERIALIZER_T
#define SERIALIZER_T

#include <type_traits>

template<class T> Error 
Serializer::save(const T &object)
{
    return object.serialize(*this);
}

template<class... Args> Error 
Serializer::operator()(Args... args)
{
    return process(args...);
}

template<class T, class ...Args> Error 
Serializer::process(T arg, Args... args)
{
    static_assert((std::is_same_v<T, uint64_t> || std::is_same_v<T, bool>), 
            "Serializer only accepts uint64_t and bool parameters.");

    if (std::is_same_v<T, uint64_t>) {
        _out << arg;
    } else if (std::is_same_v<T, bool>) {
        if (arg) {
            _out << "true";
        } else {
            _out << "false";
        }
    }

    _out << _sep;

    return process(args...);
}

template<class ...Args> Error 
Serializer::process()
{
    return Error::NoError;
}

#endif