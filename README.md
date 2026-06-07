# Лабораторна робота №1 — Бібліотека (C++, ООП)

Система керування бібліотекою з використанням класів, наслідування, поліморфізму та роботи з файлами.

## Ієрархія класів

- `Book` — базова книга
- `EBook` — електронна книга
- `SpecialEditionEBook` — спеціальне видання електронної книги
- `User` — абстрактний користувач
- `Reader` — читач бібліотеки
- `Loan` — запис про видачу
- `Library` — бібліотека

## Складання

```bash
g++ -std=c++17 main.cpp src/Book.cpp src/User.cpp src/Loan.cpp src/Library.cpp -o lab1
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
