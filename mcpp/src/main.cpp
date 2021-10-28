/// mcpp - modern cpp project build, pack, doc tool, dependency manager.
/// 
/// mcpp [OPTIONS] [SUBCOMMAND]
/// e.g.
///   mcpp -h, --help
///   mcpp --build
///   mcpp --run
///   mcpp --pack
///   mcpp --update
#include <iostream>

class AppOption
{
public:
};


class AppArg
{
public:
};


class ParseResult
{
public:

};

class App
{
public:
    App(int argc, char *argv[]);   

    void set_version();
    void set_author();
    void set_about();

    void add_option();

    ParseResult parse();

private:

};

int main(int argc, char *argv[]) {
    App app(argc, argv);
    app.add_option();
    auto parse = app.parse();
}
