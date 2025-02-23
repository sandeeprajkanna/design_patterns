#include <iostream>
#include <vector>

// Memento: Stores state
class Memento {
private:
    std::string state;
public:
    Memento(std::string s) : state(s) {}
    std::string getState() const { return state; }
};

// Originator: Creates and restores Memento
class Originator {
private:
    std::string state;
public:
    void setState(const std::string& s) { 
        state = s; 
        std::cout << "State changed to: " << state << std::endl;
    }

    Memento saveStateToMemento() {
        return Memento(state);
    }

    void restoreFromMemento(const Memento& m) {
        state = m.getState();
        std::cout << "Restored state: " << state << std::endl;
    }
};

// Caretaker: Stores Mementos
class Caretaker {
private:
    std::vector<Memento> history;
public:
    void addMemento(const Memento& m) {
        history.push_back(m);
    }

    Memento getMemento(int index) {
        return history[index];
    }
};

// Main function
int main() {
    Originator originator;
    Caretaker caretaker;

    originator.setState("State1");
    caretaker.addMemento(originator.saveStateToMemento());

    originator.setState("State2");
    caretaker.addMemento(originator.saveStateToMemento());

    originator.setState("State3");

    // Undo to State1
    originator.restoreFromMemento(caretaker.getMemento(0));

    return 0;
}
