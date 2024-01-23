
#include "database.h"

void initializeDatabase() {
    int rc = sqlite3_open("library.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS books ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                      "title TEXT NOT NULL,"
                      "author TEXT NOT NULL,"
                      "genre TEXT,"
                      "status TEXT NOT NULL)";
    
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}

void closeDatabase() {
    sqlite3_close(db);
}
