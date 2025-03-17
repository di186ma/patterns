#include <iostream>
#include <string>

class Component {
public:
    virtual void operation() const = 0;
    virtual ~Component() = default;
};

class ConcreteComponent : public Component {
public:
    void operation() const override {
        std::cout << "ConcreteComponent: базовая операция." << std::endl;
    }
};

class Decorator : public Component {
protected:
    Component* component;
public:
    Decorator(Component* c) : component(c) {}
    void operation() const override {
        if (component) {
            component->operation();
        }
    }
};

class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* c) : Decorator(c) {}
    void operation() const override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorA: дополнительная операция A." << std::endl;
    }
};

class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* c) : Decorator(c) {}
    void operation() const override {
        Decorator::operation();
        std::cout << "ConcreteDecoratorB: дополнительная операция B." << std::endl;
    }
};

void clientCode(Component* component) {
    component->operation();
}

int main() {
    Component* component = new ConcreteComponent;
    Component* decoratorA = new ConcreteDecoratorA(component);
    Component* decoratorB = new ConcreteDecoratorB(decoratorA);

    clientCode(decoratorB);

    delete component;
    delete decoratorA;
    delete decoratorB;

    return 0;
}
