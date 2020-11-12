#include "test.hpp"
#include <iostream>
#include <sstream>

void
simple_create_test()
{
    Serializer s{std::cout};
    Deserializer d{std::cin};
}

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template<class Serializer> Error 
    serialize(Serializer &serializer) const
    {
        return serializer(a, b, c);
    }

    template<class Deserializer> Error 
    deserialize(Deserializer &deserializer)
    {
        return deserializer(a, b, c);
    }
};

void
right_data_test()
{
    Data x{ 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(x);

    Data y{ 0, false, 0 };

    Deserializer deserializer(stream);
    const Error err = deserializer.load(y);

    assert(err == Error::NoError);

    assert(x.a == y.a);
    assert(x.b == y.b);
    assert(x.c == y.c);
}

const std::vector<std::function<void()>> tests{
    simple_create_test,
    right_data_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}