#include <iostream>

// Abstract Product A (Button)
class Button
{
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

// Abstract Product B (Checkbox)
class Checkbox
{
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};

// Concrete Product A1: Windows Button
class WindowsButton : public Button
{
public:
    void render() override
    {
        std::cout << "Rendering Windows Button\n";
    }
};

// Concrete Product A2: MacOS Button
class MacOSButton : public Button
{
public:
    void render() override
    {
        std::cout << "Rendering MacOS Button\n";
    }
};

// Concrete Product B1: Windows Checkbox
class WindowsCheckbox : public Checkbox
{
public:
    void render() override
    {
        std::cout << "Rendering Windows Checkbox\n";
    }
};

// Concrete Product B2: MacOS Checkbox
class MacOSCheckbox : public Checkbox
{
public:
    void render() override
    {
        std::cout << "Rendering MacOS Checkbox\n";
    }
};

// Abstract Factory Interface
class GUIFactory
{
public:
    virtual Button *createButton() = 0;
    virtual Checkbox *createCheckbox() = 0;
    virtual ~GUIFactory() {}
};

// Concrete Factory 1: Windows Factory
class WindowsFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new WindowsButton();
    }

    Checkbox *createCheckbox() override
    {
        return new WindowsCheckbox();
    }
};

// Concrete Factory 2: MacOS Factory
class MacOSFactory : public GUIFactory
{
public:
    Button *createButton() override
    {
        return new MacOSButton();
    }

    Checkbox *createCheckbox() override
    {
        return new MacOSCheckbox();
    }
};

void renderUI(GUIFactory* factory) {
    Button* btn = factory->createButton();
    Checkbox* chk = factory->createCheckbox();

    btn->render();
    chk->render();

    delete btn;
    delete chk;
}

int main() {
    GUIFactory* factory;

    // Example: Select OS type dynamically
    std::string osType;
    std::cout << "Enter OS (Windows/Mac): ";
    std::cin >> osType;

    if (osType == "Windows") {
        factory = new WindowsFactory();
    } else {
        factory = new MacOSFactory();
    }

    renderUI(factory);
    delete factory;

    return 0;
}
