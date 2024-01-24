#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <iostream>

extern sqlite3* db;

void initializeDatabase();
void closeDatabase();
bool registerUser(const std::string& username, const std::string& password);
bool loginUser(const std::string& username, const std::string& password);


#endif
