#include "detailed_book.h"
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
DetailedBook::DetailedBook() : publisher(nullptr), year(0), isbn(nullptr) {}

// Конструктор копирования
DetailedBook::DetailedBook(const DetailedBook& other) : Book(other), publisher(nullptr), year(other.year), isbn(nullptr) {
    if (other.publisher) publisher = strCopy(other.publisher);
    if (other.isbn) isbn = strCopy(other.isbn);
}

// Конструктор с параметрами
DetailedBook::DetailedBook(const char* title, const char* author, const char* publisher, int year, const char* isbn)
    : Book(title, author), publisher(nullptr), year(year), isbn(nullptr) {
    this->publisher = strCopy(publisher);
    this->isbn = strCopy(isbn);
}

// Деструктор
DetailedBook::~DetailedBook() {
    delete[] publisher;
    delete[] isbn;
}

// Методы для доступа к полям
const char* DetailedBook::getPublisher() const { return publisher; }
int DetailedBook::getYear() const { return year; }
const char* DetailedBook::getIsbn() const { return isbn; }

// Методы для установки значений полей
void DetailedBook::setPublisher(const char* publisher) {
    delete[] this->publisher;
    this->publisher = strCopy(publisher);
}
void DetailedBook::setYear(int year) { this->year = year; }
void DetailedBook::setIsbn(const char* isbn) {
    delete[] this->isbn;
    this->isbn = strCopy(isbn);
}

// Переопределенный виртуальный метод print
void DetailedBook::print(std::ostream& os) const {
    Book::print(os); // Вызываем метод print базового класса
    os << ", Publisher: " << (publisher ? publisher : "N/A")
       << ", Year: " << year << ", ISBN: " << (isbn ? isbn : "N/A");
}

 // Перегруженный оператор присваивания
DetailedBook& DetailedBook::operator=(const DetailedBook& other) {
    if (this != &other) {
        Book::operator=(other);
        delete[] publisher;
        delete[] isbn;
        publisher = nullptr;
        isbn = nullptr;

        year = other.year;
        if(other.publisher) publisher = strCopy(other.publisher);
        if(other.isbn) isbn = strCopy(other.isbn);
    }
    return *this;
}
