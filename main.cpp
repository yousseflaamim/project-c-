
#include <iostream>
#include "library_management.h"

int main() {
    initializeDatabase();

    while (true) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Exit\n";
        std::cout << "Choose an option: ";

        int mainChoice;
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin.ignore();
                std::getline(std::cin, username);

                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                if (registerUser(username, password)) {
                    std::cout << "Registration successful. You can now log in." << std::endl;
                } else {
                    std::cout << "Registration failed. Please try again." << std::endl;
                }
                break;
            }
            case 2: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin.ignore();
                std::getline(std::cin, username);

                std::cout << "Enter password: ";
                std::getline(std::cin, password);

                if (loginUser(username, password)) {
                    // User successfully logged in, proceed with library operations
                    while (true) {
                        std::cout << "\nLibrary Operations\n";
                        std::cout << "1. Add Book\n";
                        std::cout << "2. Display Books\n";
                        std::cout << "3. Delete Book\n";
                        std::cout << "4. updated Book\n";
                        std::cout << "5. Logout\n";
                        std::cout << "Choose an option: ";

                        int libraryChoice;
                        std::cin >> libraryChoice;

                        switch (libraryChoice) {
                            case 1: {
                                // Add Book operation
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
                                // Display Books operation
                                displayBooks();
                                break;
                            case 3: {
                                // Delete Book operation
                                int bookId;
                                std::cout << "Enter the ID of the book to delete: ";
                                std::cin >> bookId;

                                deleteBook(bookId);
                                break;
                            }
                             case 4: {
                                // Update Book operation
                                int bookId;
                                std::cout << "Enter the ID of the book to update: ";
                                std::cin >> bookId;

                                std::string title, author, genre, status;
                                std::cout << "Enter new book title: ";
                                std::cin.ignore();
                                std::getline(std::cin, title);

                                std::cout << "Enter new author name: ";
                                std::getline(std::cin, author);

                                std::cout << "Enter new genre (optional): ";
                                std::getline(std::cin, genre);

                                std::cout << "Enter new book status (read/unread): ";
                                std::getline(std::cin, status);

                                updateBook(bookId, title, author, genre, status);
                                break;
                            }
                            case 5:
                                std::cout << "Logging out..." << std::endl;
                                return 0; // Exit the program
                            default:
                                std::cout << "Invalid option. Please try again.\n";
                        }break;
                    }
                } else {
                    std::cout << "Login failed. Please check your username and password." << std::endl;
                }
                break;
            }
            case 3:
                closeDatabase();
                return 0; // Exit the program
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}