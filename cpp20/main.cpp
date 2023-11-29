/*! 一种声明式的命令行构件库。

  > cman --help
  The C/C++ project & package manager
   
  Usage: cman [OPTIONS] [COMMAND]
  
  Options:
      -V, --version
  
  Commands:
      new
      build
      test
      doc
      ...
  [Footer]
*/

#include <iostream>
#include <variant>

class Zero;
class ZeroElement
{
public:
    ZeroElement(Zero&& builder)
        : mValue(std::move(builder.mValue))
    {

    }

private:
    int mValue;
};

class Zero
{
    friend class ZeroElement;
public:
    Zero() = default;
    
    Zero(const Zero&) = delete;
    Zero& operator=(const Zero&) = delete;
    
    Zero(Zero&& other)
        : mValue(std::move(other.mValue))
    {

    }

    Zero& operator=(Zero&& other)
    {
        mValue = std::move(other.mValue);
    }

    Zero& value(int v)
    {
        mValue = v;
        return *this;
    }

private:
    int mValue;
};

class One;
class OneElement: public ZeroElement
{
public:
    OneElement(One&& builder)
        : ZeroElement(std::move(builder.mZero))
        , mValue(std::move(builder.mValue))
    {}

private:
    int mValue;
};

class One
{
    friend class OneElement;
public:
    One& value(int v)
    {
        mValue = v;
        return *this;
    }

    One& zero(Zero&& v)
    {
        mZero = std::move(v);
    }

private:
    Zero mZero;
    int mValue;
};

int main(int argc, char* argv[])
{
    One()
    .value(1)
    .zero(std::move(
        Zero().
        value(0)
    ));

    return 0;
}
