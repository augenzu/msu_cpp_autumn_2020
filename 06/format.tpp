#include "format-error.hpp"
#include "to-strings.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

size_t
str_idx_to_num_idx(const std::string &str)
{
    size_t num = std::stoul(str);

    std::stringstream check_stream;
    check_stream << str;

    size_t check_num = -1;
    check_stream >> check_num;
    std::string rest;
    check_stream >> rest;

    if (rest != "") {
        throw FormatError("Argument index is not a number.");
    }

    return num;
}

enum class State
{
    RawChars,
    ArgumentIndexChars
};

template<class... Args> std::string
format(const std::string &fmt, const Args &... args)
{
    std::vector<std::string> str_args = to_strings(args...);

    std::string formatted;

    size_t prev_pos = 0;
    size_t pos = 0;
    State state = State::RawChars;

    while (pos < fmt.size()) {
        char ch = fmt[pos];
        switch (state) {
        case State::RawChars:
            {
                switch (ch) {
                case '{':
                    {
                        // out raw chars as they are
                        formatted += std::string(fmt, prev_pos, pos - prev_pos);
                        prev_pos = ++pos;
                        state = State::ArgumentIndexChars;
                        break;
                    }
                case '}':
                    {
                        // error - there was no '{' before
                        throw FormatError("Close brace '}' without previous open brace '{'.");
                    }
                default:
                    {
                        ++pos;
                    }
                }
                break;
            }
        case State::ArgumentIndexChars:
            {
                switch (ch) {
                case '{':
                    {
                        // another one '{' before '}' for previous '{'
                        throw FormatError("Open brace'{' without close brace '}'.");
                    }
                case '}':
                    {
                        // argument index expression has ended
                        std::string str_idx = std::string(fmt, prev_pos, pos - prev_pos);
                        size_t num_idx = str_idx_to_num_idx(str_idx);
                        if (num_idx >= str_args.size()) {
                            throw FormatError("Argument index should be less than number of arguments.");
                        } else {
                            formatted += str_args[num_idx];
                            prev_pos = ++pos;
                            state = State::RawChars;
                        }
                        break;
                    }
                default:
                    {
                        ++pos;
                    }
                }
            }
        }
    }

    switch (state) {
        case State::RawChars:
            {
                // the rest of string
                formatted += std::string(fmt, prev_pos, pos - prev_pos);
                break;
            }
        case State::ArgumentIndexChars:
            {
                // '{' without '}'
                throw FormatError("Open brace'{' without close brace '}'.");
            }
    }

    return formatted;
}