#include <iostream>
#include <memory>

class Logger {
protected:
    std::shared_ptr<Logger> nextLogger;  // ✅ Next handler in the chain
public:
    void setNext(std::shared_ptr<Logger> next) { nextLogger = next; }
    virtual void handleRequest(int level, const std::string& message) {
        if (nextLogger) nextLogger->handleRequest(level, message);
    }
    virtual ~Logger() = default;
};

class InfoLogger : public Logger {
    public:
        void handleRequest(int level, const std::string& message) override {
            if (level == 1) {
                std::cout << "[INFO]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->handleRequest(level, message);
            }
        }
    };
    
    class WarningLogger : public Logger {
    public:
        void handleRequest(int level, const std::string& message) override {
            if (level == 2) {
                std::cout << "[WARNING]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->handleRequest(level, message);
            }
        }
    };
    
    class ErrorLogger : public Logger {
    public:
        void handleRequest(int level, const std::string& message) override {
            if (level == 3) {
                std::cout << "[ERROR]: " << message << std::endl;
            } else if (nextLogger) {
                nextLogger->handleRequest(level, message);
            }
        }
    };

    int main() {
        auto infoLogger = std::make_shared<InfoLogger>();
        auto warningLogger = std::make_shared<WarningLogger>();
        auto errorLogger = std::make_shared<ErrorLogger>();
    
        // ✅ Setting up the chain
        infoLogger->setNext(warningLogger);
        warningLogger->setNext(errorLogger);
    
        // 🔥 Send requests
        infoLogger->handleRequest(1, "This is an informational message.");
        infoLogger->handleRequest(2, "This is a warning message.");
        infoLogger->handleRequest(3, "This is an error message.");
    
        return 0;
    }
    