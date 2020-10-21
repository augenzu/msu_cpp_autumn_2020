#include "parser.h"
#include "test.h"

// test inputs and true outputs
std::vector<InOut> tests{
    { 
        "  asd 1    32not-a-number", 
        { { 0 }, { 0 }, { 1 }, { "asd", "32not-a-number" } } 
    },
    { 
        "000123\n\t0000123a", 
        { { 0 }, { 0 }, { 123 }, { "0000123a" } } 
    },
    { 
        "\tword-word--word--- 42\\42\\42/", 
        { { 0 }, { 0 }, {}, { "word-word--word---", "42\\42\\42/" } } 
    },
    { 
        "very_very_long_string\t\r10_000_000\n\n\n\n\n\n", 
        { { 0 }, { 0 }, {}, { "very_very_long_string", "10_000_000" } } 
    },
    { 
        "---___---___8___--- 8 ---___---", 
        { { 0 }, { 0 }, { 8 }, { "---___---___8___---", "---___---" } } 
    },
    {
        "",
        { { 0 }, { 0 }, {}, {} }
    },
    {
        "0x100\n100\t0.01",
        { { 0 }, { 0 }, { 100 }, { "0x100", "0.01" } }
    },
    {
        "1 1 2 3 5 8 13 21",
        { { 0 }, { 0 }, { 1, 1, 2, 3, 5, 8, 13, 21 }, {} }
    }
};

void
testing()
{
    // for output of test callback
    Output output{};

    // test callbacks
    auto 
    start_callback_test = [&]()
            {
                output.start_v.push_back(0);
            };
    auto 
    end_callback_test = [&]()
            {
                output.end_v.push_back(0);
            };
    auto 
    number_token_callback_test = [&](uint64_t num)
            {
                output.num_v.push_back(num);
            };
    auto 
    string_token_callback_test = [&](const std::string &str)
            {
                output.str_v.push_back(str);
            };

    TokenParser tp;
    tp.set_start_callback(start_callback_test);
    tp.set_end_callback(end_callback_test);
    tp.set_number_token_callback(number_token_callback_test);
    tp.set_string_token_callback(string_token_callback_test);

    for (auto &test: tests) {
        output = {};
        tp.parse(test.input);
        assert(output.num_v == test.output.num_v);
        assert(output.str_v == test.output.str_v);
    }

    std::cout << "All tests passed successfully." << std::endl;
}