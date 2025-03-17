#include <iostream>
#include <string>

class Implementation {
public:
    virtual void operationImpl(const std::string& text) const = 0;
    virtual ~Implementation() = default;
};

class ConcreteImplementationA : public Implementation {
public:
    void operationImpl(const std::string& text) const override {
        std::cout << "ConcreteImplementationA: " << text << std::endl;
    }
};

class ConcreteImplementationB : public Implementation {
public:
    void operationImpl(const std::string& text) const override {
        std::cout << "ConcreteImplementationB: " << text << std::endl;
    }
};

class Abstraction {
protected:
    Implementation* implementation;
public:
    Abstraction(Implementation* impl) : implementation(impl) {}
    virtual void operation(const std::string& text) const {
        implementation->operationImpl(text);
    }
    virtual ~Abstraction() = default;
};

class ExtendedAbstraction : public Abstraction {
public:
    ExtendedAbstraction(Implementation* impl) : Abstraction(impl) {}
    void operation(const std::string& text) const override {
        std::cout << "ExtendedAbstraction: ";
        implementation->operationImpl(text);
    }
};

void clientCode(const Abstraction& abstraction) {
    abstraction.operation("Hello, Bridge!");
}

int main() {
    Implementation* implementationA = new ConcreteImplementationA;
    Abstraction* abstractionA = new Abstraction(implementationA);
    clientCode(*abstractionA);

    Implementation* implementationB = new ConcreteImplementationB;
    Abstraction* abstractionB = new ExtendedAbstraction(implementationB);
    clientCode(*abstractionB);

    delete implementationA;
    delete abstractionA;
    delete implementationB;
    delete abstractionB;

    return 0;
}
