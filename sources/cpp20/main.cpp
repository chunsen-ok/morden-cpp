#include <iostream>
#include <fstream>
#include <cstdio>
#include <sqlite3.h>

static const char* stories_table = R"(CREATE TABLE IF NOT EXISTS stories (
  id INTEGER PRIMARY KEY,
  text TEXT,
  extra BLOB
);)";

static int callback(void*, int argc, char* argv[], char* colName[])
{
    return 0;
}

static fts5_api* fts5_api_from_db(sqlite3 *db)
{
    fts5_api *pRet = 0;
    sqlite3_stmt *pStmt = 0;

    if (SQLITE_OK == sqlite3_prepare(db, "SELECT fts5(?1)", -1, &pStmt, 0)) {
        sqlite3_bind_pointer(pStmt, 1, (void*)&pRet, "fts5_api_ptr", NULL);
        sqlite3_step(pStmt);
    }

    sqlite3_finalize(pStmt);
    
    return pRet;
}

static int create_tokenizer(void*, const char* argv[], int argc, Fts5Tokenizer* out[])
{
    std::printf("Create tokenizer\n");
    return SQLITE_OK;
}

static void delete_tokenizer(Fts5Tokenizer* tokenizer)
{
    std::printf("Delete tokenizer\n");
}

static int tokenize(Fts5Tokenizer* tokenizer, void* ctx, int flags, const char* text, int size, int(*xToken)(void*, int, const char*, int, int, int))
{
    std::printf("tokenizer\n");
    return SQLITE_OK;
}

int main(int argc, char* argv[])
{
    sqlite3* db;
    char* errMsg = nullptr;
    int rc;

    if (argc != 2) {
        std::printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }

    // std::fstream f;
    // f.open("F:\\laws.txt", std::ios_base::in);
    // if (!f.is_open()) {
    //     std::printf("Can't open law file\n");
    //     return 1;
    // }

    // std::string law((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>()); 

    rc = sqlite3_open(argv[1], &db);
    if (rc) {
        std::fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    fts5_tokenizer chinese_tokenizer;
    chinese_tokenizer.xCreate = &create_tokenizer;
    chinese_tokenizer.xTokenize = &tokenize;
    chinese_tokenizer.xDelete = &delete_tokenizer;
    if (fts5_api* fts = fts5_api_from_db(db); fts) {
        fts->xCreateTokenizer(fts, "chinese_tokenize", nullptr, &chinese_tokenizer, nullptr);
    }

    sqlite3_stmt* stmt;

    rc = sqlite3_prepare(db, "CREATE VIRTUAL TABLE raws_chinese_index USING fts5(id, text, tokenize='chinese_tokenize');", -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::fprintf(stderr, "Prepare error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }
    
    // rc = sqlite3_bind_text(stmt, 1, law.data(), -1, SQLITE_STATIC);
    // if (rc != SQLITE_OK) {
    //     std::fprintf(stderr, "Bind error: %s\n", sqlite3_errmsg(db));
    //     sqlite3_finalize(stmt);
    //     sqlite3_close(db);
    //     return 1;
    // }

    do {
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            const unsigned char* text = sqlite3_column_text(stmt, 0);
            std::printf("text: %s\n", text);
        }
    } while (rc == SQLITE_ROW);
    
    if (rc != SQLITE_DONE) {
        std::fprintf(stderr, "Step result code: %d, extend code: %d, error: %s\n", rc, sqlite3_extended_errcode(db), sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
