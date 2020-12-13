#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "error.hpp"
#include <iostream>
#include <istream>

class Deserializer
{
private:
    static constexpr char _sep{ ' ' };
    std::istream &_in{ std::cin };

    template<class T, class ...Args> Error 
    process(T &, Args &...);
    template<class ...Args> Error 
    process();

public:
    Deserializer(const Deserializer &) = delete;
    Deserializer(Deserializer &&) = delete;
    Deserializer(std::istream &in = std::cin)
    : _in(in)
    {
    }
    Deserializer &
    operator=(const Deserializer &) = delete;
    Deserializer &
    operator=(Deserializer &&) = delete;
    ~Deserializer() = default;

    template<class T> Error 
    load(T &);
    template<class ...Args> Error 
    operator()(Args &...);
};

#include "deserializer.tpp"

#endif