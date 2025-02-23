#include <iostream>
#include <memory>

// Abstract Product
class Shape {
public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
// Concrete Product: Circle
class Circle : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a Circle\n";
        }
    };
    
    // Concrete Product: Rectangle
    class Rectangle : public Shape {
    public:
        void draw() const override {
            std::cout << "Drawing a Rectangle\n";
        }
    };
    enum class ShapeType { CIRCLE, RECTANGLE };
class ShapeFactory {
    public:
        virtual std::unique_ptr<Shape> createShape() = 0;
        virtual ~ShapeFactory() = default;
};

// Factory Class
class CircleFactory : public ShapeFactory {
    public:
        
         std::unique_ptr<Shape> createShape() {
             return std::make_unique<Circle>();
            // switch (type) {
            //     case ShapeType::CIRCLE:
            //     case ShapeType::RECTANGLE:
            //         return std::make_unique<Rectangle>();
            //     default:
            //         return nullptr;
            // }
        }
    };


    class ReactangleFactory : public ShapeFactory {
        public:
            
             std::unique_ptr<Shape> createShape() {
                 return std::make_unique<Rectangle>();
                // switch (type) {
                //     case ShapeType::CIRCLE:
                //     case ShapeType::RECTANGLE:
                //         return std::make_unique<Rectangle>();
                //     default:
                //         return nullptr;
                // }
            }
        };
    int main() {
        std::shared_ptr<ShapeFactory> ptr = std::make_shared<CircleFactory>();
        ptr->createShape()->draw();
        // auto circle = ShapeFactory::createShape(ShapeFactory::ShapeType::CIRCLE);
        // auto rectangle = ShapeFactory::createShape(ShapeFactory::ShapeType::RECTANGLE);
        ptr.reset(new ReactangleFactory());
        ptr->createShape()->draw();
        // if (circle) circle->draw();
        // if (rectangle) rectangle->draw();
    
        return 0;
    }
            