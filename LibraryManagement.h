#pragma once

#include "Database.h"
#include "LibraryOperations.h"

class LibraryManagement {
public:
    LibraryManagement(); 
    void initialize();

private:
    Database db;
    LibraryOperations libraryOperations;
};
