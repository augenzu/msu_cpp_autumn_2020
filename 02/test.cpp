#include "parser.h"
#include "test.h"

std::vector<InOut> test_in_outs{
    { 
        "  asd 1    32not-a-number", { { 1 }, 
        { "asd", "32not-a-number" } } 
    },
    { 
        "000123\n\t0000123a", 
        { { 123 }, { "0000123a" } } 
    },
    { 
        "\tword-word--word--- 42\\42\\42/", 
        { {}, { "word-word--word---", "42\\42\\42/" } } 
    },
    { 
        "very_very_long_string\t\r10_000_000\n\n\n\n\n\n", 
        { {}, { "very_very_long_string", "10_000_000" } } 
    },
    { 
        "---___---___8___--- 8 ---___---", 
        { { 8 }, { "---___---___8___---", "---___---" } } 
    }
};

void
testing()
{
    std::vector<std::string> start_v{};
    std::vector<std::string> end_v{};
    std::vector<uint64_t> num_v{};
    std::vector<std::string> str_v{};

    auto 
    lambda_start_callback_test = [&]()
            {
                start_v.push_back("LSCT");
            };
    auto 
    lambda_end_callback_test = [&]()
            {
                end_v.push_back("LECT");
            };
    auto 
    lambda_number_token_callback_test = [&](uint64_t num)
            {
                num_v.push_back(num);
            };
    auto 
    lambda_string_token_callback_test = [&](const std::string &str)
            {
                str_v.push_back(str);
            };

    TokenParser tp;
    tp.set_start_callback(lambda_start_callback_test);
    tp.set_end_callback(lambda_end_callback_test);
    tp.set_number_token_callback(lambda_number_token_callback_test);
    tp.set_string_token_callback(lambda_string_token_callback_test);

    for (auto &test_in_out: test_in_outs) {
        start_v = {};
        end_v = {};
        num_v = {};
        str_v = {};
        tp.parse(test_in_out.input);
        assert(num_v == test_in_out.output.first);
        assert(str_v == test_in_out.output.second);
    }
}