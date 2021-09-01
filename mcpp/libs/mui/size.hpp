#ifndef SIZE_HPP
#define SIZE_HPP

template<typename T>
class Size 
{
public:
    T w, h;
};

template<typename T>
bool operator==(const Size<T> &lhs, const Size<T> &rhs) {
    return lhs.w == rhs.w && lhs.h == rhs.h;
}

template<typename T>
bool operator!=(const Size<T> &lhs, const Size<T> &rhs) {
    return !(lhs == rhs);
}

#endif
