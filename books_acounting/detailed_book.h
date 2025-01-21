#ifndef DETAILED_BOOK_H
#define DETAILED_BOOK_H

#include "book.h"

class DetailedBook : public Book {
private:
    char* publisher;
    int year;
    char* isbn;

public:
    DetailedBook();
    DetailedBook(const DetailedBook& other);
    DetailedBook(const char* title, const char* author, const char* publisher, int year, const char* isbn);
    ~DetailedBook() override;

    const char* getPublisher() const;
    int getYear() const;
    const char* getIsbn() const;
    void setPublisher(const char* publisher);
    void setYear(int year);
    void setIsbn(const char* isbn);

    friend std::ostream& operator<<(std::ostream& os, const DetailedBook& book);
     DetailedBook& operator=(const DetailedBook& other);
};

#endif
