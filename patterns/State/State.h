#ifndef STATE_H
#define STATE_H

// Предварительное объявление класса VendingMachine
class VendingMachine;

// Абстрактный класс состояния
class State {
public:
    virtual void insertCoin() = 0;
    virtual void ejectCoin() = 0;
    virtual void selectDrink() = 0;
    virtual void dispense() = 0;
    virtual ~State() = default;
};

// Конкретные состояния
class NoCoinState : public State {
private:
    VendingMachine* machine;  // Объявление указателя на VendingMachine
public:
    NoCoinState(VendingMachine* m); // Измененный конструктор
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class HasCoinState : public State {
private:
    VendingMachine* machine;  // Объявление указателя на VendingMachine
public:
    HasCoinState(VendingMachine* m); // Измененный конструктор
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class SoldState : public State {
private:
    VendingMachine* machine;  // Объявление указателя на VendingMachine
public:
    SoldState(VendingMachine* m); // Измененный конструктор
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class SoldOutState : public State {
private:
    VendingMachine* machine;  // Объявление указателя на VendingMachine
public:
    SoldOutState(VendingMachine* m); // Измененный конструктор
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

#endif