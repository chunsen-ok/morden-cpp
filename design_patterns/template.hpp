#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP
#include <iostream>

#define ACCESSER(B, O) friend void test<B, O>(O * o);

template <typename T, typename U>
void test(U *w)
{
    T *t = new T;
    t->T::hello(w);

    delete t;
    t = nullptr;
}

class Obj
{
public:
    int count{0};
};

template <typename T>
class Builder
{
protected:
    virtual void hello(T *o) = 0;
};

class MyBuilder : public Builder<Obj>
{
    ACCESSER(MyBuilder, Obj)
protected:
    void hello(Obj *o) override
    {
        std::cout << o->count << std::endl;
    }

    void other(Obj *o)
    {
        hello(o);
    }
};

#endif
