#include <iostream>
#include <vector>
#include <memory>

// Component Interface
class FileSystemComponent {
public:
    virtual void showDetails(int indent = 0) const = 0;
    virtual ~FileSystemComponent() = default;
};

// Leaf (File)
class File : public FileSystemComponent {
    std::string name;
public:
    File(std::string name) : name(std::move(name)) {}
    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "- " << name << "\n";
    }
};

// Composite (Folder)
class Folder : public FileSystemComponent {
    std::string name;
    std::vector<std::shared_ptr<FileSystemComponent>> children;
public:
    Folder(std::string name) : name(std::move(name)) {}

    void add(std::shared_ptr<FileSystemComponent> component) {
        children.push_back(component);
    }

    void showDetails(int indent = 0) const override {
        std::cout << std::string(indent, ' ') << "[Folder] " << name << "\n";
        for (const auto& child : children) {
            child->showDetails(indent + 2);
        }
    }
};

// Usage
int main() {
    auto root = std::make_shared<Folder>("Root");
    auto folder1 = std::make_shared<Folder>("Documents");
    auto file1 = std::make_shared<File>("resume.pdf");
    auto file2 = std::make_shared<File>("notes.txt");

    folder1->add(file1);
    folder1->add(file2);
    root->add(folder1);
    root->add(std::make_shared<File>("image.png"));

    root->showDetails();
    return 0;
}
