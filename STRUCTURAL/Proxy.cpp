#include <iostream>
#include <memory>

// Step 1: Subject Interface
class ISubject {
public:
    virtual void request() = 0;
    virtual ~ISubject() = default;
};

// Step 2: RealSubject (Actual Object)
class RealSubject : public ISubject {
public:
    void request() override {
        std::cout << "RealSubject: Handling the request.\n";
    }
};

// Step 3: Proxy (Controls Access)
class Proxy : public ISubject {
private:
    std::unique_ptr<RealSubject> realSubject;
    std::string role;

public:
    Proxy(std::string userRole) : role(userRole) {}

    void request() override {
        if (role == "Admin") {
            if (!realSubject) {  // Lazy initialization
                realSubject = std::make_unique<RealSubject>();
            }
            realSubject->request();
        } else {
            std::cout << "Proxy: Access Denied! Only Admin can execute this request.\n";
        }
    }
};

// Step 4: Client Code
int main() {
    std::cout << "User with 'Guest' role:\n";
    Proxy guestProxy("Guest");
    guestProxy.request();  // Access Denied!

    std::cout << "\nUser with 'Admin' role:\n";
    Proxy adminProxy("Admin");
    adminProxy.request();  // Request is forwarded to RealSubject

    return 0;
}
