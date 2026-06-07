# Лабораторна робота №1 — Бібліотека (C++, ООП)

Система керування бібліотекою з використанням класів, наслідування, поліморфізму та роботи з файлами.

## UML-діаграма класів

```mermaid
classDiagram
    class Book {
        -title: string
        -author: string
        -isbn: string
        -year: int
        -totalCopies: int
        +Book(t, a, i, y, copies)
        +getTitle() string
        +getAuthor() string
        +getISBN() string
        +getYear() int
        +getTotalCopies() int
        +displayInfo() void
        +getBorrowingCost() double
        +matchesTitle(q) bool
        +checkout() bool
        +checkin() void
        +isOldEdition(thresholdYear) bool
        +isAvailable() bool
    }

    class EBook {
        -downloadUrl: string
        -fileSizeMB: double
        +EBook(t, a, i, y, url, size)
        +getDownloadInfo() void
        +displayInfo() void
        +getBorrowingCost() double
    }

    class SpecialEditionEBook {
        -hasBonusContent: bool
        +SpecialEditionEBook(t, a, i, y, url, size, bonus)
        +displayInfo() void
        +getBorrowingCost() double
    }

    class User {
        #name: string
        #id: string
        #email: string
        +User(n, i, e)
        +displayInfo() void*
        +notify(message) void
        +getId() string
    }

    class Reader {
        -borrowedIsbns: vector~string~
        +Reader(n, i, e)
        +displayInfo() void
        +borrow(isbn) bool
        +returnBook(isbn) bool
        +listBorrowed() void
    }

    class Loan {
        -loanId: string
        -bookIsbn: string
        -userId: string
        -loanDate: time_t
        -dueDate: time_t
        -returned: bool
        +Loan(lid, isbn, uid, loanD, dueD)
        +markReturned() void
        +isReturned() bool
        +isOverdue() bool
        +daysLeft() int
        +getISBN() string
        +getUserId() string
        +getLoanId() string
    }

    class Library {
        -books: vector~Book~
        -readers: vector~Reader~
        -loans: vector~Loan~
        +addBook(book) void
        +addReader(reader) void
        +findBookByISBN(isbn) Book*
        +findReaderById(id) Reader*
        +issueBook(isbn, readerId) bool
        +returnBook(isbn, readerId) bool
        +listBooks() void
        +listReaders() void
        +listLoans() void
    }

    Book <|-- EBook
    EBook <|-- SpecialEditionEBook
    User <|-- Reader
    Library --> Book
    Library --> Reader
    Library --> Loan
```

## Складання

```bash
g++ -std=c++17 main.cpp Book.cpp User.cpp Loan.cpp Library.cpp -o lab1
```

## Формат файлів

**books.txt**
```
Title;Author;ISBN;Year;Copies
The Lord of the Rings;J.R.R. Tolkien;1234567890;1954;3
```

**readers.txt**
```
Name;Id;Email
Danilo;U001;danilo@example.com
```

## Використання

```bash
./lab1
```
