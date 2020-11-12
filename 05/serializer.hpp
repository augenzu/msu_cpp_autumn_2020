#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "error.hpp"
#include <iostream>
#include <ostream>

class Serializer
{
private:
    static constexpr char _sep{' '};
    std::ostream &_out/*{std::cout}*/;

    template<class T> Error 
    process(T);
    // template<> Error 
    // process<bool>(bool);
    // template<> Error 
    // process<uint64_t>(uint64_t);
    template<class T, class ...Args> Error 
    process(T, Args...);
    // template<class ...Args> Error 
    // process(Args...);

public:
    Serializer(const Serializer &) = delete;
    Serializer(Serializer &&) = delete;
    explicit Serializer(std::ostream & = std::cout);
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