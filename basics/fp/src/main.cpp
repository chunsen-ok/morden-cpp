#include <iostream>
#include <string>
#include <algorithm>
#include <functional>

// filter: C<T>, (T -> bool) -> C<T>;
// transform: C<T>, (In -> Out) -> C<Out>;
// reduce/folding: C<T>, R, (R, T -> R) -> R;
// partition: 

enum Gender
{
    Male,
    Female,
};

class Human
{
public:
    Human()
        : Human("", Male, 0)
    {}

    Human(const std::string& name, Gender gender, int age)
        : mName(name)
        , mGender(gender)
        , mAge(age)
    {}

    const std::string& name() const { return mName; }
    Gender gender() const { return mGender; }
    int age() const { return mAge; }

private:
    std::string mName;
    Gender mGender;
    int mAge;
};

// Predicates

bool is_female(const Human& human)
{
    return human.gender() == Gender::Female;
}

bool order_than(const Human& human, int age)
{
    return human.age() > age;    
}

template<typename Iter, typename Pred>
std::vector<std::string> names_for(Iter begin, Iter end, Pred pred)
{
    // return filter(humans, is_female);
    std::vector<Human> females(humans.size());
    const auto last = std::copy_if(begin, end, females.begin(), std::forward<Pred>(pred));

    std::vector<std::string> names(std::distance(females.begin(), last));
    std::transform(females.begin(), last, names.begin(), [](const Human& human){ return human.name(); });

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

int main()
{
    std::string s{"  Hello world  !  "};
    std::cout << trim(s) << std::endl;

    using namespace std::placeholders;

    const std::vector<Human> humans{
        Human{"Nihao",Male, 12},
        Human{"Abc",Female, 46},
        Human{"VHG",Male, 14},
        Human{"HAH",Male, 68},
        Human{"W2V",Female, 52},
        Human{"HAV",Female, 23},
        Human{"ANH",Male, 27},
        Human{"AHE",Female, 37},
        Human{"DH",Male, 47},
        Human{"DCV",Male, 12},
        Human{"DHW",Male, 76},
        Human{"TH",Female, 3},
        Human{"SJH",Male, 7},
        Human{"HTR",Female, 45},
    };

    for(const auto& name: names_for(humans.cbegin(), humans.cend(), std::bind(order_than, _1, 30))) {
        std::cout << name << std::endl;
    }

    return 0;
}
