
//yousseflaamim
#include "LibraryManagement.h"
#include <iostream>

LibraryManagement::LibraryManagement() : libraryOperations(db) {} // Constructor initialization list

void LibraryManagement::initialize() {
    db.initialize(); 

    while (true) {
        std::cout << "\nLibrary Management System\n";
        std::cout << "1. Register\n";
        std::cout << "2. Login\n";
        std::cout << "3. Library Operations\n"; 
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";

        int mainChoice;
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1: {
                std::string username, password;
                std::cout << "Enter new username: ";
                std::cin >> username;
                std::cout << "Enter new password: ";
                std::cin >> password;

                if (db.registerUser(username, password)) {
                    std::cout << "Registration successful. You can now login." << std::endl;
                } else {
                    std::cout << "Registration failed. Please try again." << std::endl;
                }
                break;
            
            }
            case 2: {
                std::string username, password;
                std::cout << "Enter username: ";
                std::cin >> username;
                std::cout << "Enter password: ";
                std::cin >> password;

                if (db.loginUser(username, password)) {
                    std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
                    libraryOperations.showMenu(); 
                } else {
                    std::cout << "Login failed. Invalid username or password." << std::endl;
                }
                break;
            }
            case 3: {
                
                libraryOperations.showMenu();
                break;
            }
            case 4: {
                db.close(); 
                return;
            }
            default:
                std::cout << "Invalid option. Please try again.\n";
        }
    }
}
