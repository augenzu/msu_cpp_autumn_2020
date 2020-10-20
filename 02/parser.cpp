#include "parser.h"

TokenParser::TokenParser() = default;

TokenParser::~TokenParser() = default;

void 
TokenParser::set_start_callback(const std::function<void()> &start_callback)
{
    this->start_callback = start_callback;
}

void 
TokenParser::set_end_callback(const std::function<void()> &end_callback)
{
    this->end_callback = end_callback;
}

void
TokenParser::set_number_token_callback(const std::function<void(uint64_t)> &number_token_callback)
{
    this->number_token_callback = number_token_callback;
}

void
TokenParser::set_string_token_callback(const std::function<void(const std::string &)> &string_token_callback)
{
    this->string_token_callback = string_token_callback;
}

void
TokenParser::parse(const std::string &input)
{
    start_callback();
    
    state = ST_SPACE;
    size_t i = 0;

    while(i < input.size()) {
        char ch = input[i];

        switch(state) {
        case ST_SPACE:
            if (isspace(ch)) {
                ;
            } else if (isdigit(ch)) {
                curr_num = ch - '0';
                curr_str = "";
                curr_str += ch;   // this may be not a number but just a beginning of a string
                state = ST_NUMBER;
            } else {
                curr_str = "";
                curr_str += ch;
                state = ST_STRING;
            }
            ++i;
            break;
        case ST_NUMBER:
            if (isspace(ch)) {
                number_token_callback(curr_num);
                state = ST_SPACE;
            } else if (isdigit(ch)) {
                curr_num *= 10;
                curr_num += (ch - '0');
                curr_str += ch;   // this may be not a number but just a beginning of a string
            } else {
                curr_str += ch;
                state = ST_STRING;
            }
            ++i;
            break;
        case ST_STRING:
            if (isspace(ch)) {
                string_token_callback(curr_str);
                state = ST_SPACE;
            } else if (isdigit(ch)) {
                curr_str += ch;
            } else {
                curr_str += ch;
            }
            ++i;
            break;
        }        
    }

    switch(state) {
    case ST_NUMBER:
        number_token_callback(curr_num);
        break;
    case ST_STRING:
        string_token_callback(curr_str);
        break;
    }       

    end_callback();
}
