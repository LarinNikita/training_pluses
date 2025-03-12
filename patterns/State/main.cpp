#include "VendingMachine.h" // Включаем заголовочный файл для VendingMachine
#include <iostream>

int main() {
    VendingMachine vm(3);

    vm.selectDrink();    // Нельзя без монетки
    vm.insertCoin();     // Монетка принята
    vm.ejectCoin();      // Возврат монетки
    vm.insertCoin();     // Монетка принята
    vm.selectDrink();    // Выдача напитка (осталось 2)

    vm.insertCoin();
    vm.selectDrink();    // Выдача (осталось 1)

    vm.insertCoin();
    vm.selectDrink();    // Выдача (осталось 0)

    vm.insertCoin();     // Напитки закончились

    return 0;
}