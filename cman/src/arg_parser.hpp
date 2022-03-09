#ifndef ARG_PARSER_HPP
#define ARG_PARSER_HPP

#include <string>
#include <vector>
#include <iomanip>
#include <iostream>

class Arg
{
public:
    Arg(const std::string &name, const std::string &description = std::string{}, const std::string &value = std::string{})
        : m_name(name), m_desc(description), m_value(value) {}

    const std::string &name() const { return m_name; }
    const std::string &desc() const { return m_desc; }
    const std::string &value() const { return m_value; }

    std::size_t name_value_length() const {
        // --<name>
        auto len = 2 + m_name.length();
        if (!m_value.empty()) {
            // --<name> <value>
            len += 1 + m_value.length();
        }
        return len;
    }

    static void showHelp(const Arg &arg, int name_value_width)
    {
        std::cout << "    " << std::setw(name_value_width + 4) << std::left;
        if (!arg.value().empty()) {
            std::cout << (std::string("--") + arg.name() + " <" + arg.value() + ">");
        } else {
            std::cout << std::string("--") + arg.name();
        }
        std::cout << arg.desc() << std::endl;
    }

private:
    std::string m_name;
    std::string m_desc;
    std::string m_value;
};

struct ArgWrap {
    bool found;
    Arg arg;
};

template<typename T>
class ArgContainer
{
public:
    ArgContainer(const std::string &name, const std::string &desc)
        : m_name(name), m_desc(desc) {}

    const std::string &name() const { return m_name; }
    const std::string &desc() const { return m_desc; }

    T &add_arg(const Arg &arg) {
        m_args.push_back(ArgWrap{false, arg});
        return static_cast<T&>(*this);
    }

    bool is_set(const std::string &name) const {
        for (const auto &wrap: m_args) {
            if (wrap.found && wrap.arg.name() == name) {
                return true;
            }
        }
        return false;
    }

    virtual void parse(int argc, char *argv[]) {
        for (int i = argc; i < argc; ++i) {
            const char *arg = argv[i];
            const auto len = std::strlen(arg);
            if (arg[0] == '-' && len == 1) {
                // standard io
                // ...
            } else if (std::strcmp(arg, "--") == 0) {
                // option finished
                // ...
            } else if (arg[0] == '-') {
                // options
                if (arg[1] == '-') {
                    // long options
                    const auto arg_name = std::string(&arg[2]);
                    auto it = std::find_if(m_args.begin(), m_args.end(), [arg_name](const ArgWrap &arg){
                        return arg.arg.name() == arg_name;
                    });
                    if (it != m_args.end()) {
                        it->found = true;
                    }
                } else {
                    // short options
                    // ...
                }
            } else {
                // values
                // ...
            }
        }
    }


protected:
    std::string m_name;
    std::string m_desc;
    std::vector<ArgWrap> m_args;
};

class Command: public ArgContainer<Command>
{
public:
    Command(const std::string &name, const std::string &desc)
        : ArgContainer<Command>(name, desc) {}

    virtual void showHelp() const {
        std::cout << desc() << '\n' << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "    " << name();

        if (m_args.size() > 0) {
            std::cout << " [OPTIONS]\n" << std::endl;
        }

        std::size_t len = 0;
        for (const auto &arg: m_args) {
            len = std::max(arg.arg.name_value_length(), len);
        }

        for (const auto &arg: m_args) {
            Arg::showHelp(arg.arg, len);
        }
    }

protected:
    std::string m_name;
    std::string m_desc;
    std::vector<ArgWrap> m_args;
};

struct CommandWrap {
    bool found;
    Command cmd;
};

class App: public ArgContainer<App>
{
public:
    App(const std::string &name, const std::string &desc)
        : ArgContainer<App>(name, desc) {}

    App &add_command(const Command &cmd) {
        m_cmds.push_back(CommandWrap{false, cmd});
        return *this;
    }

    void parse(int argc, char *argv[]) override {
        for (int i = 1; i < argc; ++i) {
            const char *arg = argv[i];
            const auto len = std::strlen(arg);

            if (i == 1 && arg[0] != '-') {
                // commands
                const auto cmd_name = std::string(arg);
                auto it = std::find_if(m_cmds.begin(), m_cmds.end(), [cmd_name](const CommandWrap &wrap){
                    return wrap.cmd.name() == cmd_name;
                });
                if (it != m_cmds.end()) {
                    it->found = true;
                    it->cmd.parse(argc - 1, &argv[1]);
                    break;
                }
            }
            
            if (arg[0] == '-' && len == 1) {
                // standard io
                // ...
            } else if (std::strcmp(arg, "--") == 0) {
                // option finished
                // ...
            } else if (arg[0] == '-') {
                // options
                if (arg[1] == '-') {
                    // long options
                    const auto arg_name = std::string(&arg[2]);
                    auto it = std::find_if(m_args.begin(), m_args.end(), [arg_name](const ArgWrap &arg){
                        return arg.arg.name() == arg_name;
                    });
                    if (it != m_args.end()) {
                        it->found = true;
                    }
                } else {
                    // short options
                    // ...
                }
            } else {
                // values
                // ...
            }
        }
    }

    void showHelp() const {
        std::cout << desc() << '\n' << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "    " << name();

        if (m_args.size() > 0) {
            std::cout << " [OPTIONS]";
        }

        if (m_cmds.size() > 0) {
            std::cout << " [COMMAND]";
        }

        std::cout << std::endl;

        std::size_t len{0};
        for (const auto &wrap: m_args) {
            len = std::max(wrap.arg.name_value_length(), len);
        }

        if (m_args.size() > 0) {
            std::cout << "\nOptions:\n";
        }

        for (const auto &arg: m_args) {
            Arg::showHelp(arg.arg, len);
        }

        len = 0;
        for (const auto &cmd: m_cmds) {
            len = std::max(cmd.cmd.name().size(), len);
        }

        if (m_cmds.size() > 0) {
            std::cout << "\nCommands:\n";
        }

        for (const auto &cmd: m_cmds) {
            std::cout << "    " << std::setw(len + 4) << std::left << cmd.cmd.name() << cmd.cmd.desc() << std::endl;
        }
    }

private:
    std::vector<CommandWrap> m_cmds;
};

#endif
