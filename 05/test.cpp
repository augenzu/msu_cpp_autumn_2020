#include "test.hpp"
#include "deserializer.hpp"
#include "serializer.hpp"
#include <cassert>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

struct ValidData
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
valid_data_test()
{
    ValidData input{ 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(input);
    assert(err == Error::NoError);

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(output);
    assert(err == Error::NoError);

    assert(input.a == output.a);
    assert(input.b == output.b);
    assert(input.c == output.c);
}

void
corrupted_bool_test()
{
    std::stringstream stream;
    stream << "0 fAlSe 0 ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
not_a_number_test()
{
    std::stringstream stream;
    stream << "0 false 123A56 ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
negative_number_test()
{
    std::stringstream stream;
    stream << "-42 false 0 ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
number_starts_with_zero_test()
{
    std::stringstream stream;
    stream << "0 false 01 ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
too_big_number_test()
{
    std::stringstream stream;
    stream << "0 false 11111111111111111111111111111111111111111111111111111 ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

struct OtherValidData
{
    bool b;
    uint64_t a;
    uint64_t c;

    template<class Serializer> Error 
    serialize(Serializer &serializer) const
    {
        return serializer(b, a, c);
    }

    template<class Deserializer> Error 
    deserialize(Deserializer &deserializer)
    {
        return deserializer(b, a, c);
    }
};

void
wrong_parameter_type_test()
{
    ValidData input{ 1, true, 2 };

    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(input);
    assert(err == Error::NoError);

    OtherValidData output{ false, 0, 0 };

    Deserializer deserializer(stream);
    err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
too_few_params_test()
{
    std::stringstream stream;
    stream << "0 false";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

void
too_many_params_test()
{
    std::stringstream stream;
    stream << "0 false 0 0 0 0 0   ";

    ValidData output{ 0, false, 0 };

    Deserializer deserializer(stream);
    Error err = deserializer.load(output);
    assert(err == Error::CorruptedArchive);
}

struct EmptyData
{
    template<class Serializer> Error 
    serialize(Serializer &serializer) const
    {
        return serializer();
    }

    template<class Deserializer> Error 
    deserialize(Deserializer &deserializer)
    {
        return deserializer();
    }
};

void
empty_data_test()
{
    EmptyData input{};

    std::stringstream stream;

    Serializer serializer(stream);
    Error err = serializer.save(input);
    assert(err == Error::NoError);

    EmptyData output{};

    Deserializer deserializer(stream);
    err = deserializer.load(output);
    assert(err == Error::NoError);
}

struct InvalidData
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
// It is only here to show what happens if we pass structure containing 
// fields with any other types except of uint64_t or bool 
// to Serializer or Deserializer

// void
// invalid_data_test()
// {
//     InvalidData input{ "input-data" };

//     std::stringstream stream;

//     Serializer serializer(stream);
//     serializer.save(input);

//     InvalidData output{ "output-data" };

//     Deserializer deserializer(stream);
//     const Error err = deserializer.load(output);
// }

const std::vector<std::function<void()>> tests{
    valid_data_test,
    corrupted_bool_test,
    not_a_number_test,
    negative_number_test,
    number_starts_with_zero_test,
    too_big_number_test,
    wrong_parameter_type_test,
    too_few_params_test,
    too_many_params_test,
    empty_data_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}