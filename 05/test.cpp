#include "test.hpp"
#include <iostream>
#include <sstream>
#include <tuple>

#include "serializer.hpp"
#include "deserializer.hpp"
#include <cassert>
#include <functional>
#include <vector>

void
simple_create_test()
{
    Serializer s{ std::cout };
    Deserializer d{ std::cin };
}

struct RightData
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
    RightData input{ 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(input);

    // std::cout << "err: " 
    //         << (err == Error::CorruptedArchive ? "Error::CorruptedArchive" : "Error::NoError")
    //         << std::endl;

    // std::cout << "stream.str(): " << "|" << stream.str() << "|" << std::endl;

    RightData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(output);

    assert(err == Error::NoError);
    
    // std::cout << "err: " 
    //         << (err == Error::CorruptedArchive ? "Error::CorruptedArchive" : "Error::NoError")
    //         << std::endl;

    assert(input.a == output.a);
    assert(input.b == output.b);
    assert(input.c == output.c);
}

struct WrongData
{
    std::string str;

    template<class Serializer> Error 
    serialize(Serializer &serializer) const
    {
        return serializer(str);
    }

    template<class Deserializer> Error 
    deserialize(Deserializer &deserializer)
    {
        return deserializer(str);
    }
};


// This test SHOULD fail so it is never run.
// It is only here to show what happens if we pass something 
// except of uint64_t or bool parameters to Serializer or Deserializer

// void
// wrong_data_test()
// {
//     WrongData input{ "input-data" };

//     std::stringstream stream;

//     Serializer serializer(stream);
//     serializer.save(input);

//     WrongData output{ "output-data" };

//     Deserializer deserializer(stream);
//     const Error err = deserializer.load(output);
// }

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