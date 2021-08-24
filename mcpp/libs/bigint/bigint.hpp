#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <random>

class BigInt
{
public:
    BigInt() = default;
    BigInt(const std::string &numStr, bool positive = true);

    void set_positve(bool positive = true) { m_positive = positive; }
    bool is_positive() const { return m_positive; }

    BigInt operator+(const BigInt &other) const;
    BigInt operator-(const BigInt &other) const;
    BigInt operator*(const BigInt &other) const;
    BigInt operator/(const BigInt &other) const;
    BigInt operator%(const BigInt &other) const;
    bool operator==(const BigInt &other) const;
    bool operator<(const BigInt &other) const;

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
    
    static bool can_conevert(const std::string &numStr);
    
    template<int MIN = 10, int MAX = 1024>
    static BigInt random() {
        int *seed = new int;
        std::mt19937_64 e(*seed);
        std::uniform_int_distribution<int> dist(MIN, MAX);
        std::uniform_int_distribution<int> rnum(0, 9);
        const int len = dist(e);
        delete seed;

        std::string s;
        for (int i = 0; i < len; ++i) {
            s.push_back('0' + static_cast<char>(rnum(e)));
        }

        return BigInt(s);
    }

    friend std::ostream &operator<<(std::ostream &os, const BigInt &num) {  
        if (num.m_nums.size() > 0) {
            return os << (num.is_positive() ? "" : "-") << num.m_nums;
        } else {
            return os << "0";
        }
    }

private:
    void removeFrontZero();

private:
    bool m_positive{true};
    std::string m_nums;
};


#endif
