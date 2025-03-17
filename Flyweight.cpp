#include <iostream>
#include <unordered_map>
#include <string>

class Flyweight {
public:
    virtual void operation(const std::string& extrinsicState) const = 0;
    virtual ~Flyweight() = default;
};

class ConcreteFlyweight : public Flyweight {
private:
    std::string intrinsicState;
public:
    ConcreteFlyweight(const std::string& state) : intrinsicState(state) {}
    void operation(const std::string& extrinsicState) const override {
        std::cout << "ConcreteFlyweight: внутреннее состояние (" << intrinsicState
                  << "), внешнее состояние (" << extrinsicState << ")." << std::endl;
    }
};

class FlyweightFactory {
private:
    std::unordered_map<std::string, Flyweight*> flyweights;
public:
    Flyweight* getFlyweight(const std::string& key) {
        if (flyweights.find(key) == flyweights.end()) {
            flyweights[key] = new ConcreteFlyweight(key);
        }
        return flyweights[key];
    }
    ~FlyweightFactory() {
        for (auto& pair : flyweights) {
            delete pair.second;
        }
    }
};

void clientCode(FlyweightFactory& factory, const std::string& intrinsicState, const std::string& extrinsicState) {
    Flyweight* flyweight = factory.getFlyweight(intrinsicState);
    flyweight->operation(extrinsicState);
}

int main() {
    FlyweightFactory factory;

    clientCode(factory, "State1", "Extrinsic1");
    clientCode(factory, "State1", "Extrinsic2");
    clientCode(factory, "State2", "Extrinsic3");

    return 0;
}
