#include <iostream>
#include <string>
#include <memory>

class Prototype {
public:
    virtual ~Prototype() = default;
    virtual std::unique_ptr<Prototype> clone() const = 0;
    virtual void print() const = 0;
};

class ConcretePrototype : public Prototype {
public:
    ConcretePrototype(const std::string& name) : name(name) {}

    std::unique_ptr<Prototype> clone() const override {
        return std::make_unique<ConcretePrototype>(*this);
    }

    void print() const override {
        std::cout << "ConcretePrototype: " << name << std::endl;
    }

private:
    std::string name;
};

int main() {
    std::unique_ptr<Prototype> prototype = std::make_unique<ConcretePrototype>("Original");
    std::unique_ptr<Prototype> clone = prototype->clone();

    prototype->print();
    clone->print();

    return 0;
}
