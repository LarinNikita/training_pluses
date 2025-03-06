### Файл `book_table.h`

#### Определение класса `BookTable`

```cpp
#ifndef BOOK_TABLE_H
#define BOOK_TABLE_H

#include "book.h"

class BookTable {
private:
    Book** books; // Указатель на массив указателей на объекты типа Book
    int capacity; // Текущая вместимость массива
    int count;    // Количество книг в таблице

public:
    BookTable(); // Конструктор по умолчанию
    ~BookTable(); // Деструктор

    void addBook(Book* book); // Метод для добавления новой книги
    void removeBook(int index); // Метод для удаления книги по индексу
    void updateBook(int index, Book* newBook); // Метод для обновления существующей книги
    int getCount() const; // Метод для получения количества книг
    Book* operator[](int index) const; // Перегруженный оператор индексирования

    friend std::ostream& operator<<(std::ostream& os, const BookTable& table); // Перегруженный оператор вывода
};

#endif
```

#### Объяснение:

1. **Класс `BookTable`**:
   - **Приватные члены**:
     - `Book** books`: Массив указателей на объекты типа `Book`.
     - `int capacity`: Вместимость массива книг.
     - `int count`: Текущее количество книг в таблице.
   - **Публичные методы**:
     - `BookTable()`: Конструктор по умолчанию, инициализирует все члены класса значением по умолчанию.
     - `~BookTable()`: Деструктор, освобождает память, выделенную под книги и сам массив указателей.
     - `void addBook(Book* book)`: Метод для добавления новой книги в таблицу. Если массив заполнен, увеличивает его вместимость в два раза.
     - `void removeBook(int index)`: Метод для удаления книги по указанному индексу. Уменьшает количество книг и проверяет, нужно ли уменьшить вместимость массива.
     - `void updateBook(int index, Book* newBook)`: Метод для обновления книги по указанному индексу.
     - `int getCount() const`: Возвращает количество книг в таблице.
     - `Book* operator[](int index) const`: Перегруженный оператор индексирования, позволяет получить книгу по указанному индексу.
     - `friend std::ostream& operator<<(std::ostream& os, const BookTable& table)`: Дружественная функция для перегрузки оператора вывода, чтобы можно было вывести всю таблицу книг в поток вывода.

### Файл `book_table.cpp`

#### Реализация методов класса `BookTable`

```cpp
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
        if (count > 0 && count == capacity / 4) {
            capacity /= 2;
            Book** newBooks = new Book*[capacity];
            for (int i = 0; i < count; ++i) {
                newBooks[i] = books[i];
            }
            delete[] books;
            books = newBooks;
        }
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
        os << *table.books[i];
    }
    return os;
}
```

#### Объяснение:

1. **Конструктор по умолчанию**:

   - `BookTable()`: Инициализирует `books` нулевым указателем, `capacity` равным 0 и `count` равным 0.

2. **Деструктор**:

   - `~BookTable()`: Освобождает память, выделенную под книги в массиве и сам массив указателей. Удаляет каждую книгу перед освобождением памяти массива.

3. **Метод `addBook`**:

   - Если количество книг равно вместимости, увеличивает вместимость в два раза и выделяет новый массив указателей на книги. Копирует старые указатели в новый массив и освобождает память старого массива.
   - Добавляет новую книгу в конец массива и увеличивает счетчик количества книг.

4. **Метод `removeBook`**:

   - Удаляет книгу по указанному индексу, перемещая остальные книги влево. Если количество книг становится равным четверти вместимости, уменьшает вместимость в два раза.

5. **Метод `updateBook`**:

   - Обновляет книгу по указанному индексу, сначала удаляя старую книгу и затем добавляя новую.

6. **Метод `getCount`**:

   - Возвращает текущее количество книг в таблице.

7. **Перегруженный оператор индексирования**:

   - Позволяет получать книгу по указанному индексу, возвращая `nullptr`, если индекс выходит за пределы допустимого диапазона.

8. **Перегруженный оператор вывода**:
   - Оператор для вывода всей таблицы книг в поток вывода. Перебирает массив книг и выводит каждую книгу с помощью перегруженного оператора `<<` для объектов типа `Book`.

### Файл `detailed_book.h`

```cpp
#ifndef DETAILED_BOOK_H
#define DETAILED_BOOK_H

#include "book.h"

class DetailedBook : public Book {
private:
    char* publisher; // Указатель на строку, представляющую издателя книги
    int year;         // Целое число, представляющее год издания книги
    char* isbn;       // Указатель на строку, представляющую ISBN книги

public:
    DetailedBook();
    DetailedBook(const DetailedBook& other);
    DetailedBook(const char* title, const char* author, const char* publisher, int year, const char* isbn);
    ~DetailedBook() override; // Переопределенный деструктор

    const char* getPublisher() const; // Метод для получения издателя книги
    int getYear() const;              // Метод для получения года издания книги
    const char* getIsbn() const;      // Метод для получения ISBN книги
    void setPublisher(const char* publisher); // Метод для установки издателя книги
    void setYear(int year);             // Метод для установки года издания книги
    void setIsbn(const char* isbn);     // Метод для установки ISBN книги

    friend std::ostream& operator<<(std::ostream& os, const DetailedBook& book); // Перегруженный оператор вывода
     DetailedBook& operator=(const DetailedBook& other); // Перегруженный оператор присваивания
};

#endif
```

### Объяснение файла `detailed_book.h`

1. **Класс `DetailedBook`**:
   - Наследуется от класса `Book`.
   - Приватные члены:
     - `char* publisher`: Указатель на строку, хранящую название издателя книги.
     - `int year`: Целое число, представляющее год издания книги.
     - `char* isbn`: Указатель на строку, хранящую международный стандартный книжный номер (ISBN).
   - Публичные методы:
     - Конструкторы: по умолчанию (`DetailedBook()`), копирования (`DetailedBook(const DetailedBook& other)`) и с параметрами (`DetailedBook(const char* title, const char* author, const char* publisher, int year, const char* isbn)`).
     - Деструктор (`~DetailedBook()`): освобождает память, выделенную для `publisher` и `isbn`.
     - Методы доступа к полям: `getPublisher()`, `getYear()`, `getIsbn()`.
     - Методы установки значений полей: `setPublisher(const char* publisher)`, `setYear(int year)`, `setIsbn(const char* isbn)`.
     - Перегруженный оператор вывода (`operator<<`).
     - Перегруженный оператор присваивания (`operator=`).

### Файл `detailed_book.cpp`

```cpp
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

// Перегруженный оператор вывода (переопределен)
std::ostream& operator<<(std::ostream& os, const DetailedBook& book) {
    os << static_cast<const Book&>(book) << ", Publisher: " << (book.publisher ? book.publisher : "N/A")
       << ", Year: " << book.year << ", ISBN: " << (book.isbn ? book.isbn : "N/A");
    return os;
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
```

### Объяснение файла `detailed_book.cpp`

1. **Вспомогательная функция `strCopy`**:

   - Принимает указатель на строку и возвращает копию этой строки, выделенную динамически.

2. **Конструктор по умолчанию (`DetailedBook::DetailedBook()`):**

   - Инициализирует `publisher`, `year` и `isbn` нулевыми указателями и значением 0 для `year`.

3. **Конструктор копирования (`DetailedBook::DetailedBook(const DetailedBook& other)`):**

   - Копирует данные из другого объекта `DetailedBook`, включая вызов конструктора базового класса `Book` и копирование строк.

4. **Конструктор с параметрами (`DetailedBook::DetailedBook(const char* title, const char* author, const char* publisher, int year, const char* isbn)`):**

   - Инициализирует базовые поля `title` и `author` конструктором базового класса и копирует строки для `publisher` и `isbn`.

5. **Деструктор (`DetailedBook::~DetailedBook()`):**

   - Освобождает память, выделенную для `publisher` и `isbn`.

6. **Методы доступа к полям (`getPublisher()`, `getYear()`, `getIsbn()`):**

   - Возвращают значения соответствующих полей.

7. **Методы установки значений полей (`setPublisher(const char* publisher)`, `setYear(int year)`, `setIsbn(const char* isbn)`):**

   - Устанавливают значения соответствующих полей, при этом старое значение освобождается.

8. **Перегруженный оператор вывода (`operator<<`):**

   - Выводит информацию о книге, включая данные из базового класса `Book` и дополнительную информацию о издателе, годе издания и ISBN.

9. **Перегруженный оператор присваивания (`operator=`):**
   - Присваивает значения из другого объекта `DetailedBook`, включая освобождение старой памяти и копирование новых строк.

### 1. Файл `book.h`

#### Описание:

Этот файл содержит объявление класса `Book` и прототип функции `strCopy`. Класс `Book` представляет книгу с заголовком и автором. В нём также определены конструкторы, деструктор, методы для доступа к полям, оператор присваивания и перегруженный оператор вывода.

#### Основные компоненты:

- **Прототип функции `strCopy`:**

  ```cpp
  inline char* strCopy(const char* str);
  ```

  Функция копирует строку, переданную в качестве аргумента. Используется для создания копий заголовка и автора книги.

- **Класс `Book`:**

  - **Поля:**

    ```cpp
    protected:
        char* title;
        char* author;
    ```

    Поля класса, хранящие заголовок и автора книги.

  - **Конструкторы:**

    ```cpp
    Book();
    Book(const Book& other);
    Book(const char* title, const char* author);
    ```

    Конструктор по умолчанию, конструктор копирования и конструктор с параметрами.

  - **Методы:**

    ```cpp
    virtual ~Book();
    const char* getTitle() const;
    const char* getAuthor() const;
    void setTitle(const char* title);
    void setAuthor(const char* author);
    ```

    Деструктор, методы для получения и установки заголовка и автора.

  - **Перегруженные операторы:**
    ```cpp
    std::ostream& operator<<(std::ostream& os, const Book& book);
    Book& operator=(const Book& other);
    ```
    Перегруженный оператор вывода и оператор присваивания.

### 2. Файл `book.cpp`

#### Описание:

Этот файл содержит реализацию функций, объявленных в `book.h`. Включает определение функции `strCopy` и методы класса `Book`.

#### Основные компоненты:

- **Функция `strCopy`:**

  ```cpp
  char* strCopy(const char* str) {
      if (!str) return nullptr;
      size_t len = strlen(str) + 1;
      char* newStr = new char[len];
      strcpy(newStr, str);
      return newStr;
  }
  ```

  Функция копирует строку, используя `strlen` для определения длины строки и `strcpy` для копирования.

- **Конструктор по умолчанию:**

  ```cpp
  Book::Book() : title(nullptr), author(nullptr) {}
  ```

  Инициализирует поля `title` и `author` нулевыми указателями.

- **Конструктор копирования:**

  ```cpp
  Book::Book(const Book& other) : title(nullptr), author(nullptr) {
      if (other.title) title = strCopy(other.title);
      if (other.author) author = strCopy(other.author);
  }
  ```

  Копирует заголовок и автора из другой книги, используя `strCopy`.

- **Конструктор с параметрами:**

  ```cpp
  Book::Book(const char* title, const char* author) : title(nullptr), author(nullptr) {
      this->title = strCopy(title);
      this->author = strCopy(author);
  }
  ```

  Принимает строки для заголовка и автора и сохраняет их, используя `strCopy`.

- **Деструктор:**

  ```cpp
  Book::~Book() {
      delete[] title;
      delete[] author;
  }
  ```

  Освобождает выделенную память для заголовка и автора.

- **Методы доступа к полям:**

  ```cpp
  const char* Book::getTitle() const { return title; }
  const char* Book::getAuthor() const { return author; }
  void Book::setTitle(const char* title) {
      delete[] this->title;
      this->title = strCopy(title);
  }
  void Book::setAuthor(const char* author) {
      delete[] this->author;
      this->author = strCopy(author);
  }
  ```

  Методы для получения и установки заголовка и автора.

- **Перегруженный оператор вывода:**

  ```cpp
  std::ostream& operator<<(std::ostream& os, const Book& book) {
      os << "Title: " << (book.title ? book.title : "N/A") << ", Author: " << (book.author ? book.author : "N/A");
      return os;
  }
  ```

  Перегруженный оператор вывода, который выводит заголовок и автора, если они не равны `nullptr`.

- **Перегруженный оператор присваивания:**

  ```cpp
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
  ```

  Оператор присваивания, который копирует заголовок и автора из другой книги, если они не равны `nullptr`.

### 3. Файл `main.cpp`

#### Описание:

Этот файл содержит функцию `main`, где происходит демонстрация работы с классами `Book` и другими компонентами программы. Включает создание таблицы книг, добавление книг, изменение записи и удаление записи.

#### Основные компоненты:

- **Создание таблицы книг:**

  ```cpp
  BookTable table;
  ```

  Создает объект `BookTable`, который будет содержать список книг.

- **Добавление базовых книг:**

  ```cpp
  table.addBook(new Book("The Lord of the Rings", "J.R.R. Tolkien"));
  table.addBook(new Book("Pride and Prejudice", "Jane Austen"));
  ```

  Добавляет две базовые книги в таблицу.

- **Добавление детальных книг:**

  ```cpp
  table.addBook(new DetailedBook("1984", "George Orwell", "Secker & Warburg", 1949, "978-0451524935"));
  table.addBook(new DetailedBook("To Kill a Mockingbird", "Harper Lee", "J. B. Lippincott & Co.", 1960, "978-0446310789"));
  ```

  Добавляет две детальные книги в таблицу.

- **Вывод начальной таблицы:**

  ```cpp
  std::cout << table;
  ```

  Выводит содержимое таблицы книг.

- **Изменение записи:**

  ```cpp
  table.updateBook(0, new Book("The Hobbit", "J.R.R. Tolkien"));
  ```

  Изменяет первую книгу в таблице на новую.

- **Вывод таблицы после изменений:**

  ```cpp
  std::cout << table;
  ```

  Выводит обновленное содержимое таблицы.

- **Удаление записи:**

  ```cpp
  table.removeBook(1);
  ```

  Удаляет вторую книгу из таблицы.

- **Вывод таблицы после удаления:**

  ```cpp
  std::cout << table;
  ```

  Выводит обновленное содержимое таблицы после удаления книги.

- **Доступ к записи по индексу:**

  ```cpp
  Book* book = table[0];
  if(book) {
      std::cout << *book;
  } else {
      std::cout << "Книга не найдена.";
  }
  ```

  Получает книгу по индексу 0 и выводит её информацию.

- **Получение количества записей:**
  ```cpp
  std::cout << table.getCount();
  ```
  Выводит количество книг в таблице.
