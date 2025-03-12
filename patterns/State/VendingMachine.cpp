#include "VendingMachine.h" // Включаем заголовок класса VendingMachine
#include <iostream>

VendingMachine::VendingMachine(int count) : drinkCount(count) {
    noCoinState = new NoCoinState(this);
    hasCoinState = new HasCoinState(this);
    soldState = new SoldState(this);
    soldOutState = new SoldOutState(this);

    currentState = (drinkCount > 0) ? noCoinState : soldOutState;
}

VendingMachine::~VendingMachine() {
    delete noCoinState;
    delete hasCoinState;
    delete soldState;
    delete soldOutState;
}

void VendingMachine::setState(State* state) {
    currentState = state;
}

void VendingMachine::insertCoin() {
    currentState->insertCoin();
}

void VendingMachine::ejectCoin() {
    currentState->ejectCoin();
}

void VendingMachine::selectDrink() {
    currentState->selectDrink();
    currentState->dispense();
}

void VendingMachine::releaseDrink() {
    std::cout << "Напиток выдан\n";
    drinkCount--;
}

int VendingMachine::getDrinkCount() const {
    return drinkCount;
}

State* VendingMachine::getNoCoinState() const { return noCoinState; }
State* VendingMachine::getHasCoinState() const { return hasCoinState; }
State* VendingMachine::getSoldState() const { return soldState; }
State* VendingMachine::getSoldOutState() const { return soldOutState; }