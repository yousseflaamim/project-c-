
#include "LibraryOperations.h"
#include <iostream>
LibraryOperations::LibraryOperations(Database& db) : database(db) {
    
  
}

void LibraryOperations::showMenu() {
    while (true) {
        std::cout << "\nLibrary Operations\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Display Books\n";
        std::cout << "3. Delete Book\n";
        std::cout << "4. Update Book\n";
        std::cout << "5. Logout\n";
        std::cout << "Choose an option: ";

        int libraryChoice;
        std::cin >> libraryChoice;

        switch (libraryChoice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                updateBook();
                break;
            case 5:
                std::cout << "Logging out..." << std::endl;
                return;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}

void LibraryOperations::addBook() {
   std::string title, author, genre, status;

    std::cout << "Enter book title: ";
    std::cin.ignore(); 
    std::getline(std::cin, title);

    std::cout << "Enter author name: ";
    std::getline(std::cin, author);

    std::cout << "Enter genre (optional): ";
    std::getline(std::cin, genre);

    std::cout << "Enter book status (read/unread): ";
    std::getline(std::cin, status);

    if (database.insertBook(title, author, genre, status)) {
        std::cout << "Book added successfully." << std::endl;
    } else {
        std::cerr << "Failed to add book. Please try again." << std::endl;
    }
}

void LibraryOperations::displayBooks() {
    std::cout << "Displaying books:" << std::endl;
    database.displayBooks();
}


void LibraryOperations::deleteBook() {
    int bookId;
    
    std::cout << "Enter the ID of the book you want to delete: ";
    std::cin >> bookId;

    if (database.deleteBook(bookId)) {
        std::cout << "Book deleted successfully." << std::endl;
    } else {
        std::cerr << "Failed to delete book. Please try again." << std::endl;
    }
}
void LibraryOperations::updateBook() {
    int bookId;
    std::string title, author, genre, status;
    
    std::cout << "Enter the ID of the book you want to update: ";
    std::cin >> bookId;

    std::cout << "Enter the updated title: ";
    std::cin.ignore(); 
    std::getline(std::cin, title);

    std::cout << "Enter the updated author: ";
    std::getline(std::cin, author);

    std::cout << "Enter the updated genre (optional): ";
    std::getline(std::cin, genre);

    std::cout << "Enter the updated status: ";
    std::getline(std::cin, status);

    if (database.updateBook(bookId, title, author, genre, status)) {
        std::cout << "Book updated successfully." << std::endl;
    } else {
        std::cerr << "Failed to update book. Please try again." << std::endl;
    }
}