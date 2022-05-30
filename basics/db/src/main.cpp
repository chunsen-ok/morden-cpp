#include <cstdio>
#include <iostream>
#include <sqlite/sqlite3.h>
#include <orm/query_builder.hpp>

namespace {

constexpr char create_sql[] = R"(
CREATE TABLE IF NOT EXISTS contacts (
  tp INT4 NOT NULL,
  uid INT8 NOT NULL,
  name TEXT,
  UNIQUE(tp, uid)
);
)";

constexpr char insert_sql[] = R"(
INSERT INTO contacts VALUES (1,1,'Abc'),(1,2,'Az'),(1,3,'Ab');
)";

}

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
    int i;
    for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int run_sqlite()
{
    sqlite3 *db{nullptr};
    char *zErrMsg{nullptr};
    int rc{0};

    rc = sqlite3_open("data.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // create table
    rc = sqlite3_exec(db, create_sql, callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // insert rows
    rc = sqlite3_exec(db, insert_sql, callback, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);

    return 0;
}

int main() {
    DbTable table("account");
    table.add_column(DbColumn("uid", "INT4"));
    table.set_pkeys({"uid"});
    table.migrate();
}
