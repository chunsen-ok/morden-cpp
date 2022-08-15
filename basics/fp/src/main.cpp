#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

// filter: C<T>, (T -> bool) -> C<T>;
// transform: C<T>, (In -> Out) -> C<Out>;
// reduce/folding: C<T>, R, (R, T -> R) -> R;

enum Gender
{
    Male,
    Female,
};

class Human
{
public:
    Human(const std::string& name, Gender gender)
        : mName(name)
        , mGender(gender)
    {}

    const std::string& name() const { return mName; }
    Gender gender() const { return mGender; }

private:
    std::string mName;
    Gender mGender;
};

// find_females: std::vector<Human> -> std::vector<std::string>;
// is_female: Human -> bool;

bool is_female(const Human& human)
{
    return human.gender() == Gender::Female;
}

std::vector<std::string> find_females(const std::vector<Human>& humans)
{
    // return filter(humans, is_female);
    std::vector<std::string> names;
    for (const auto& human: humans) {
        if (is_female(human)) {
            names.push_back(human.name());
        }
    }

    return names;
}

bool is_not_whitespace(char ch)
{
    return ch != ' ' && ch != '\n' && ch != '\t';
}

std::string trim_left(std::string s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_not_whitespace));
    return s;
}

std::string trim_right(std::string s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), is_not_whitespace).base(), s.end());
    return s;
}

std::string trim(std::string s)
{
    return trim_right(trim_left(s));
}

class MultiArgs
{
public:

    template<typename ... Args>
    static std::shared_ptr<MultiArgs> create(Args ... args)
    {
        return std::shared_ptr<MultiArgs>(new MultiArgs(std::forward<Args>(args)...));
    }

private:
    MultiArgs(int a, double b, const std::string& c)
        : mA(a)
        , mB(b)
        , mC(c)
    {

    }

private:
    int mA;
    double mB;
    std::string mC;
};

int main()
{
    const std::vector<Human> humans{
        Human{"Nihao",Male},
        Human{"Abc",Female},
        Human{"VHG",Male},
        Human{"HAH",Male},
        Human{"W2V",Female},
        Human{"HAV",Female},
        Human{"ANH",Male},
        Human{"AHE",Female},
        Human{"DH",Male},
        Human{"DCV",Male},
        Human{"DHW",Male},
        Human{"TH",Female},
        Human{"SJH",Male},
        Human{"HTR",Female},
    };

    for(const auto& name: find_females(humans)) {
        std::cout << name << std::endl;
    }

    std::string s{"  Hello world  !  "};

    std::cout << trim(s) << std::endl;

    return 0;
}
