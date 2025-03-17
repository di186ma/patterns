#include <iostream>
#include <vector>
#include <memory>

class Component {
public:
    virtual void operation() const = 0;
    virtual void add(std::shared_ptr<Component> component) {}
    virtual void remove(std::shared_ptr<Component> component) {}
    virtual ~Component() = default;
};

class Leaf : public Component {
public:
    void operation() const override {
        std::cout << "Leaf: выполнение операции." << std::endl;
    }
};

class Composite : public Component {
private:
    std::vector<std::shared_ptr<Component>> children;
public:
    void operation() const override {
        std::cout << "Composite: выполнение операции." << std::endl;
        for (const auto& child : children) {
            child->operation();
        }
    }
    void add(std::shared_ptr<Component> component) override {
        children.push_back(component);
    }
    void remove(std::shared_ptr<Component> component) override {
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
    }
};

void clientCode(const Component& component) {
    component.operation();
}

int main() {
    auto leaf1 = std::make_shared<Leaf>();
    auto leaf2 = std::make_shared<Leaf>();
    auto leaf3 = std::make_shared<Leaf>();

    auto composite1 = std::make_shared<Composite>();
    composite1->add(leaf1);
    composite1->add(leaf2);

    auto composite2 = std::make_shared<Composite>();
    composite2->add(leaf3);
    composite2->add(composite1);

    clientCode(*composite2);

    return 0;
}
