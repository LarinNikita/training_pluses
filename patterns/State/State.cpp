#include "State.h"
#include "VendingMachine.h"
#include <iostream>

// Инициализация machine в конструкторах
NoCoinState::NoCoinState(VendingMachine* m) : machine(m) {}

void NoCoinState::insertCoin() {
    std::cout << "Монетка принята\n";
    machine->setState(machine->getHasCoinState());
}

void NoCoinState::ejectCoin() {
    std::cout << "Нет монетки для возврата\n";
}

void NoCoinState::selectDrink() {
    std::cout << "Сначала вставьте монетку\n";
}

void NoCoinState::dispense() {
    std::cout << "Сначала оплатите напиток\n";
}

HasCoinState::HasCoinState(VendingMachine* m) : machine(m) {}

void HasCoinState::insertCoin() {
    std::cout << "Монетка уже вставлена\n";
}

void HasCoinState::ejectCoin() {
    std::cout << "Монетка возвращена\n";
    machine->setState(machine->getNoCoinState());
}

void HasCoinState::selectDrink() {
    std::cout << "Выбор напитка...\n";
    machine->setState(machine->getSoldState());
}

void HasCoinState::dispense() {
    std::cout << "Сначала выберите напиток\n";
}

SoldState::SoldState(VendingMachine* m) : machine(m) {}

void SoldState::insertCoin() {
    std::cout << "Подождите, идет выдача напитка\n";
}

void SoldState::ejectCoin() {
    std::cout << "Извините, вы уже выбрали напиток\n";
}

void SoldState::selectDrink() {
    std::cout << "Нельзя выбрать напиток дважды\n";
}

void SoldState::dispense() {
    if(machine->getDrinkCount() > 0) {
        machine->releaseDrink();
        machine->setState(machine->getNoCoinState());
    } else {
        std::cout << "Напитки закончились!\n";
        machine->setState(machine->getSoldOutState());
    }
}

SoldOutState::SoldOutState(VendingMachine* m) : machine(m) {}

void SoldOutState::insertCoin() {
    std::cout << "Извините, напитки закончились\n";
}

void SoldOutState::ejectCoin() {
    std::cout << "Нет монетки для возврата\n";
}

void SoldOutState::selectDrink() {
    std::cout << "Напитки закончились\n";
}

void SoldOutState::dispense() {
    std::cout << "Напитки закончились\n";
}