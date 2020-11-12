#ifndef SERIALIZER_T
#define SERIALIZER_T

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

template<class T> Error 
Serializer::process(T arg)
{
}

template<class T, class ...Args> Error 
Serializer::process(T arg, Args... args)
{
    auto err = process(arg);
    if (err != Error::NoError) {
        return err;
    }
    _out << _sep;
    return process(args...);
}

#endif