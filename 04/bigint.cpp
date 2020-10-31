#include "bigint.h"

const size_t Bigint::DIGIT_LEN = 9;
const uint64_t Bigint::RADIX = 1000000000U;  // 10 ** 9


void
Bigint::swap(Bigint &rhs)
{
    std::swap(is_negative, rhs.is_negative);
    std::swap(digits_cnt, rhs.digits_cnt);
    std::swap(digits, rhs.digits);
}

void
Bigint::remove_significant_zeros()
{
    int new_digits_cnt = digits_cnt;
    while (new_digits_cnt > 0 && !digits[new_digits_cnt - 1]) {
        --new_digits_cnt;
    }
    if (!new_digits_cnt) {
        new_digits_cnt = 1;
    }
    if (new_digits_cnt < digits_cnt) {
        uint64_t *new_digits = new uint64_t[new_digits_cnt];
        for (int i = 0; i < new_digits_cnt; ++i) {
            new_digits[i] = digits[i];
        }
        digits_cnt = new_digits_cnt;
        delete[] digits;
        digits = new_digits;
    }
}


Bigint::Bigint() : 
is_negative(false), digits_cnt(1), digits(new uint64_t[1])
{
    digits[0] = 0;
}

Bigint::Bigint(int64_t val)
{   
    is_negative = val < 0;

    uint64_t abs_val = llabs(val);
    if (abs_val / RADIX) {
        digits_cnt = 2;
        digits = new uint64_t[digits_cnt];
        digits[0] = abs_val % RADIX;
        digits[1] = abs_val / RADIX;
    } else {
        digits_cnt = 1;
        digits = new uint64_t[digits_cnt];
        digits[0] = abs_val;
    }
}

Bigint::Bigint(const std::string &str)
{
    is_negative = (str[0] == '-');
    digits_cnt = ((str.size() - is_negative) + (DIGIT_LEN - 1)) / DIGIT_LEN;

    digits = new uint64_t[digits_cnt];
    for (int i = 0; i < digits_cnt; ++i) {
        digits[i] = 0;
    }

    int digit_pos = 0;
    uint64_t base = 1;
    int start_idx = is_negative;

    for (int i = 0; i < str.size() - start_idx; ++i) {
        int str_idx = str.size() - 1 - i;
        digits[digit_pos] += (str[str_idx] - '0') * base;
        base *= 10;
        if (i % DIGIT_LEN == DIGIT_LEN - 1) {
            ++digit_pos;
            base = 1;
        }
    }

    remove_significant_zeros();

    if (digits_cnt == 1 && digits[0] == 0) {
        is_negative = false;
    }
}

Bigint::Bigint(const Bigint &rhs) : 
is_negative(rhs.is_negative), digits_cnt(rhs.digits_cnt), 
        digits(new uint64_t[rhs.digits_cnt])
{
    for (int i = 0; i < rhs.digits_cnt; ++i) {
        digits[i] = rhs.digits[i];
    }
}

Bigint::Bigint(Bigint &&rhs) :
is_negative(rhs.is_negative), digits_cnt(rhs.digits_cnt), digits(rhs.digits)
{
    rhs.digits_cnt = 0;
    rhs.digits = nullptr;
}


Bigint::~Bigint()
{
    delete[] digits;
    digits = nullptr;
}


Bigint &
Bigint::operator=(const Bigint &rhs)
{
    Bigint copy_rhs{ rhs };
    swap(copy_rhs);
    return *this;
}
    
Bigint &
Bigint::operator=(Bigint &&rhs)
{
    swap(rhs);
    return *this;
}


Bigint::operator std::string() const
{
    std::stringstream ss;

    if (is_negative) {
        ss << '-';
    }

    ss << digits[digits_cnt - 1];
    for (int i = digits_cnt - 2; i >= 0; --i) {
        std::stringstream aux;
        aux << digits[i];
        size_t extra_zeros = DIGIT_LEN - aux.str().size();
        for (int i = 0; i < extra_zeros; ++i) {
            ss << 0;
        }
        ss << digits[i];
    }

    std::string str;
    ss >> str;

    return str;
}

Bigint
Bigint::operator-() const
{
    Bigint neg{ *this };
    neg.is_negative ^= false;
    return neg;
}

Bigint &
Bigint::operator+=(const Bigint &rhs)
{
    if (is_negative != rhs.is_negative) {
        return *this -= -rhs;
    }
    
    Bigint sum;
    sum.is_negative = is_negative;
    sum.digits_cnt = std::max(digits_cnt, rhs.digits_cnt) + 1;
    delete[] sum.digits;
    sum.digits = new uint64_t[sum.digits_cnt];

    uint64_t carry = 0;

    for (int i = 0; i < std::min(digits_cnt, rhs.digits_cnt); ++i) {
        sum.digits[i] = digits[i] + rhs.digits[i] + carry;
        carry = sum.digits[i] / RADIX;
        sum.digits[i] %= RADIX;
    }
    if (digits_cnt < rhs.digits_cnt) {
        for (int i = digits_cnt; i < rhs.digits_cnt; ++i) {
            sum.digits[i] = rhs.digits[i] + carry;
            carry = sum.digits[i] / RADIX;
            sum.digits[i] %= RADIX;
        }
    } else {
        for (int i = rhs.digits_cnt; i < digits_cnt; ++i) {
            sum.digits[i] = digits[i] + carry;
            carry = sum.digits[i] / RADIX;
            sum.digits[i] %= RADIX;
        }
    }
    sum.digits[sum.digits_cnt - 1] = carry;

    sum.remove_significant_zeros();
    swap(sum);

    return *this;
}

Bigint &
Bigint::operator-=(const Bigint &)
{
    return *this;
}

Bigint &
Bigint::operator*=(const Bigint &rhs)
{
    Bigint prod;
    prod.is_negative = is_negative ^ rhs.is_negative;
    prod.digits_cnt = digits_cnt + rhs.digits_cnt;
    delete[] prod.digits;
    prod.digits = new uint64_t[prod.digits_cnt];
    for (int i = 0; i < prod.digits_cnt; ++i) {
        prod.digits[i] = 0;
    }

    for (int i = 0; i < digits_cnt; ++i) {
        uint64_t carry = 0;
        for (int j = 0; j < rhs.digits_cnt; ++j) {
            uint64_t prod_item = digits[i] * rhs.digits[j] + prod.digits[i + j] + carry;
            prod.digits[i + j] = prod_item % RADIX;
            carry = prod_item / RADIX;
        }
        prod.digits[i + rhs.digits_cnt] += carry;
    }

    prod.remove_significant_zeros();
    swap(prod);
    
    return *this;
}


bool
Bigint::operator==(const Bigint &rhs) const
{
    if (is_negative != rhs.is_negative || digits_cnt != rhs.digits_cnt) {
        return false;
    }
    for (int i = 0; i < digits_cnt; ++i) {
        if (digits[i] != rhs.digits[i]) {
            return false;
        }
    }
    return true;
}
    
bool
Bigint::operator!=(const Bigint &rhs) const
{
    return !(*this == rhs); 
}
    
bool
Bigint::operator<(const Bigint &rhs) const
{
    if (is_negative != rhs.is_negative) {
        return is_negative;
    }
    if (digits_cnt < rhs.digits_cnt) {
        return true ^ is_negative;
    }
    if (digits_cnt > rhs.digits_cnt) {
        return false ^ is_negative;
    }
    for (int i = digits_cnt - 1; i >= 0; --i) {
        if (digits[i] < rhs.digits[i]) {
            return true ^ is_negative;
        }
        if (digits[i] > rhs.digits[i]) {
            return false ^ is_negative;
        }
    }
    return false ^ is_negative;
}
    
bool
Bigint::operator<=(const Bigint &rhs) const
{
    return *this < rhs || *this == rhs;
}
    
bool
Bigint::operator>(const Bigint &rhs) const
{
    return !(*this <= rhs);
}
    
bool
Bigint::operator>=(const Bigint &rhs) const
{
    return !(*this < rhs);
}


std::ostream &
operator<<(std::ostream &out, const Bigint &bigint)
{
    out << static_cast<std::string>(bigint);
    return out;
}