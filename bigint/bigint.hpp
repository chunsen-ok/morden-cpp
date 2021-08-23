#include <iostream>
#include <random>
#include <algorithm>
#include <stdexcept>

constexpr bool isDigit(char ch)
{
    return '0' <= ch && ch <= '9';
}

class BigInt
{
public:
    BigInt() = default;
    BigInt(const std::string &numStr): m_nums(numStr) {
        if (m_nums.size() > 0) {
            if (m_nums[0] == '-') {
                m_positive = false;
            }
            if (!isDigit(m_nums[0])) {
                m_nums.erase(0, 1);
            }
            if (!can_conevert(m_nums)) {
                throw std::invalid_argument("Invalid BigInt string");
            }
        }

        removeFrontZero();
    }

    bool is_positive() const { return m_positive; }

    BigInt operator+(const BigInt &other) const {
        if (is_positive() == other.is_positive()) {
            const int min_size = std::min(this->m_nums.size(), other.m_nums.size());
            const int max_size = std::max(this->m_nums.size(), other.m_nums.size());
            const BigInt &larger = this->m_nums.size() > other.m_nums.size() ? *this : other;
            std::string s;
            char n{0};
            for (int i =  0; i < max_size; ++i) {
                if (i < min_size)  {
                    const char t = (m_nums[m_nums.size() - 1 - i] - '0') + (other.m_nums[other.m_nums.size() - 1 - i] - '0') + n;
                    s.push_back('0' + (t % 10));
                    n = t / 10;
                } else {
                    s.push_back(larger.m_nums[larger.m_nums.size() - 1 - i]);
                }
            }

            if (!is_positive()) {
                s.push_back('-');
            }
            
            std::reverse(s.begin(), s.end());
            return BigInt(s);
        }
        return BigInt();
    }

    /*
    BigInt operator-(const BigInt &other) const {
        if (is_positive() == other.is_positive()) {
            bool positive = !this->operator<(other);
            const BigInt &large = abs_less_than(other) ? other : *this;
            const BigInt &small = abs_less_than(other) ? *this : other;
            for (int i = 0; i < large.m_nums.size(); ++i) {
                // ...
            }
        }
    }
    */

    BigInt operator*(const BigInt &other) const {
        BigInt total;
        for (int i = m_nums.size() - 1; i >= 0; --i) {
            std::string tmp;
            char n{0};
            const int base = m_nums.size() - 1 - i;
            if (base > 0) {
                tmp.append(base, '0');
            }
            const char n1 = m_nums[i] - '0';
            for (int j = other.m_nums.size() - 1; 0 <= j; --j) {
                const char n2 = other.m_nums[j] - '0';
                const char t = n1 * n2 + n;
                tmp.push_back('0' + (t % 10));
                n = t / 10;
            }
            if (n > 0) {
                tmp.push_back('0' + n);
            }
            std::reverse(tmp.begin(), tmp.end());
            total = total + BigInt(tmp);
        }
        return total;
    }

    bool operator==(const BigInt &other) const {
        if (is_positive() == other.is_positive() && m_nums.size() == other.m_nums.size() && m_nums == other.m_nums) {
            return true;
        }
        return false;
    }

    bool operator<(const BigInt &other) const {
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

    bool operator<=(const BigInt &other) const {
        return this->operator<(other) || this->operator==(other);
    }

    bool operator>(const BigInt &other) const {
        return !this->operator<=(other);
    }

    bool operator>=(const BigInt &other) const {
        return !this->operator<(other);
    }

    bool operator!=(const BigInt &other) const {
        return !this->operator==(other);
    }

    BigInt abs() const {
        BigInt tmp = *this;
        tmp.m_positive = true;
        return tmp;
    }

    template<int MIN = 10, int MAX = 1024>
    static BigInt random() {
        std::random_device r;
        std::default_random_engine e(r());
        std::uniform_int_distribution<int> dist(MIN, MAX);
        std::uniform_int_distribution<int> rnum(0, 9);
        const int len = dist(e);

        std::string s;
        for (int i = 0; i < len; ++i) {
            s.push_back('0' + static_cast<char>(rnum(e)));
        }

        return BigInt(s);
    }
    
    static bool can_conevert(const std::string &numStr) {
        for (const char ch: numStr) {
            if (!isDigit(ch)) {
                return false;
            }
        }
        return true;
    }
    
    friend std::ostream &operator<<(std::ostream &os, const BigInt &num) {  
        if (num.m_nums.size() > 0) {
            return os << (num.is_positive() ? "+" : "-") << num.m_nums;
        } else {
            return os << "0";
        }
    }

private:

    void removeFrontZero() {
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
    
    bool abs_less_than(const BigInt &other) const {
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

private:
    bool m_positive{true};
    std::string m_nums;
};
