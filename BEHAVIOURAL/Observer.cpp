#include <iostream>
#include <vector>

// Observer Interface
class Observer {
public:
    virtual void update(float temp) = 0;
};

// Subject (Weather Station)
class WeatherStation {
    std::vector<Observer*> observers;
    float temperature;
public:
    void addObserver(Observer* obs) { observers.push_back(obs); }
    void setTemperature(float temp) {
        temperature = temp;
        notifyObservers();
    }
    void notifyObservers() {
        for (auto obs : observers) obs->update(temperature);
    }
};

// Concrete Observer (Display)
class TemperatureDisplay : public Observer {
public:
    void update(float temp) override {
        std::cout << "Updated Temperature: " << temp << "°C\n";
    }
};

int main() {
    WeatherStation station;
    TemperatureDisplay display;

    station.addObserver(&display);
    station.setTemperature(25.5); // Output: Updated Temperature: 25.5°C

    return 0;
}
