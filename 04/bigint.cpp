#include "bigint.h"

const size_t Bigint::DIGIT_LEN = 18;
const uint64_t Bigint::RADIX = 1000000000000000000U;  // 10 ** 18


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

    uint64_t abs_val = abs(val);
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
    for (int i = digits_cnt - 1; i >= 0; --i) {
        ss << digits[i];
    }

    std::string str;
    ss >> str;

    return str;
}


// Bigint &
// Bigint::operator+=(const Bigint &rhs)
// {
//     // assume *this & rhs have the same signs

//     uint32_t carry = 0;

//     for (size_t i = 0; i < std::min(digits_cnt, rhs.digits_cnt); ++i) {
//         uint64_t sum = digits[i] + rhs.digits[i] + carry;
//         digits[i] += sum % RADIX;
//         carry = sum / RADIX;
//     }

//     if (digits_cnt > rhs.digits_cnt) {
//         digits[rhs.digits_cnt] += carry;
//     } else {
//         uint32_t new_digits
//     }







//     if (carry) {
//         if (digits_cnt > rhs.digits_cnt) {
//             digits[rhs.digits_cnt] += carry;
//         } else {

//         }
//     }

//     return *this;
// }


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