
#ifndef LIBRARY_MANAGEMENT_H
#define LIBRARY_MANAGEMENT_H
#include "Book.h"
#include <string>


void initializeDatabase();
void insertBook(const std::string& title, const std::string& author, const std::string& genre, const std::string& status);
void displayBooks();
void deleteBook(int bookId);
void closeDatabase();

#endif 
