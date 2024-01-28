// yousseflaamim
#ifndef LIBRARY_OPERATIONS_H
#define LIBRARY_OPERATIONS_H

#include "Database.h"

class LibraryOperations {
public:
    LibraryOperations(Database& db); 
    void showMenu(); 
    void addBook(); 
    void displayBooks(); 
    void deleteBook(); 
    void updateBook(); 
private:
    Database& database; 
};

#endif 