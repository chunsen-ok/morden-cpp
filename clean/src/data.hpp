#ifndef CLEAN_DATA_HPP
#define CLEAN_DATA_HPP

template<int R, typename T>
class Data
{
public:
    constexpr int role() const { return R; }

    void reset(const T &data) { inner = data; }
    void reset(T &&data) { inner = std::move(data); }

    const T &operator*() const { return inner; }
    T &operator*() { return inner; }

    const T *operator->() const { return &inner; }
    T *operator->() { return &inner; }

private:
    T inner;
};

#endif
