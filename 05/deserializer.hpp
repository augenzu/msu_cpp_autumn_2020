#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include "error.hpp"
#include <iostream>
#include <istream>

class Deserializer
{
private:
    static constexpr char _sep{' '};
    std::istream &_in/*{std::cin}*/;

    template<class T> Error 
    process(T &);
    // template<> Error 
    // process<bool>(bool &);
    // template<> Error 
    // process<uint64_t>(uint64_t &);
    template<class T, class ...Args> Error 
    process(T &, Args &...);
    // template<class ...Args> Error 
    // process(Args &...);

public:
    Deserializer(const Deserializer &) = delete;
    Deserializer(Deserializer &&) = delete;
    explicit Deserializer(std::istream & = std::cin);
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