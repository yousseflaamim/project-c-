#include "LibraryManagement.h"

int main() {
     LibraryManagement* library = new LibraryManagement();
    library->initialize();
     delete library;
    return 0;
}
