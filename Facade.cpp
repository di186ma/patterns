#include <iostream>
#include <string>

class SubsystemA {
public:
    void operationA() const {
        std::cout << "SubsystemA: выполнение операции A." << std::endl;
    }
};

class SubsystemB {
public:
    void operationB() const {
        std::cout << "SubsystemB: выполнение операции B." << std::endl;
    }
};

class SubsystemC {
public:
    void operationC() const {
        std::cout << "SubsystemC: выполнение операции C." << std::endl;
    }
};

class Facade {
private:
    SubsystemA* subsystemA;
    SubsystemB* subsystemB;
    SubsystemC* subsystemC;
public:
    Facade() {
        subsystemA = new SubsystemA;
        subsystemB = new SubsystemB;
        subsystemC = new SubsystemC;
    }
    ~Facade() {
        delete subsystemA;
        delete subsystemB;
        delete subsystemC;
    }
    void operation() const {
        std::cout << "Facade: запуск операций подсистем." << std::endl;
        subsystemA->operationA();
        subsystemB->operationB();
        subsystemC->operationC();
    }
};

void clientCode(const Facade& facade) {
    facade.operation();
}

int main() {
    Facade facade;
    clientCode(facade);
    return 0;
}
