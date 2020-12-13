#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "error.hpp"
#include <iostream>
#include <ostream>

class Serializer
{
private:
    static constexpr char _sep{ ' ' };
    std::ostream &_out{ std::cout };

    template<class T, class ...Args> Error 
    process(T, Args...);
    template<class ...Args> Error 
    process();

public:
    Serializer(const Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    explicit Serializer(std::ostream &out = std::cout) 
    : _out(out)
    {
    }
    Serializer &
    operator=(const Serializer &) = delete;
    Serializer &
    operator=(Serializer &&) = delete;
    ~Serializer() = default;

    template<class T> Error 
    save(const T &);
    template<class ...Args> Error 
    operator()(Args...);
};

#include "serializer.tpp"

#endif