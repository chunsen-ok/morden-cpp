#include <iostream>
#include <string>
#include <memory>
#include <vector>

class Rule: public std::enable_shared_from_this<Rule> 
{
public:
    [[nodiscard]] static std::shared_ptr<Rule> create()
    {
        return std::shared_ptr<Rule>(new Rule{});
    }

protected:
    Rule(): std::enable_shared_from_this<Rule>{} {}
};

class Target: public std::enable_shared_from_this<Target>
{
public:
    [[nodiscard]] static std::shared_ptr<Target> create()
    {
        return std::shared_ptr<Target>(new Target{});
    }

    void add_source(const std::shared_ptr<Target> &source)
    {
        if (!source) {
            std::cerr << "Invalid source\n";
            return;
        }

        auto it = std::find(mDepends.cbegin(), mDepends.cend(), source);
        if (it == mDepends.cend()) {
            mDepends.push_back(source);
        }
    }

    void set_rule(const std::shared_ptr<Rule> &rule)
    {
        if (!rule) {
            std::cerr << "Invalid rule\n";
            return;
        }

        mRule = rule;
    }

    void build()
    {
        // ...
    }

protected:
    Target() = default;

private:
    std::vector<std::shared_ptr<Target>> mDepends;
    std::shared_ptr<Rule> mRule;
};

int main()
{
    auto a = Target::create();
    auto b = Target::create();
    a->add_source(b);

    a->build();
}
