#include <iostream>
#include <vector>
#include <string>
#include <cstring>

class CommandLineOption
{
public:
    CommandLineOption(const std::string &name, const std::string &description);

    void set_short_name(char name);
    void set_long_name(const std::string &name);
    void set_value(const std::string &name, const std::string &default_value = std::string{});
};

class CommandLineOptionCategory
{
public:
    CommandLineOptionCategory(const std::string &name);

    void add_option(const CommandLineOption &option);
};

class CommandLineApp
{
public:
    CommandLineApp(int argc, char *argv[])
    {
        for (auto i = 0; i < argc; ++i) {
            const auto len = std::strlen(argv[i]);
            if (len == 1) {
                // error
            } else if (len >= 2) {
                if (argv[i][0] == '-') {
                    if (argv[i][1] == '-') {
                        if (len == 2) {
                            // ignore
                        } else {
                            // option - long name
                        }
                    } else {
                        // option - short name
                    }
                } else {
                    // command
                }
            }
        }
    }

    void add_option(const CommandLineOption &option);
    void add_category(const CommandLineOptionCategory &category);

    void set_description(const std::string &desc);

    void parse()
    {

    }

private:
    std::vector<std::string> m_args;
};

// cman <command> [options] [arguments]
// cman <options> [values] [arguments]
int main(int argc, char *argv[]) {
    auto app = CommandLineApp(argc, argv);

    // CommandLineOption newOpt{"new", "Create a new project."};
    // newOpt.set_value("project");
    // default category - OPTIONS
    // app.add_option(newOpt);

    app.parse();
}
