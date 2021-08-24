#include "bigint.hpp"
#include <algorithm>
#include <stdexcept>
#include <string_view>

namespace {

constexpr bool isDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}

bool less_than(const std::string &lhs, const std::string &rhs) {
    if (lhs.size() == rhs.size()) {
        for (int i = 0; i < lhs.size(); ++i) {
            const char lt = lhs[i];
            const char rt = rhs[i];
            if (lt != rt) {
                return lt < rt;
            }
        }
    }
    return lhs.size() < rhs.size();
}

std::pair<bool, std::string> abs_add(const std::string &lhs, const std::string &rhs) {
    const std::string &larger = less_than(lhs, rhs) ? rhs : lhs;
    const std::string &smaller = less_than(lhs, rhs) ? lhs : rhs;
    std::string s;
    char n{0};
    for (int i =  0; i < larger.size(); ++i) {
        char t = larger[larger.size() - 1 - i] - '0' + n;
        if (i < smaller.size())  {
            t = t + (smaller[smaller.size() - 1 - i] - '0');
        }        
        s.push_back('0' + (t % 10));
        n = t / 10;
    }

    if (n > 0) {
        s.push_back('0' + n);
    }

    std::reverse(s.begin(), s.end());

    return std::make_pair(true, s);
}

std::pair<bool, std::string> abs_sub(const std::string &lhs, const std::string &rhs) {
    const std::string &large = less_than(lhs, rhs) ? rhs : lhs;
    const std::string &small = less_than(lhs, rhs) ? lhs : rhs;
    std::string s;
    char n {0};
    for (int i = 0; i < large.size(); ++i) {
        const char n1 = (large[large.size() - 1 - i] - '0') + n;
        if (i < small.size()) {
            const char n2 = small[small.size() - 1 - i] - '0';
            char t = n1 - n2;
            if (t < 0) { // 借位
                n = -1;
                t += 10;
            } else {
                n = 0;
            }
            s.push_back(t + '0');
        } else {
            s.push_back(n1 + '0');
        }
    }

    std::reverse(s.begin(), s.end());

    const bool positive = !less_than(lhs, rhs);
    return std::make_pair(positive, s);
}

std::pair<bool, std::string> abs_mul(const std::string &lhs, const std::string &rhs) {
    std::string s;
    for (int i = lhs.size() - 1; i >= 0; --i) {
        std::string tmp;
        char n{0};
        const int base = lhs.size() - 1 - i;
        if (base > 0) {
            tmp.append(base, '0');
        }
        const char n1 = lhs[i] - '0';
        for (int j = rhs.size() - 1; 0 <= j; --j) {
            const char n2 = rhs[j] - '0';
            const char t = n1 * n2 + n;
            tmp.push_back('0' + (t % 10));
            n = t / 10;
        }
        if (n > 0) {
            tmp.push_back('0' + n);
        }
        
        std::reverse(tmp.begin(), tmp.end());
        s = abs_add(s, tmp).second;
    }
    return std::make_pair(true, s);
}

std::pair<bool, std::string> abs_div(const std::string &lhs, const std::string &rhs) {
    if (less_than(lhs, rhs)) {
        return std::make_pair(true, "");
    } else if (lhs == rhs) {
        return std::make_pair(true, "1");
    } else {
        const std::string_view dividend(lhs.data(), lhs.size() - (rhs.size() - 1));
        const char divisor = rhs[0] - '0';

        std::string s;
        char n{0};
        for (const char v: dividend) {
            n = n * 10 + (v - '0');
            const char t = n / divisor;
            if (t != 0) {
                s.push_back(t + '0');
                n = n % divisor;
            } else {
                n = v - '0';
                if (s.size() != 0) {
                    s.push_back('0');
                }
            }
        }
        return std::make_pair(true, s);
    }
    return std::make_pair(true, "");
}

}

BigInt::BigInt(const std::string &numStr, bool positive)
    : m_positive(positive)
    , m_nums(numStr)
{
    if (m_nums.size() > 0) {
        if (!isDigit(m_nums[0])) {
            m_nums.erase(0, 1);
        }
        if (!can_conevert(m_nums)) {
            throw std::invalid_argument("Invalid BigInt string");
        }
    }

    removeFrontZero();
}


BigInt BigInt::operator+(const BigInt &other) const {
    if (is_positive() == other.is_positive()) {
        std::pair<bool, std::string> s = abs_add(m_nums, other.m_nums);
        return BigInt(s.second, s.first);
    } else {
        auto s = abs_sub(m_nums, other.m_nums);
        if (this->operator<(other)) {
            s.first = !s.first;
        }
        return BigInt(s.second, s.first);
    }
    return BigInt();
}

BigInt BigInt::operator-(const BigInt &other) const {
    if (is_positive() == other.is_positive()) {
        const std::pair<bool, std::string> s = abs_sub(m_nums, other.m_nums);
        return BigInt(s.second, s.first);
    } else {
        auto s = abs_add(m_nums, other.m_nums);
        if (this->operator<(other)) {
            s.first = !s.first;
        }
        return BigInt(s.second, s.first);
    }
    return BigInt();
}

BigInt BigInt::operator*(const BigInt &other) const {
    bool positive = is_positive() == other.is_positive();
    const auto s = abs_mul(m_nums, other.m_nums);
    return BigInt{s.second, positive};
}

BigInt BigInt::operator/(const BigInt &other) const {
    const auto s = abs_div(m_nums, other.m_nums);
    return BigInt(s.second, is_positive() == other.is_positive());
}

BigInt BigInt::operator%(const BigInt &other) const {
    const auto op = abs_div(m_nums, other.m_nums);
    const auto m = abs_mul(op.second, other.m_nums);
    const auto remain = abs_sub(m_nums, m.second);
    return BigInt(remain.second, remain.first);
}

bool BigInt::operator==(const BigInt &other) const {
    if (is_positive() == other.is_positive() && m_nums.size() == other.m_nums.size() && m_nums == other.m_nums) {
        return true;
    }
    return false;
}

bool BigInt::operator<(const BigInt &other) const {
    if (is_positive() == other.is_positive()) {
        if (m_nums.size() == other.m_nums.size()) {
            for (int i = 0; i < m_nums.size(); ++i) {
                const char lhs = m_nums[i];
                const char rhs = other.m_nums[i];
                if (lhs != rhs) { 
                    return is_positive() ? lhs < rhs : lhs > rhs;
                }
            }
        }
        return m_nums.size() < other.m_nums.size();
    }
    return !is_positive();
}
    
bool BigInt::can_conevert(const std::string &numStr) {
    for (const char ch: numStr) {
        if (!isDigit(ch)) {
            return false;
        }
    }
    return true;
}

void BigInt::removeFrontZero() {
    int eraseCount{0};
    for (int i = 0; i < m_nums.size(); ++i) {
        if (m_nums[i] == '0') {
            ++eraseCount;
        } else {
            break;
        }
    }
    if (eraseCount > 0) {
        m_nums.erase(0, eraseCount);
    }
}
