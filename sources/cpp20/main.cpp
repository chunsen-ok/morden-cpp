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

class CommandBuilder;
class Command
{
public:
    static CommandBuilder create();
    static CommandBuilder create(const std::string& name);

    void parse(int argc, char* argv[]);
};

class DocumentBuilder;
class Document
{
public:
    static DocumentBuilder create();
};

class DocumentBuilder
{
public:
    using Self = DocumentBuilder;

    Self& header();
    Self& body();
    Self& footer();

    operator Document ();
};

class CommandBuilder
{
public:
    using Self = CommandBuilder;

    Self& command(const Command& cmd);
    Self& doc(const Document& doc);

    operator Command ();
};

int main(int argc, char* argv[])
{
    Command app = Command::create()
    .command(
        Command::create("new")
    )
    .doc(
        Document::create()
        .header()
        .body()
        .footer()
    );

    app.parse(argc, argv);

    return 0;
}
