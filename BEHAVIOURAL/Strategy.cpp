#include <iostream>
#include <memory>

// Strategy Interface
class PaymentStrategy {
public:
    virtual void pay(double amount) const = 0;
    virtual ~PaymentStrategy() = default;
};

// Concrete Strategy 1: Credit Card Payment
class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paid $" << amount << " using Credit Card.\n";
    }
};

// Concrete Strategy 2: PayPal Payment
class PayPalPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paid $" << amount << " using PayPal.\n";
    }
};

// Concrete Strategy 3: UPI Payment
class UPIPayment : public PaymentStrategy {
public:
    void pay(double amount) const override {
        std::cout << "Paid $" << amount << " using UPI.\n";
    }
};

// Context Class: Handles Payment
class PaymentContext {
private:
    std::unique_ptr<PaymentStrategy> strategy; // Holds a payment strategy
public:
    void setStrategy(std::unique_ptr<PaymentStrategy> newStrategy) {
        strategy = std::move(newStrategy);
    }

    void executePayment(double amount) const {
        if (strategy) {
            strategy->pay(amount);
        } else {
            std::cout << "No payment strategy selected.\n";
        }
    }
};

// Client Code
int main() {
    PaymentContext context;

    // Paying with Credit Card
    context.setStrategy(std::make_unique<CreditCardPayment>());
    context.executePayment(100.0);

    // Switching to PayPal
    context.setStrategy(std::make_unique<PayPalPayment>());
    context.executePayment(200.0);

    // Switching to UPI
    context.setStrategy(std::make_unique<UPIPayment>());
    context.executePayment(150.0);

    return 0;
}
