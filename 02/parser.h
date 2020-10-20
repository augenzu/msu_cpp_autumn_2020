#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <functional>
#include <cstdint>
#include <cctype>

class TokenParser
{
private:
    enum State { ST_SPACE, ST_NUMBER, ST_STRING };
    State state{ ST_SPACE };

    uint64_t curr_num{ 0 };
    std::string curr_str{};

    std::function<void()> start_callback{ [](){ std::cout << "start_callback is called" << std::endl; } };
    std::function<void()> end_callback{ [](){ std::cout << "end_callback is called" << std::endl; } };
    std::function<void(uint64_t)> number_token_callback{ [](uint64_t num)
            {
                std::cout << "number_token_callback is called, " 
                << "number is " << num << std::endl; 
            } };
    std::function<void(const std::string &)> string_token_callback{ [](const std::string &str)
            {
                std::cout << "str_token_callback is called, " 
                << "string is " << str << std::endl; 
            } };

public:
    TokenParser();
    ~TokenParser();
    void 
    set_start_callback(const std::function<void()> &);
    void
    set_end_callback(const std::function<void()> &);
    void
    set_number_token_callback(const std::function<void(uint64_t)> &);
    void
    set_string_token_callback(const std::function<void(const std::string &)> &);
    void
    parse(const std::string &);
};

#endif
