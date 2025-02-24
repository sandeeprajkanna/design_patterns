#include <iostream>
#include <stack>
#include <memory>

// **Command Interface**
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() = default;
};

// **Receiver (Actual Device)**
class Light {
public:
    void turnOn() {
        std::cout << "💡 Light is ON\n";
    }
    void turnOff() {
        std::cout << "💡 Light is OFF\n";
    }
};

// **Concrete Command: Turn On Light**
class LightOnCommand : public Command {
private:
    Light& light;

public:
    LightOnCommand(Light& light) : light(light) {}

    void execute() override {
        light.turnOn();
    }

    void undo() override {
        light.turnOff();
    }
};

// **Concrete Command: Turn Off Light**
class LightOffCommand : public Command {
private:
    Light& light;

public:
    LightOffCommand(Light& light) : light(light) {}

    void execute() override {
        light.turnOff();
    }

    void undo() override {
        light.turnOn();
    }
};

// **Invoker (Remote Control)**
class RemoteControl {
private:
    std::stack<std::shared_ptr<Command>> commandHistory;

public:
    void pressButton(std::shared_ptr<Command> command) {
        command->execute();
        commandHistory.push(command);
    }

    void pressUndo() {
        if (!commandHistory.empty()) {
            commandHistory.top()->undo();
            commandHistory.pop();
        } else {
            std::cout << "❌ No command to undo\n";
        }
    }
};

// **Client Code**
int main() {
    Light livingRoomLight;

    auto lightOn = std::make_shared<LightOnCommand>(livingRoomLight);
    auto lightOff = std::make_shared<LightOffCommand>(livingRoomLight);

    RemoteControl remote;
    
    remote.pressButton(lightOn);   // Light is ON
    remote.pressButton(lightOff);  // Light is OFF
    remote.pressUndo();            // Undo: Light is ON
    remote.pressUndo();            // Undo: Light is OFF
    remote.pressUndo();            // No command to undo

    return 0;
}
