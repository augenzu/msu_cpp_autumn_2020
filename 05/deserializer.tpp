#ifndef DESERIALIZER_T
#define DESERIALIZER_T

#include <cctype>
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
        // check whether strval is empty or not
        if (strval.empty()) {
            return Error::CorruptedArchive;
        }
        // check whether strval only contains digits or not
        for (auto it = strval.begin(), end = strval.end(); it != end; ++it) {
            if (!isdigit(*it)) {
                return Error::CorruptedArchive;
            }
        }
        // check for artefacts such as 00000 or 000034
        if (strval[0] == '0' && strval.size() > 1) {
            return Error::CorruptedArchive;
        }
        // check whether strval contains correct uint64_t number or not
        std::string max_strval = std::to_string(std::numeric_limits<uint64_t>::max());
        if (strval.size() > max_strval.size()
                || (strval.size() == max_strval.size() && strval > max_strval)) {
            return Error::CorruptedArchive;
        }
        arg = stoull(strval);
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
    std::string rest;
     _in >> rest;
    // check whether the rest of input is empty or not
    return rest.empty() ? Error::NoError : Error::CorruptedArchive;
}

#endif