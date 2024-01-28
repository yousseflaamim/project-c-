#include "Database.h"
sqlite3* db;

Database::Database() {
    int rc = sqlite3_open("library.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }

    const char* booksTableSql = "CREATE TABLE IF NOT EXISTS books ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "title TEXT NOT NULL,"
                                "author TEXT NOT NULL,"
                                "genre TEXT,"
                                "status TEXT NOT NULL)";

    rc = sqlite3_exec(db, booksTableSql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create books table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
/////////table user
    const char* usersTableSql = "CREATE TABLE IF NOT EXISTS users ("
                                "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                "username TEXT NOT NULL,"
                                "password TEXT NOT NULL)";

    rc = sqlite3_exec(db, usersTableSql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't create users table: " << sqlite3_errmsg(db) << std::endl;
        exit(1);
    }
}


Database::~Database() {
     sqlite3_close(db);
}

void Database::initialize() {
}

void Database::close() {
   
    sqlite3_close(db);
}

bool Database::registerUser(const std::string& username, const std::string& password) {
     const char* sql = "INSERT INTO users (username, password) VALUES (?, ?)";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "User registered successfully." << std::endl;
    return true;
}


bool Database::loginUser(const std::string& username, const std::string& password) {
    const char* sql = "SELECT * FROM users WHERE username = ? AND password = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
        return true;
    } else {
        std::cout << "Login failed. Invalid username or password." << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);

}

void Database::displayBooks() {
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

bool Database::insertBook(const std::string& title, const std::string& author, const std::string& genre, const std::string& status) {
    const char* sql = "INSERT INTO books (title, author, genre, status) VALUES (?, ?, ?, ?)";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt); 
        return false;
    }

    sqlite3_finalize(stmt); 
    std::cout << "Book added successfully." << std::endl;
    return true;
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
bool Database::deleteBook(int bookId) {
    const char* sql = "DELETE FROM books WHERE id = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_int(stmt, 1, bookId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Book deleted successfully." << std::endl;
    return true;
}

bool Database::updateBook(int bookId, const std::string& title, const std::string& author, const std::string& genre, const std::string& status) {
    const char* sql = "UPDATE books SET title = ?, author = ?, genre = ?, status = ? WHERE id = ?";
    sqlite3_stmt* stmt;

    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, author.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, genre.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 5, bookId);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        std::cerr << "Execution failed: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_finalize(stmt);
    std::cout << "Book updated successfully." << std::endl;
    return true;
}

int Database::callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    return 0;
}

