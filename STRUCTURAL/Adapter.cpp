#include <iostream>

// Adaptee (Old API)
class LegacyTemperatureSensor {
public:
    double getTemperatureFahrenheit() {
        return 98.6; // Returns temperature in Fahrenheit
    }
};

// Target Interface (New System expects Celsius)
class TemperatureSensor {
public:
    virtual double getTemperatureCelsius() = 0;
    virtual ~TemperatureSensor() = default;
};

// Adapter (Converts Fahrenheit to Celsius)
class TemperatureAdapter : public TemperatureSensor, public LegacyTemperatureSensor {
    // LegacyTemperatureSensor& legacySensor;
public:
    // TemperatureAdapter(LegacyTemperatureSensor& sensor) : legacySensor(sensor) {}
    TemperatureAdapter() {}
    double getTemperatureCelsius() override {
        double fahrenheit = getTemperatureFahrenheit();
        return (fahrenheit - 32) * 5 / 9;  // Convert to Celsius
    }
};

// Client Code
int main() {
    // LegacyTemperatureSensor legacySensor;
    
    TemperatureAdapter adapter;
    
    std::cout << "Temperature in Celsius: " << adapter.getTemperatureCelsius() << "°C\n";
    return 0;
}
