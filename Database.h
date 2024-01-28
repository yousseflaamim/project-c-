#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>
#include "Book.h"

class Database {
public:
    Database();
    ~Database();
    void initialize();
    void close();
    bool registerUser(const std::string& username, const std::string& password);
    bool loginUser(const std::string& username, const std::string& password);
    void displayBooks();
    bool insertBook(const std::string& title, const std::string& author, const std::string& genre, const std::string& status);
    bool deleteBook(int bookId);
    bool updateBook(int bookId, const std::string& title, const std::string& author, const std::string& genre, const std::string& status);
private:
    sqlite3* db;
    static int callback(void* NotUsed, int argc, char** argv, char** azColName);
};

#endif
