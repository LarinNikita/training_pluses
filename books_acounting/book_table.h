#ifndef BOOK_TABLE_H
#define BOOK_TABLE_H

#include "book.h"

class BookTable {
private:
    Book** books;
    int capacity;
    int count;

public:
    BookTable();
    ~BookTable();

    void addBook(Book* book);
    void removeBook(int index);
    void updateBook(int index, Book* newBook);
    int getCount() const;
    Book* operator[](int index) const;

    void print(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const BookTable& table);
};

#endif
