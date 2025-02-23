#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Forward declaration
class User;

// Mediator Interface
class ChatMediator
{
public:
    virtual void sendMessage(const std::string &message, std::shared_ptr<User> sender) = 0;
    virtual void addUser(std::shared_ptr<User> user) = 0;
    virtual ~ChatMediator() = default;
};

class User : public std::enable_shared_from_this<User>
{
protected:
    std::shared_ptr<ChatMediator> mediator;
    std::string name;

public:
    User(std::shared_ptr<ChatMediator> med, const std::string &userName)
        : mediator(std::move(med)), name(userName) {}

    void send(const std::string &message)
    {
        mediator->sendMessage(message, shared_from_this()); // Now shared_from_this() is available
    }

    void receive(const std::string &message, const std::string &sender)
    {
        std::cout << name << " received from " << sender << ": " << message << std::endl;
    }

    std::string getName() const { return name; }
};

class ChatRoom : public ChatMediator
{
    std::vector<std::shared_ptr<User>> users;

public:
    void addUser(std::shared_ptr<User> user) override
    {
        users.push_back(user);
    }

    void sendMessage(const std::string &message, std::shared_ptr<User> sender) override
    {
        for (const auto &user : users)
        {
            if (user != sender)
            { // Do not send message to the sender itself
                user->receive(message, sender->getName());
            }
        }
    }
};

int main()
{
    std::shared_ptr<ChatMediator> chatRoom = std::make_shared<ChatRoom>();

    std::shared_ptr<User> user1 = std::make_shared<User>(chatRoom, "Alice");
    std::shared_ptr<User> user2 = std::make_shared<User>(chatRoom, "Bob");
    std::shared_ptr<User> user3 = std::make_shared<User>(chatRoom, "Charlie");

    chatRoom->addUser(user1);
    chatRoom->addUser(user2);
    chatRoom->addUser(user3);

    user1->send("Hello, everyone!");
    user2->send("Hi Alice!");
    user3->send("Hey Bob!");

    return 0;
}
