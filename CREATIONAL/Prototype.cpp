#include <iostream>
#include <memory>

// Prototype Interface
class Shape {
public:
    virtual std::unique_ptr<Shape> clone() const = 0;
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
// Concrete Prototype: Circle
class Circle : public Shape {
    private:
        int radius;
    
    public:
        Circle(int r) : radius(r) {}
    
        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Circle>(*this);
        }
    
        void draw() const override {
            std::cout << "Drawing a Circle with radius " << radius << "\n";
        }
    };
    
    // Concrete Prototype: Rectangle
    class Rectangle : public Shape {
    private:
        int width, height;
    
    public:
        Rectangle(int w, int h) : width(w), height(h) {}
    
        std::unique_ptr<Shape> clone() const override {
            return std::make_unique<Rectangle>(*this);
        }
    
        void draw() const override {
            std::cout << "Drawing a Rectangle with width " << width << " and height " << height << "\n";
        }
    };
    int main() {
        // Create original objects
        std::unique_ptr<Shape> circle = std::make_unique<Circle>(10);
        std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(5, 7);
    
        // Clone the objects
        std::unique_ptr<Shape> clonedCircle = circle->clone();
        std::unique_ptr<Shape> clonedRectangle = rectangle->clone();
    
        // Display cloned objects
        clonedCircle->draw();
        clonedRectangle->draw();
    
        return 0;
    }
        