#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <iostream>
#include <sstream>

class Bigint
{
private:
    // digit base is 10, not 16!
    // little-endian
    static const size_t DIGIT_LEN;  // in 10x digits
    static const uint64_t RADIX;

    bool is_negative{ false };
    size_t digits_cnt{};  // number of digits
    uint64_t *digits{ nullptr };  // we store digits of number in reversed order

public:
    Bigint();
    Bigint(int64_t);
    explicit Bigint(const std::string &);
    Bigint(const Bigint &);
    Bigint(Bigint &&);

    ~Bigint();

    Bigint &
    operator=(const Bigint &);
    Bigint &
    operator=(Bigint &&);

    operator std::string() const;

    Bigint &
    operator+=(const Bigint &);
    Bigint &
    operator-=(const Bigint &);
    Bigint &
    operator*=(const Bigint &);
    Bigint
    operator-() const;

    bool
    operator==(const Bigint &) const;
    bool
    operator!=(const Bigint &) const;
    bool
    operator<(const Bigint &) const;
    bool
    operator<=(const Bigint &) const;
    bool
    operator>(const Bigint &) const;
    bool
    operator>=(const Bigint &) const;
};

std::ostream &
operator<<(std::ostream &, const Bigint &);

Bigint
operator+(const Bigint &, const Bigint &);
Bigint
operator-(const Bigint &, const Bigint &);
Bigint
operator*(const Bigint &, const Bigint &);

#endif