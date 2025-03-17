#include <iostream>
#include <string>

class Subject {
public:
    virtual void request() const = 0;
    virtual ~Subject() = default;
};

class RealSubject : public Subject {
public:
    void request() const override {
        std::cout << "RealSubject: обработка запроса." << std::endl;
    }
};

class Proxy : public Subject {
private:
    RealSubject* realSubject;
    bool checkAccess() const {
        std::cout << "Proxy: проверка доступа." << std::endl;
        return true;
    }
    void logAccess() const {
        std::cout << "Proxy: логирование запроса." << std::endl;
    }
public:
    Proxy(RealSubject* subject) : realSubject(subject) {}
    ~Proxy() {
        delete realSubject;
    }
    void request() const override {
        if (checkAccess()) {
            realSubject->request();
            logAccess();
        }
    }
};

void clientCode(const Subject& subject) {
    subject.request();
}

int main() {
    RealSubject* realSubject = new RealSubject;
    Proxy* proxy = new Proxy(realSubject);

    clientCode(*proxy);

    delete proxy;

    return 0;
}
