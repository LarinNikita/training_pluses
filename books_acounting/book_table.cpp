#include "book_table.h"
#include <iostream>

// Конструктор по умолчанию
BookTable::BookTable() : books(nullptr), capacity(0), count(0) {}

// Деструктор
BookTable::~BookTable() {
    for (int i = 0; i < count; ++i) {
        delete books[i];
    }
    delete[] books;
}

// Метод для добавления новой записи
void BookTable::addBook(Book* book) {
    if (count == capacity) {
        capacity = capacity == 0 ? 1 : capacity * 2;
        Book** newBooks = new Book*[capacity];
        for (int i = 0; i < count; ++i) {
            newBooks[i] = books[i];
        }
        delete[] books;
        books = newBooks;
    }
     books[count++] = book;
}

// Метод для удаления записи по номеру
void BookTable::removeBook(int index) {
   if (index >= 0 && index < count) {
        delete books[index];
       for (int i = index; i < count - 1; ++i) {
           books[i] = books[i + 1];
       }
       count--;
   }
}

// Метод для изменения существующей записи
void BookTable::updateBook(int index, Book* newBook) {
    if (index >= 0 && index < count) {
        delete books[index];
        books[index] = newBook;
    }
}

// Метод для получения количества записей
int BookTable::getCount() const { return count; }

// Перегруженный оператор индексирования
Book* BookTable::operator[](int index) const {
    if(index >= 0 && index < count) return books[index];
    return nullptr;
}


// Перегруженный оператор вывода
std::ostream& operator<<(std::ostream& os, const BookTable& table) {
    for(int i = 0; i < table.count; ++i) {
       os << i + 1 << ". " << *table.books[i] << std::endl;
    }
    return os;
}
