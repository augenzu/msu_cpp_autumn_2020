#ifndef BIGINT_H
#define BIGINT_H

#include <cstdint>
#include <iostream>
#include <sstream>

class Bigint
{
private:
    static const size_t DIGIT_LEN;
    static const uint64_t RADIX;

    bool is_negative{ false };
    size_t digits_cnt{};  // number of digits
    uint64_t *digits{ nullptr };  // store digits of number in reversed order (LE)

    void
    swap(Bigint &);
    void
    remove_significant_zeros();

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

    Bigint
    operator-() const;
    Bigint &
    operator+=(const Bigint &);
    Bigint &
    operator-=(const Bigint &);
    Bigint &
    operator*=(const Bigint &);

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