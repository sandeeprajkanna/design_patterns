#include <iostream>

// Forward Declarations
class Manager;
class Engineer;

// Visitor Interface
class TaxCalculator {
public:
    virtual void visit(Manager* emp) = 0;
    virtual void visit(Engineer* emp) = 0;
};

// Element Interface
class Employee {
public:
    virtual void accept(TaxCalculator* visitor) = 0;
};

// Concrete Element: Manager
class Manager : public Employee {
public:
    void accept(TaxCalculator* visitor) override {
        visitor->visit(this);
    }
};

// Concrete Element: Engineer
class Engineer : public Employee {
public:
    void accept(TaxCalculator* visitor) override {
        visitor->visit(this);
    }
};

// Concrete Visitor: Tax Calculation
class IncomeTaxCalculator : public TaxCalculator {
public:
    void visit(Manager* emp) override {
        std::cout << "Manager's tax calculated.\n";
    }
    void visit(Engineer* emp) override {
        std::cout << "Engineer's tax calculated.\n";
    }
};

int main() {
    Manager mgr;
    Engineer eng;
    IncomeTaxCalculator taxCalc;

    mgr.accept(&taxCalc); // Output: Manager's tax calculated.
    eng.accept(&taxCalc); // Output: Engineer's tax calculated.

    return 0;
}
