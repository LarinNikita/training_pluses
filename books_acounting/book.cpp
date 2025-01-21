#include "book.h"
#include <cstring>

// Вспомогательная функция для копирования строк в стиле C
    char* strCopy(const char* str) {
        if (!str) return nullptr;
        size_t len = strlen(str) + 1;
        char* newStr = new char[len];
        strcpy(newStr, str);
        return newStr;
    }

// Конструктор по умолчанию
Book::Book() : title(nullptr), author(nullptr) {}

// Конструктор копирования
Book::Book(const Book& other) : title(nullptr), author(nullptr) {
    if (other.title) title = strCopy(other.title);
    if (other.author) author = strCopy(other.author);
}

// Конструктор с параметрами
Book::Book(const char* title, const char* author) : title(nullptr), author(nullptr) {
    this->title = strCopy(title);
    this->author = strCopy(author);
}

// Деструктор
Book::~Book() {
    delete[] title;
    delete[] author;
}

// Методы для доступа к полям
const char* Book::getTitle() const { return title; }
const char* Book::getAuthor() const { return author; }

// Методы для установки значений полей
void Book::setTitle(const char* title) {
    delete[] this->title;
    this->title = strCopy(title);
}
void Book::setAuthor(const char* author) {
    delete[] this->author;
    this->author = strCopy(author);
}

// Перегруженный оператор вывода
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Title: " << (book.title ? book.title : "N/A") << ", Author: " << (book.author ? book.author : "N/A");
    return os;
}

// Перегруженный оператор присваивания
Book& Book::operator=(const Book& other) {
    if (this != &other) {
        delete[] title;
        delete[] author;

        title = nullptr;
        author = nullptr;

        if(other.title) title = strCopy(other.title);
        if(other.author) author = strCopy(other.author);
    }
    return *this;
}
