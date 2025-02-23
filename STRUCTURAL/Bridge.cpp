#include <iostream>

// Implementor Interface
class Device {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual ~Device() = default;
};

// Concrete Implementor 1 (TV)
class TV : public Device {
    public:
        void turnOn() override {
            std::cout << "TV is turned ON.\n";
        }
    
        void turnOff() override {
            std::cout << "TV is turned OFF.\n";
        }
    };
    
    // Concrete Implementor 2 (Radio)
    class Radio : public Device {
    public:
        void turnOn() override {
            std::cout << "Radio is turned ON.\n";
        }
    
        void turnOff() override {
            std::cout << "Radio is turned OFF.\n";
        }
    };

    // Abstraction (Remote Control)
class RemoteControl {
    protected:
        Device* device;
    public:
        RemoteControl(Device* dev) : device(dev) {}
        virtual void powerButton() = 0;
        virtual ~RemoteControl() = default;
    };

    // Refined Abstraction (Basic Remote)
class BasicRemote : public RemoteControl {
    public:
        BasicRemote(Device* dev) : RemoteControl(dev) {}
        
        void powerButton() override {
            std::cout << "Basic Remote: Power Button Pressed\n";
            device->turnOn();
        }
    };
    
    // Refined Abstraction (Smart Remote with additional feature)
    class SmartRemote : public RemoteControl {
    public:
        SmartRemote(Device* dev) : RemoteControl(dev) {}
    
        void powerButton() override {
            std::cout << "Smart Remote: Power Button Pressed\n";
            device->turnOn();
        }
    
        void voiceControl() {
            std::cout << "Smart Remote: Voice Control Activated\n";
        }
    };

    int main() {
        Device* tv = new TV();
        Device* radio = new Radio();
    
        RemoteControl* basicRemote = new BasicRemote(tv);
        RemoteControl* smartRemote = new SmartRemote(radio);
    
        basicRemote->powerButton();
        smartRemote->powerButton();
        dynamic_cast<SmartRemote*>(smartRemote)->voiceControl();  // Smart remote specific feature
    
        delete tv;
        delete radio;
        delete basicRemote;
        delete smartRemote;
        
        return 0;
    }
    