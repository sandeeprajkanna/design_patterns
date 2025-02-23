#include <iostream>
#include <unordered_map>
#include <memory>

// Step 1: Flyweight Interface
class Character {
public:
    virtual void display(int size, int color) = 0;
    virtual ~Character() = default;
};

// Step 2: ConcreteFlyweight (Shared Object)
class ConcreteCharacter : public Character {
private:
    char symbol;  // Intrinsic (shared) state

public:
    ConcreteCharacter(char c) : symbol(c) {}

    void display(int size, int color) override {
        std::cout << "Character: " << symbol
                  << " | Font Size: " << size
                  << " | Color: " << color << "\n";
    }
};



// Step 3: Flyweight Factory (Manages Reuse)
class CharacterFactory {
private:
    std::unordered_map<char, std::shared_ptr<Character>> characterPool;

public:
    std::shared_ptr<Character> getCharacter(char c) {
        if (characterPool.find(c) == characterPool.end()) {
            characterPool[c] = std::make_shared<ConcreteCharacter>(c);
        }
        return characterPool[c];  // Return shared instance
    }
};

// Step 4: Client Code
int main() {
    CharacterFactory factory;

    std::shared_ptr<Character> c1 = factory.getCharacter('A');
    std::shared_ptr<Character> c2 = factory.getCharacter('B');
    std::shared_ptr<Character> c3 = factory.getCharacter('A');  // Reuse 'A'

    c1->display(12, 1);  // Unique size and color (extrinsic state)
    c2->display(14, 2);
    c3->display(18, 3);  // 'A' is reused

    return 0;
}
