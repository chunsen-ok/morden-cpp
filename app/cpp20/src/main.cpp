#include <iostream>

template<typename T>
struct AccTraits;

template<>
struct AccTraits<char> {
    using AccT = int;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccTraits<int> {
    using AccT = long;
    static constexpr AccT zero() { return 0; }
};

template<>
struct AccTraits<float> {
    using AccT = double;
    static constexpr AccT zero() { return 0.0; }
};

struct SumPolicy {
    template<typename T0, typename T1>
    static T0 accumulate(T0 const& total, T1 const& value) {
        return total + value;
    }
};

struct MultiplyPolicy {
    template<typename T0, typename T1>
    static T0 accumulate(T0 const& total, T1 const& value) {
        return total * value;
    }
};

template<typename T>
struct MaxTraits;

template<>
struct MaxTraits<char> {
    using AccT = char;
    static constexpr char zero() { return std::numeric_limits<char>::min(); }
};

struct MaxPolicy {
    template<typename T0, typename T1>
    static T0 accumulate(T0 const& total, T1 const& value) {
        return std::max(total, value);
    }
};

template<typename Iter, typename Policy = SumPolicy, typename AT = AccTraits<typename std::iterator_traits<Iter>::value_type>>
auto accum(Iter beg, Iter end, typename AT::AccT const& initial = AT::zero())
{
    typename AT::AccT total = initial;
    while (beg != end) {
        total = Policy::accumulate(total, *beg);
        ++beg;
    }
    return total;
}

int main() {
    const char chars[] = "72985021734-2734.";
    std::cout << accum<decltype(std::begin(chars)), MaxPolicy, MaxTraits<char>>(std::begin(chars), std::end(chars)) << std::endl;
    return 0;
}
