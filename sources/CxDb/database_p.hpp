#ifndef MCPP_DATABASE_PRIVATE_H
#define MCPP_DATABASE_PRIVATE_H

#include <cppjieba/Jieba.hpp>
extern "C" {
#include <sqlite3.h>
}

const char* const DICT_PATH = "./build/extern/cppjieba/cppjieba-prefix/src/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "./build/extern/cppjieba/cppjieba-prefix/src/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "./build/extern/cppjieba/cppjieba-prefix/src/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "./build/extern/cppjieba/cppjieba-prefix/src/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "./build/extern/cppjieba/cppjieba-prefix/src/cppjieba/dict/stop_words.utf8";

namespace mcpp {

class Database;
class DatabasePrivate
{
    Database* const p;
public:
    DatabasePrivate(Database* ptr)
        : p{ptr}
        , db{nullptr}
        , is_open{false}
        , result_code{SQLITE_OK}
        , chineseTokenizer{nullptr}
    {}

    inline int enable_fts5_chinese_tokenizer();

    sqlite3* db;
    bool is_open;
    int result_code;
    std::unique_ptr<cppjieba::Jieba> chineseTokenizer;
};

static fts5_api* fts5_api_from_db(sqlite3 *db)
{
    fts5_api *pRet = 0;
    sqlite3_stmt *pStmt = 0;

    if (SQLITE_OK == sqlite3_prepare(db, "SELECT fts5(?1)", -1, &pStmt, 0)) {
        sqlite3_bind_pointer(pStmt, 1, (void *)&pRet, "fts5_api_ptr", NULL);
        sqlite3_step(pStmt);
    }
    sqlite3_finalize(pStmt);
    return pRet;
}

static int fts5_create_tokenizer(void* ctx, const char* argv[], int argc, Fts5Tokenizer* out[])
{
    auto d = reinterpret_cast<DatabasePrivate*>(ctx);
    for (auto i = 0; i < argc; ++i) {
        std::printf("arg: %s\n", argv[i]);
    }

    if (!d->chineseTokenizer) {
        d->chineseTokenizer.reset(new cppjieba::Jieba{
            DICT_PATH,
            HMM_PATH,
            USER_DICT_PATH,
            IDF_PATH,
            STOP_WORD_PATH
        });
    }
    
    *out = reinterpret_cast<Fts5Tokenizer*>(d->chineseTokenizer.get());

    return SQLITE_OK;
}

static void fts5_delete_tokenizer(Fts5Tokenizer* tokenizer)
{
    std::cout << "Delete tokenizer\n";
}

static int fts5_tokenize(Fts5Tokenizer* tokenizer, void* ctx, int flags, const char* text, int size, int(*tokenize)(void*, int, const char*, int, int, int))
{
    std::cout << "tokenize: " << flags << text << size << std::endl;
    
    cppjieba::Jieba* jt = reinterpret_cast<cppjieba::Jieba*>(tokenizer);
    if (!jt) {
        return SQLITE_ERROR;
    }

    std::vector<std::string> words;
    jt->Cut(std::string(text, size), words, true);

    int offset = 0;
    for (const auto& token: words) {
        int s = token.size();
        std::cout << "tttt:" << token << std::endl;
        tokenize(ctx, 0, token.c_str(), token.size(), offset, offset + s);
        offset += s;
    }
    
    return SQLITE_OK;
}

int DatabasePrivate::enable_fts5_chinese_tokenizer()
{   
    if (fts5_api* fts = fts5_api_from_db(db); fts) {
        fts5_tokenizer chinese_tokenizer;
        chinese_tokenizer.xCreate = &fts5_create_tokenizer;
        chinese_tokenizer.xTokenize = &fts5_tokenize;
        chinese_tokenizer.xDelete = &fts5_delete_tokenizer;
        return fts->xCreateTokenizer(fts, "chinese_tokenizer", this, &chinese_tokenizer, nullptr);
    }
    return SQLITE_ERROR;
}

}

#endif
