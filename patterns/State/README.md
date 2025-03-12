Как собрать проект (пример с использованием g++)

    Компиляция: Скомпилируйте каждый .cpp файл в объектные файлы:

    g++ -c State.cpp -o State.o
    g++ -c VendingMachine.cpp -o VendingMachine.o
    g++ -c main.cpp -o main.o

Сборка (линковка): Слинкуйте объектные файлы в исполняемый файл:

g++ State.o VendingMachine.o main.o -o vending_machine

Запуск: Запустите исполняемый файл:

./vending_machine
