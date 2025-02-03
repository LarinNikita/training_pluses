#include <iostream>

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
    VendingMachine* machine;
public:
    NoCoinState(VendingMachine* m);
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class HasCoinState : public State {
    VendingMachine* machine;
public:
    HasCoinState(VendingMachine* m);
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class SoldState : public State {
    VendingMachine* machine;
public:
    SoldState(VendingMachine* m);
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

class SoldOutState : public State {
    VendingMachine* machine;
public:
    SoldOutState(VendingMachine* m);
    void insertCoin() override;
    void ejectCoin() override;
    void selectDrink() override;
    void dispense() override;
};

// Класс контекста - торговый автомат
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
    
    void setState(State* state) {
        currentState = state;
    }
    
    // Методы для действий пользователя
    void insertCoin() {
        currentState->insertCoin();
    }
    
    void ejectCoin() {
        currentState->ejectCoin();
    }
    
    void selectDrink() {
        currentState->selectDrink();
        currentState->dispense();
    }
    
    // Вспомогательные методы
    void releaseDrink() {
        std::cout << "Напиток выдан\n";
        drinkCount--;
    }
    
    int getDrinkCount() const {
        return drinkCount;
    }
    
    // Методы для доступа к состояниям
    State* getNoCoinState() const { return noCoinState; }
    State* getHasCoinState() const { return hasCoinState; }
    State* getSoldState() const { return soldState; }
    State* getSoldOutState() const { return soldOutState; }
};

// Реализация конкретных состояний
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

// Пример использования
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