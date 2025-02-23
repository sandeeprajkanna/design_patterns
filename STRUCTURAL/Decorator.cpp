#include <iostream>
#include <memory>

// Component Interface
class Coffee
{
public:
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
    virtual ~Coffee() = default;
};

// Concrete Component (Base Coffee)
class SimpleCoffee : public Coffee
{
public:
    std::string getDescription() const override
    {
        return "Simple Coffee";
    }

    double getCost() const override
    {
        return 50.0; // Base price of coffee
    }
};

// Decorator (Abstract Class)
class CoffeeDecorator : public Coffee
{
protected:
    std::unique_ptr<Coffee> coffee;

public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
};

// Concrete Decorator 1: Milk
class MilkDecorator : public CoffeeDecorator
{
public:
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

    std::string getDescription() const override
    {
        return coffee->getDescription() + ", Milk";
    }

    double getCost() const override
    {
        return coffee->getCost() + 10.0; // Adding cost of milk
    }
};

// Concrete Decorator 2: Sugar
class SugarDecorator : public CoffeeDecorator
{
public:
    SugarDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

    std::string getDescription() const override
    {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() const override
    {
        return coffee->getCost() + 5.0; // Adding cost of sugar
    }
};

// Concrete Decorator 3: Caramel
class CaramelDecorator : public CoffeeDecorator
{
public:
    CaramelDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}

    std::string getDescription() const override
    {
        return coffee->getDescription() + ", Caramel";
    }

    double getCost() const override
    {
        return coffee->getCost() + 15.0; // Adding cost of caramel
    }
};


int main() {
    // Create a simple coffee
    std::unique_ptr<Coffee> coffee = std::make_unique<SimpleCoffee>();
    std::cout << coffee->getDescription() << " | Cost: " << coffee->getCost() << " INR\n";

    // Add Milk
    coffee = std::make_unique<MilkDecorator>(std::move(coffee));
    std::cout << coffee->getDescription() << " | Cost: " << coffee->getCost() << " INR\n";

    // Add Sugar
    coffee = std::make_unique<SugarDecorator>(std::move(coffee));
    std::cout << coffee->getDescription() << " | Cost: " << coffee->getCost() << " INR\n";

    // Add Caramel
    coffee = std::make_unique<CaramelDecorator>(std::move(coffee));
    std::cout << coffee->getDescription() << " | Cost: " << coffee->getCost() << " INR\n";

    return 0;
}
