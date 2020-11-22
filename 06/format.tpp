#include "format-error.hpp"
#include "to-strings.hpp"
#include <cctype>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

size_t
str_idx_to_num_idx(const std::string &str)
{
    auto it = str.begin();
    // skip space symbols
    for (; it != str.end() && isspace(*it); ++it) {
    }
    // index contains only space symbols
    if (it == str.end()) {
        throw FormatError("Argument index is empty.");
    }
    if (*it == '-') {
        throw FormatError("Argument index is negative.");
    }
    ++it;
    for (; it != str.end() && !isspace(*it); ++it) {
        if (!isdigit(*it)) {
            throw FormatError("Argument index is not a number.");
        }
    }
    // check whether the rest of index contains only space symbols
    for (; it != str.end() && isspace(*it); ++it) {
    }
    if (it != str.end()) {
        throw FormatError("Argument index is not a number.");
    }
    
    std::string max_str_idx = std::to_string(std::numeric_limits<size_t>::max());
    if (str.size() > max_str_idx.size()
            || (str.size() == max_str_idx.size() && str > max_str_idx)) {
        throw FormatError("Argument index is too big.");
    }

    size_t num = std::stoul(str);
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