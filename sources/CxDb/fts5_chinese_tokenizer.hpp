#ifndef MCPP_DB_FTS5_HPP
#define MCPP_DB_FTS5_HPP

#include <sqlite3.h>

namespace mcpp {

int enable_fts5_chinese_tokenizer(sqlite3* db);

int fts5_create_tokenizer(void* ctx, const char* argv[], int argc, Fts5Tokenizer* out[]);
void fts5_delete_tokenizer(Fts5Tokenizer* tokenizer);
int fts5_tokenize(Fts5Tokenizer* tokenizer, void* ctx, int flags, const char* text, int size, int(*tokenize)(void*, int, const char*, int, int, int));

}

#endif
