#ifndef POINT_HPP
#define POINT_HPP

template<typename T>
class Point
{
public:
    T x{0}, y{0};
};

template<typename T>
bool operator==(const Point<T> &lhs, const Point<T> &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

template<typename T>
bool operator!=(const Point<T> &lhs, const Point<T> &rhs) {
    return !(lhs == rhs);
}

#endif
