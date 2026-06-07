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
        +displayInfo() void
        +checkout() bool
        +checkin() void
        +isAvailable() bool
        +matchesTitle(q) bool
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
        +displayInfo() void*
        +notify(message) void
        +getId() string
    }

    class Reader {
        -borrowedIsbns: vector~string~
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
        +markReturned() void
        +isOverdue() bool
        +daysLeft() int
    }

    class Library {
        -books: vector~Book~
        -readers: vector~Reader~
        -loans: vector~Loan~
        +addBook(book) void
        +issueBook(isbn, readerId) bool
        +returnBook(isbn, readerId) bool
        +listBooks() void
        +listLoans() void
    }

    Book <|-- EBook
    EBook <|-- SpecialEditionEBook
    User <|-- Reader
    Library --> Book
    Library --> Reader
    Library --> Loan
```

## UML-діаграма послідовності (видача книги)

```mermaid
sequenceDiagram
    participant U as Користувач/Студент
    participant L as Library
    participant B as Book
    participant R as Reader
    participant LN as Loan

    U->>L: issueBook(isbn, readerId)
    L->>B: findBookByISBN(isbn)
    B-->>L: Book*
    L->>R: findReaderById(readerId)
    R-->>L: Reader*
    L->>B: isAvailable()
    B-->>L: true
    L->>R: borrow(isbn)
    R-->>L: true
    L->>B: checkout()
    B-->>L: копія зменшено
    L->>LN: створити Loan(...)
    LN-->>L: Loan*
    L-->>U: "Книга видана"
```

## UML-діаграма варіантів використання (Use Case)

```mermaid
graph LR
    A[Адміністратор] --> UC1[Керування книгами]
    A --> UC2[Керування читачами]
    A --> UC3[Реєстрація видачі]
    A --> UC4[Реєстрація повернення]
    A --> UC5[Перегляд звітів]

    UC3 --> B[Система]
    UC4 --> B
    B --> C[Запис у журнал Loan]

    UC1 --> D[Додавання/видалення книги]
    UC2 --> E[Реєстрація читача]
    UC5 --> F[Список книг/читачів/позик]
```

## Діаграма активності (робота системи)

```mermaid
graph TD
    Start([Початок]) --> Input[Введення даних: ISBN та Reader ID]
    Input --> FindBook{Книга знайдена?}
    FindBook -->|Ні| ErrorBook[Повідомлення: книга не знайдена]
    FindBook -->|Так| FindReader{Читач знайдений?}
    FindReader -->|Ні| ErrorReader[Повідомлення: читач не знайдений]
    FindReader -->|Так| CheckAvail{Книга доступна?}
    CheckAvail -->|Ні| ErrorAvail[Повідомлення: немає в наявності]
    CheckAvail -->|Так| Issue[Видача: checkout + Loan + notify]
    Issue --> End([Кінець])
    ErrorBook --> End
    ErrorReader --> End
    ErrorAvail --> End
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

Додаткові UML-діаграми: див. папки `Class Diagram/`, `Sequence Diagram/`, `Activity Diagram/`, `Use Case/`.
