#include "database.h"

void initializeDatabase() {
    int rc = sqlite3_open("library.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }

    const char* booksTableSql = "CREATE TABLE IF NOT EXISTS books ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "title TEXT NOT NULL,"
                                "author TEXT NOT NULL,"
                                "genre TEXT,"
                                "status TEXT NOT NULL)";

    rc = sqlite3_exec(db, booksTableSql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create books table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
/////////table user
    const char* usersTableSql = "CREATE TABLE IF NOT EXISTS users ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "username TEXT NOT NULL,"
                                "password TEXT NOT NULL)";

    rc = sqlite3_exec(db, usersTableSql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create users table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}


void closeDatabase() {
    sqlite3_close(db);
}