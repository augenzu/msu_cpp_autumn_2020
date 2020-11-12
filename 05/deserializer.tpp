#ifndef DESERIALIZER_T
#define DESERIALIZER_T

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

template<class T> Error 
Deserializer::process(T &arg)
{
}

template<class T, class ...Args> Error 
Deserializer::process(T &arg, Args &...args)
{
    auto err = process(arg);
    if (err != Error::NoError) {
        return err;
    }

    return process(args...);
}

#endif