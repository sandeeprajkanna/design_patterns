#include <iostream>
#include <memory>

// Forward declaration of Context (VendingMachine)
class VendingMachine;

// State Interface
class State {
public:
    virtual void handleRequest(VendingMachine& machine) = 0;
    virtual ~State() = default;
};

// Concrete State 1: Idle State
class IdleState : public State {
public:
    void handleRequest(VendingMachine& machine) override;
};

// Concrete State 2: Dispensing State
class DispensingState : public State {
public:
    void handleRequest(VendingMachine& machine) override;
};

// Concrete State 3: Out of Stock State
class OutOfStockState : public State {
public:
    void handleRequest(VendingMachine& machine) override;
};

// Context Class: Vending Machine
class VendingMachine {
private:
    std::unique_ptr<State> currentState;  // Holds the current state
    int stock;

public:
    VendingMachine(int initialStock) : stock(initialStock) {
        if (stock > 0) {
            currentState = std::make_unique<IdleState>();
        } else {
            currentState = std::make_unique<OutOfStockState>();
        }
    }

    void setState(std::unique_ptr<State> newState) {
        currentState = std::move(newState);
    }

    int getStock() const { return stock; }

    void reduceStock() {
        if (stock > 0) {
            stock--;
        }
    }

    void request() {
        currentState->handleRequest(*this);
    }
};

// Implementations of State Methods
void IdleState::handleRequest(VendingMachine& machine) {
    std::cout << "Processing order... Dispensing item.\n";
    machine.reduceStock();
    if (machine.getStock() > 0) {
        machine.setState(std::make_unique<DispensingState>());
    } else {
        machine.setState(std::make_unique<OutOfStockState>());
    }
}

void DispensingState::handleRequest(VendingMachine& machine) {
    std::cout << "Item dispensed. Returning to idle state.\n";
    machine.setState(std::make_unique<IdleState>());
}

void OutOfStockState::handleRequest(VendingMachine& machine) {
    std::cout << "Out of stock. Cannot process order.\n";
}

// Client Code
int main() {
    VendingMachine machine(2);

    machine.request(); // First purchase
    machine.request(); // Second purchase
    machine.request(); // Third purchase (Out of Stock)

    return 0;
}
