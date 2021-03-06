#include "format.hpp"
#include "format-error.hpp"
#include "test.hpp"
#include <cassert>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <vector>

void
valid_format_test()
{
    auto text = format("{1} + {2} != {0}", 3.001, "one", 2);
    assert(text == "one + 2 != 3.001");
}

void
too_many_open_braces_test()
{
    try {
        auto text = format("{1}+{1{} = {0}", 2, "one");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Open brace'{' without close brace '}'."));
    }
}

void
too_many_close_braces_test()
{
    try {
        auto text = format("{1}+{1} }} = {0}", 2, "one");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Close brace '}' without previous open brace '{'."));
    }
}

void
indexes_surrounded_by_spaces_test()
{
    auto text = format("{  1}+{ 1 } = {0   } just stuff", 2, "one");
    assert(text == "one+one = 2 just stuff");
}

void
string_without_args_test()
{
    auto text = format("Just unformatted string");
    assert(text == "Just unformatted string");
}

void
straight_open_brace_test()
{
    try {
        auto text = format("some } text {0}", "some string");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Close brace '}' without previous open brace '{'."));
    }
}

void
straight_close_brace_test()
{
    try {
        auto text = format("some { text {0}", "some string");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Open brace'{' without close brace '}'."));
    }
}

void
empty_index_test()
{
    try {
        auto text = format("text with empty {} in brace");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is empty."));
    }
}

void
only_spaces_index_test()
{
    try {
        auto text = format("text with only spaces {     } in brace");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is empty."));
    }
}

void
spoiled_index_test()
{
    try {
        auto text = format("text with { 0tr0uble } in brace", "arg");
        std::cout << "text: " << text << std::endl;
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is not a number."));
    }
}

void
not_a_number_index_test()
{
    try {
        auto text = format("text with { not-a-number } in brace", "arg");
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is not a number."));
    }
}

void
too_big_index_test()
{
    try {
        auto text = format("text with { 6764454768658585928579879898768768768767876878 } in brace", "arg");
        std::cout << "text: " << text << std::endl;
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is too big."));
    }
}

void
negative_index_test()
{
    try {
        auto text = format("text with { -1 } in brace", "arg");
        std::cout << "text: " << text << std::endl;
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index is negative."));
    }
}

void
only_args_in_format_string_test()
{
    auto text = format("{3}{0}{1}{2}", "@", "#", "$", "%");
    assert(text == "%@#$");
}

void
too_few_args_test()
{
    try {
        auto text = format("text with { 3 } in brace", 0, 1, 2);
        std::cout << "text: " << text << std::endl;
    } catch (const FormatError &fe) {
        assert(fe.what() == std::string("Argument index should be less than number of arguments."));
    }
}

const std::vector<std::function<void()>> tests{
    valid_format_test,
    too_many_open_braces_test,
    too_many_close_braces_test,
    indexes_surrounded_by_spaces_test,
    string_without_args_test,
    straight_open_brace_test,
    straight_close_brace_test,
    empty_index_test,
    only_spaces_index_test,
    spoiled_index_test,
    not_a_number_index_test,
    too_big_index_test,
    negative_index_test,
    too_few_args_test,
    only_args_in_format_string_test
};

void
testing()
{
    for (auto &test : tests) {
        test();
    }
    
    std::cout << "All tests passsed succesfully." << std::endl;
}