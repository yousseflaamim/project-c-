
#include <iostream>
#include <sqlite3.h>
#include "library_management.h"
#include "database.h"

sqlite3* db;


void insertBook(const std::string& title, const std::string& author, const std::string& genre, const std::string& status) {
    const char* sql = "INSERT INTO books (title, author, genre, status) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_finalize(stmt);
    std::cout << "Book added successfully." << std::endl;
}

void displayBooks() {
    const char* sql = "SELECT * FROM books";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    std::cout << "ID\tTitle\tAuthor\tGenre\tStatus" << std::endl;
    std::cout << "--------------------------------------" << std::endl;

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* author = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* genre = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));

        std::cout << id << "\t" << title << "\t" << author << "\t" << genre << "\t" << status << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
}
void deleteBook(int bookId) {
    const char* sql = "DELETE FROM books WHERE id = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_bind_int(stmt, 1, bookId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    sqlite3_finalize(stmt);
    std::cout << "Book deleted successfully." << std::endl;
}
