#include "Library.h"
#include "Book.h"
#include "User.h"
#include "Loan.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <memory>

Book* parseBookLine(const std::string& line) {
    std::stringstream ss(line);
    std::string title, author, isbn, yearStr, copiesStr;
    std::getline(ss, title, ';');
    std::getline(ss, author, ';');
    std::getline(ss, isbn, ';');
    std::getline(ss, yearStr, ';');
    std::getline(ss, copiesStr, ';');
    int year = std::stoi(yearStr);
    int copies = std::stoi(copiesStr);
    return new Book(title, author, isbn, year, copies);
}

int main() {
    Library lib;
    std::ifstream booksFile("books.txt");
    std::string line;
    while (std::getline(booksFile, line)) {
        if (line.empty()) continue;
        lib.addBook(*parseBookLine(line));
    }
    booksFile.close();

    std::ifstream readersFile("readers.txt");
    std::string rName, rId, rEmail;
    while (std::getline(readersFile, rName, ';') && std::getline(readersFile, rId, ';') && std::getline(readersFile, rEmail)) {
        lib.addReader(Reader(rName, rId, rEmail));
    }
    readersFile.close();

    lib.listBooks();
    lib.listReaders();

    std::string isbn, readerId;
    std::cout << "Enter ISBN to issue: ";
    std::getline(std::cin, isbn);
    std::cout << "Enter reader ID: ";
    std::getline(std::cin, readerId);
    lib.issueBook(isbn, readerId);

    std::cout << "Enter ISBN to return: ";
    std::getline(std::cin, isbn);
    std::cout << "Enter reader ID: ";
    std::getline(std::cin, readerId);
    lib.returnBook(isbn, readerId);

    lib.listLoans();
    return 0;
}
