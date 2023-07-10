#include "fts5_chinese_tokenizer.hpp"
#include <iostream>

namespace mcpp {

fts5_api* fts5_api_from_db(sqlite3 *db)
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

int enable_fts5_chinese_tokenizer(sqlite3* db)
{
    if (fts5_api* fts = fts5_api_from_db(db); fts) {
        fts5_tokenizer chinese_tokenizer;
        chinese_tokenizer.xCreate = &fts5_create_tokenizer;
        chinese_tokenizer.xTokenize = &fts5_tokenize;
        chinese_tokenizer.xDelete = &fts5_delete_tokenizer;
        return fts->xCreateTokenizer(fts, "chinese_tokenizer", nullptr, &chinese_tokenizer, nullptr);
    }
    return SQLITE_ERROR;
}

int fts5_create_tokenizer(void* ctx, const char* argv[], int argc, Fts5Tokenizer* out[])
{
    std::cout << "create tokenizer\n";
    for (auto i = 0; i < argc; ++i) {
        std::printf("arg: %s\n", argv[i]);
    }

    return SQLITE_OK;
}

void fts5_delete_tokenizer(Fts5Tokenizer* tokenizer)
{

}

int fts5_tokenize(Fts5Tokenizer* tokenizer, void* ctx, int flags, const char* text, int size, int(*tokenize)(void*, int, const char*, int, int, int))
{
    return SQLITE_OK;
}

}
