# Лабораторна робота №1 — Бібліотека (C++, ООП)

Система керування бібліотекою з використанням класів, наслідування, поліморфізму та роботи з файлами.

## Все типи UML-діаграм

### 1. Діаграма класів (Class Diagram)

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
        +getDownloadInfo() void
        +displayInfo() void
        +getBorrowingCost() double
    }
    class SpecialEditionEBook {
        -hasBonusContent: bool
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
        +addReader(reader) void
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

### 2. Діаграма послідовності (Sequence Diagram)

```mermaid
sequenceDiagram
    actor U as Користувач
    participant L as Library
    participant B as Book
    participant R as Reader
    participant LN as Loan

    U->>L: issueBook(isbn, readerId)
    L->>B: findBookByISBN(isbn)
    B-->>L: Book*
    L->>R: findReaderById(readerId)
    R-->>L: Reader*
    alt книга доступна
        L->>B: isAvailable()
        B-->>L: true
        L->>R: borrow(isbn)
        R-->>L: true
        L->>B: checkout()
        L->>LN: Loan(loanId, isbn, userId, loanDate, dueDate)
        LN-->>L: Loan*
        L-->>U: "Книга видана"
    else книга не знайдена
        L-->>U: "Книга не знайдена"
    else читач не знайдений
        L-->>U: "Читач не знайдений"
    else немає в наявності
        L-->>U: "Книга не доступна"
    end
```

### 3. Діаграма варіантів використання (Use Case Diagram)

```mermaid
graph LR
    subgraph "Система бібліотеки"
        UC1[Додати книгу]
        UC2[Додати читача]
        UC3[Видати книгу]
        UC4[Повернути книгу]
        UC5[Переглянути список книг]
        UC6[Переглянути список читачів]
        UC7[Переглянути історію позик]
    end

    Admin[Адміністратор] --> UC1
    Admin --> UC2
    Admin --> UC3
    Admin --> UC4
    Admin --> UC5
    Admin --> UC6
    Admin --> UC7

    UC3 -->|використовує| Loan[Loan сервіс]
    UC4 -->|використовує| Loan
    Loan --> Books[Книги]
    Loan --> Readers[Читачі]
```

### 4. Діаграма активності (Activity Diagram)

```mermaid
graph TD
    Start([Початок]) --> Input[Введення ISBN та Reader ID]
    Input --> FindBook{Книга знайдена?}
    FindBook -->|Ні| Err1[Повідомлення: книга не знайдена]
    FindBook -->|Так| FindReader{Читач знайдений?}
    FindReader -->|Ні| Err2[Повідомлення: читач не знайдений]
    FindReader -->|Так| CheckAvail{Книга доступна?}
    CheckAvail -->|Ні| Err3[Повідомлення: немає в наявності]
    CheckAvail -->|Так| CheckBorrow{Читач вже взяв?}
    CheckBorrow -->|Так| Err4[Повідомлення: вже взято]
    CheckBorrow -->|Ні| Issue[Видача: checkout + Loan + notify]
    Issue --> End([Кінець])
    Err1 --> End
    Err2 --> End
    Err3 --> End
    Err4 --> End
```

### 5. Діаграма станів (State Diagram)

```mermaid
stateDiagram-v2
    [*] --> Available
    Available --> Borrowed: checkout()
    Borrowed --> Available: returnBook() / checkin()
    Borrowed --> Overdue: dueDate expired
    Overdue --> Available: returnBook() + fine
    Available --> [*]
```

### 6. Діаграма компонент (Component Diagram)

```mermaid
graph LR
    subgraph "Frontend"
        UI[Console UI / main.cpp]
    end

    subgraph "Core"
        Lib[Library]
        BM[BookManager]
        RM[ReaderManager]
        LM[LoanManager]
    end

    subgraph "Models"
        B[Book / EBook / SEBook]
        R[Reader]
        L[Loan]
    end

    subgraph "Storage"
        F1[books.txt]
        F2[readers.txt]
    end

    UI --> Lib
    Lib --> BM
    Lib --> RM
    Lib --> LM
    BM --> B
    RM --> R
    LM --> L
    BM --> F1
    RM --> F2
```

### 7. Діаграма розгортання (Deployment Diagram)

```mermaid
graph TB
    subgraph "Користувацький комп'ютер"
        App[lab1.exe]
        FS[Файлова система]
    end

    App -->|читає| FS
    App -->|записує| FS

    subgraph "Система"
        OS[Windows / Linux]
        GPP[G++ Compiler]
        STD[C++17 Runtime]
    end

    App -->|компілюється| GPP
    GPP -->|потребує| STD
    STD -->|залежить від| OS
```

### 8. Діаграма пакетів (Package Diagram)

```mermaid
graph LR
    subgraph "lab1"
        subgraph "src/"
            M[main.cpp]
            BH[Book.h / Book.cpp]
            UH[User.h / User.cpp]
            LH[Loan.h / Loan.cpp]
            LibH[Library.h / Library.cpp]
        end
        subgraph "data/"
            DB[books.txt]
            DR[readers.txt]
        end
        subgraph "diagrams/"
            DC[Class Diagram]
            DA[Activity Diagram]
            DS[Sequence Diagram]
            DU[Use Case Diagram]
            DD[Deployment Diagram]
            DSt[State Diagram]
            DCo[Component Diagram]
            DP[Package Diagram]
            DO[Object Diagram]
        end
        README[README.md]
    end

    M --> BH
    M --> UH
    M --> LH
    M --> LibH
    LibH --> BH
    LibH --> UH
    LibH --> LH
```

### 9. Діаграма об'єктів (Object Diagram)

```mermaid
graph LR
    subgraph "Об'єкти в пам'яті"
        B1[Book: LOTR, isbn=123, copies=3]
        B2[Book: HP, isbn=234, copies=2]
        R1[Reader: U001, Danilo]
        R2[Reader: U002, Ivan]
        L1[Loan: L1, ISBN=123, Reader=U001]
        Lib[Library: 5 books, 5 readers, 1 loan]
    end

    Lib --> B1
    Lib --> B2
    Lib --> R1
    Lib --> R2
    Lib --> L1
    L1 --> B1
    L1 --> R1
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

Додаткові діаграми: див. папки `Class Diagram/`, `Sequence Diagram/`, `Activity Diagram/`, `Use Case/`.
