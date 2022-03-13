#include <iostream>
#include <string>

template<int R, typename T>
class Data
{
public:
    void reset(const T &data) { inner = data; }
    void reset(T &&data) { inner = std::move(data); }

    const T &operator*() const { return inner; }
    
private:
    T inner;
};

enum Role {
    None = 0,
    PackageName,
    PackageVersion,
    PackageAuthors,
    PackageDesc,
    
    Language,
    LanguageType,
    LanguageVersion,
    
    Dependencies,
};

class LangConfig
{
public:

private:
    Data<LanguageType, std::string> m_type;
    Data<LanguageVersion, std::string> m_version;
};

class PackageConfig
{
public:

private:
    Data<PackageName, std::string> m_name;
    Data<PackageVersion, std::string> m_version;
    Data<PackageAuthors, std::string> m_authors;
    Data<PackageDesc, std::string> m_desc;
    Data<Language, LangConfig> m_lang;
};

class JsonWriter
{
public:

};

int main() {
    PackageConfig config;
    return 0;
}
