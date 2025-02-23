#include <iostream>

// Abstract Class: Beverage Preparation Template
class Beverage {
public:
    // Template Method (final to prevent override)
    virtual void prepareRecipe() final {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

protected:
    virtual void brew() = 0;            // Step to be implemented by subclasses
    virtual void addCondiments() = 0;   // Step to be implemented by subclasses

    void boilWater() { // Common step
        std::cout << "Boiling water...\n";
    }

    void pourInCup() { // Common step
        std::cout << "Pouring into cup...\n";
    }
};

// Concrete Class: Tea
class Tea : public Beverage {
    protected:
        void brew() override {
            std::cout << "Steeping the tea...\n";
        }
    
        void addCondiments() override {
            std::cout << "Adding lemon...\n";
        }
    };
    
    // Concrete Class: Coffee
    class Coffee : public Beverage {
    protected:
        void brew() override {
            std::cout << "Dripping coffee through filter...\n";
        }
    
        void addCondiments() override {
            std::cout << "Adding sugar and milk...\n";
        }
    };

    int main() {
        std::cout << "Preparing Tea:\n";
        Tea tea;
        tea.prepareRecipe(); // Calls the template method
    
        std::cout << "\nPreparing Coffee:\n";
        Coffee coffee;
        coffee.prepareRecipe(); // Calls the template method
    
        return 0;
    }
    