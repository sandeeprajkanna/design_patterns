#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

// Abstract Expression
class Expression {
public:
    virtual int interpret(std::unordered_map<std::string, int>& context) = 0;
    virtual ~Expression() = default;
};

class NumberExpression : public Expression {
    int number;
public:
    explicit NumberExpression(int value) : number(value) {}
    
    int interpret(std::unordered_map<std::string, int>&) override {
        return number;
    }
};

class AddExpression : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    AddExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) 
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return left->interpret(context) + right->interpret(context);
    }
};

class SubtractExpression : public Expression {
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;
public:
    SubtractExpression(std::shared_ptr<Expression> l, std::shared_ptr<Expression> r) 
        : left(std::move(l)), right(std::move(r)) {}

    int interpret(std::unordered_map<std::string, int>& context) override {
        return left->interpret(context) - right->interpret(context);
    }
};

int main() {
    std::unordered_map<std::string, int> context;

    // Constructing the expression: (5 + 3) - 2
    std::shared_ptr<Expression> expr = std::make_shared<SubtractExpression>(
        std::make_shared<AddExpression>(
            std::make_shared<NumberExpression>(5),
            std::make_shared<NumberExpression>(3)
        ),
        std::make_shared<NumberExpression>(2)
    );

    std::cout << "Result: " << expr->interpret(context) << std::endl; // Output: 6
    return 0;
}
