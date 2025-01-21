#include "book_table.h"
#include "book.h"
#include "detailed_book.h"
#include <iostream>

int main() {
    // Демонстрация работы классов
    std::cout << "--- Начало работы программы ---" << std::endl;
    BookTable table;
    std::cout << "Создана таблица книг." << std::endl;

    // Добавление базовых книг
    std::cout << "\n--- Добавление базовых книг ---" << std::endl;
    table.addBook(new Book("The Lord of the Rings", "J.R.R. Tolkien"));
    std::cout << "Добавлена книга: 'The Lord of the Rings' by J.R.R. Tolkien." << std::endl;
    table.addBook(new Book("Pride and Prejudice", "Jane Austen"));
    std::cout << "Добавлена книга: 'Pride and Prejudice' by Jane Austen." << std::endl;

    // Добавление детальных книг
    std::cout << "\n--- Добавление детальных книг ---" << std::endl;
    table.addBook(new DetailedBook("1984", "George Orwell", "Secker & Warburg", 1949, "978-0451524935"));
    std::cout << "Добавлена книга: '1984' by George Orwell." << std::endl;
    table.addBook(new DetailedBook("To Kill a Mockingbird", "Harper Lee", "J. B. Lippincott & Co.", 1960, "978-0446310789"));
    std::cout << "Добавлена книга: 'To Kill a Mockingbird' by Harper Lee." << std::endl;

    // Вывод таблицы
    std::cout << "\n--- Вывод начальной таблицы ---" << std::endl;
    std::cout << "Начальная таблица книг:\n" << table << std::endl;

     // Изменение записи
    std::cout << "\n--- Изменение записи ---" << std::endl;
    table.updateBook(0, new Book("The Hobbit", "J.R.R. Tolkien"));
    std::cout << "Изменена первая книга на: 'The Hobbit' by J.R.R. Tolkien." << std::endl;

    // Вывод таблицы после изменений
    std::cout << "\n--- Вывод таблицы после изменения ---" << std::endl;
    std::cout << "Таблица после изменения:\n" << table << std::endl;

    // Удаление записи
    std::cout << "\n--- Удаление записи ---" << std::endl;
    table.removeBook(1);
    std::cout << "Удалена вторая книга из таблицы." << std::endl;

    // Вывод таблицы после удаления
    std::cout << "\n--- Вывод таблицы после удаления ---" << std::endl;
    std::cout << "Таблица после удаления:\n" << table << std::endl;

    // Доступ к записи по индексу
    std::cout << "\n--- Доступ к книге по индексу ---" << std::endl;
    Book* book = table[0];
    if(book) {
        std::cout << "Книга по индексу 0: " << *book << std::endl;
    } else {
        std::cout << "Книга по индексу 0 не найдена." << std::endl;
    }

    // Получение количества записей
    std::cout << "\n--- Получение количества записей ---" << std::endl;
    std::cout << "Всего книг в таблице: " << table.getCount() << std::endl;

    std::cout << "\n--- Завершение работы программы ---" << std::endl;
    return 0;
}

