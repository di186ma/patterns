#include <iostream>

class Target {
public:
    virtual void request() const {
        std::cout << "Target: стандартное поведение." << std::endl;
    }
};

class Adaptee {
public:
    void specificRequest() const {
        std::cout << "Adaptee: специфическое поведение." << std::endl;
    }
};

class Adapter : public Target {
private:
    Adaptee* adaptee;
public:
    Adapter(Adaptee* a) : adaptee(a) {}
    void request() const override {
        adaptee->specificRequest();
    }
};

void clientCode(const Target* target) {
    target->request();
}

int main() {
    Target* target = new Target;
    clientCode(target);

    Adaptee* adaptee = new Adaptee;
    Adapter* adapter = new Adapter(adaptee);
    clientCode(adapter);

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}
