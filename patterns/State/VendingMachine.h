#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "State.h" // Включаем заголовок с определениями состояний

class VendingMachine {
private:
    State* currentState;
    int drinkCount;

    // Все возможные состояния
    State* noCoinState;
    State* hasCoinState;
    State* soldState;
    State* soldOutState;

public:
    VendingMachine(int count);
    ~VendingMachine();

    void setState(State* state);

    // Методы для действий пользователя
    void insertCoin();
    void ejectCoin();
    void selectDrink();

    // Вспомогательные методы
    void releaseDrink();
    int getDrinkCount() const;

    // Методы для доступа к состояниям
    State* getNoCoinState() const;
    State* getHasCoinState() const;
    State* getSoldState() const;
    State* getSoldOutState() const;
};

#endif