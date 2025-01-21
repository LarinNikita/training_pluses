#ifndef BOOK_H
#define BOOK_H

#include <iostream>

// Прототип strCopy
inline char* strCopy(const char* str);

class Book {
    protected:
        char* title;
        char* author;

    public:
        Book();
        Book(const Book& other);
        Book(const char* title, const char* author);
        virtual ~Book();

        const char* getTitle() const;
        const char* getAuthor() const;
        void setTitle(const char* title);
        void setAuthor(const char* author);

        friend std::ostream& operator<<(std::ostream& os, const Book& book);
        Book& operator=(const Book& other);
};

#endif
    