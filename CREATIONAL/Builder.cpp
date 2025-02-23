#include <iostream>
#include <string>

class Car {
private:
    std::string engine;
    std::string seats;
    std::string GPS;
    
public:
    void setEngine(const std::string& eng) { engine = eng; }
    void setSeats(const std::string& s) { seats = s; }
    void setGPS(const std::string& gps) { GPS = gps; }

    void show() {
        std::cout << "Car Configuration: \n";
        std::cout << "Engine: " << engine << "\n";ccccx
        std::cout << "Seats: " << seats << "\n";
        std::cout << "GPS: " << GPS << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Car* car) {
        os << car->engine << " " << car->GPS <<std::endl;
        return os;
    } 
};

class CarBuilder {
    public:
        virtual CarBuilder* buildEngine(const std::string& type) = 0;
        virtual CarBuilder* buildSeats(const std::string& type) = 0;
        virtual CarBuilder* buildGPS(const std::string& type) = 0;
        virtual Car* getCar() = 0;
        virtual ~CarBuilder() {}
    };
    
    class ConcreteCarBuilder : public CarBuilder {
        private:
            Car* car;
            
        public:
            ConcreteCarBuilder() : car(new Car()) {}
        
            CarBuilder* buildEngine(const std::string& type) override {
                car->setEngine(type);
                return this;
            }
        
            CarBuilder* buildSeats(const std::string& type) override {
                car->setSeats(type);
                return this;
            }
        
            CarBuilder* buildGPS(const std::string& type) override {
                car->setGPS(type);
                return this;
            }
        
            Car* getCar() override {
                return car;
            }
        };

        
        class CarDirector {
            public:
                static Car* createLuxuryCar(CarBuilder* builder) {
                    return builder->buildEngine("V8 Engine")
                                  ->buildSeats("Leather Seats")
                                  ->buildGPS("Advanced GPS")
                                  ->getCar();
                }
            
                static Car* createEconomyCar(CarBuilder* builder) {
                    return builder->buildEngine("Basic Engine")
                                  ->buildSeats("Fabric Seats")
                                  ->getCar();
                }
            };

            int main() {
                ConcreteCarBuilder builder;
            
                std::cout << "Luxury Car:\n";
                Car* luxuryCar = CarDirector::createLuxuryCar(&builder);
                std::cout << luxuryCar << std::endl;
                luxuryCar->show();
                delete luxuryCar;
            
                std::cout << "\nEconomy Car:\n";
                Car* economyCar = CarDirector::createEconomyCar(&builder);
                economyCar->show();
                delete economyCar;
            
                return 0;
            }
            