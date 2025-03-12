#include <iostream>
#include <memory>

class Button {
public:
    virtual void render() = 0;
    virtual ~Button() = default;
};

class Checkbox {
public:
    virtual void render() = 0;
    virtual ~Checkbox() = default;
};

class WindowsButton : public Button {
public:
    void render() override {
        std::cout << "Render a button in Windows style" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Render a checkbox in Windows style" << std::endl;
    }
};

class MacOSButton : public Button {
public:
    void render() override {
        std::cout << "Render a button in macOS style" << std::endl;
    }
};

class MacOSCheckbox : public Checkbox {
public:
    void render() override {
        std::cout << "Render a checkbox in macOS style" << std::endl;
    }
};

class GUIFactory {
public:
    virtual std::unique_ptr<Button> createButton() = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() = 0;
    virtual ~GUIFactory() = default;
};

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<WindowsButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacOSFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() override {
        return std::make_unique<MacOSButton>();
    }

    std::unique_ptr<Checkbox> createCheckbox() override {
        return std::make_unique<MacOSCheckbox>();
    }
};

class Application {
private:
    std::unique_ptr<GUIFactory> factory;
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;

public:
    Application(std::unique_ptr<GUIFactory> factory)
            : factory(std::move(factory)) {
        button = this->factory->createButton();
        checkbox = this->factory->createCheckbox();
    }

    void render() {
        button->render();
        checkbox->render();
    }
};

int main() {
    auto windowsApp = std::make_unique<Application>(std::make_unique<WindowsFactory>());
    windowsApp->render();

    auto macApp = std::make_unique<Application>(std::make_unique<MacOSFactory>());
    macApp->render();

    return 0;
}
