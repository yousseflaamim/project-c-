
#include <iostream>
#include "library_management.h"

int main() {
    initializeDatabase();

    while (true) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Display Books\n";
        std::cout << "3. Delete Book\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
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

                insertBook(title, author, genre, status);
                break;
            }
            case 2:
                displayBooks();
                break;
            case 3: {
                int bookId;
                std::cout << "Enter the ID of the book to delete: ";
                std::cin >> bookId;

                deleteBook(bookId);
                break;
            }
            case 4:
                closeDatabase();
                return 0;
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
