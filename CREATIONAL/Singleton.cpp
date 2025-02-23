#include <iostream>

class Logger {
private:
    Logger() { std::cout << "Logger Initialized.\n"; }

public:
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    static Logger& getInstance() {
        static Logger instance;  // Thread-safe in C++11+
        return instance;
    }

    void log(const std::string& message) {
        std::cout << "Log: " << message << "\n";
    }
};

int main() {
    Logger& logger1 = Logger::getInstance();  // ✅ Reference assignment (OK)
    logger1.log("Singleton pattern without mutex!");

    Logger& logger2 = Logger::getInstance();
    logger2.log("Same instance is used everywhere.");

    return 0;
}
