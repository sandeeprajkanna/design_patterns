#include <iostream>
#include <vector>
#include <memory>

// Iterator Interface
class Iterator
{
public:
    virtual bool hasNext() = 0;
    virtual int next() = 0;
    virtual ~Iterator() = default;
};

class ConcreteIterator : public Iterator
{
    std::vector<int> collection;
    size_t index;

public:
    explicit ConcreteIterator(const std::vector<int> &data) : collection(data), index(0) {}

    bool hasNext() override
    {
        return index < collection.size();
    }

    int next() override
    {
        return hasNext() ? collection[index++] : -1;
    }
};

// Aggregate Interface
class IterableCollection
{
public:
    virtual std::shared_ptr<Iterator> createIterator() = 0;
    virtual ~IterableCollection() = default;
};

class NumberCollection : public IterableCollection
{
    std::vector<int> numbers;

public:
    void add(int num)
    {
        numbers.push_back(num);
    }

    std::shared_ptr<Iterator> createIterator() override
    {
        return std::make_shared<ConcreteIterator>(numbers);
    }
};

int main()
{
    NumberCollection collection;
    collection.add(10);
    collection.add(20);
    collection.add(30);
    collection.add(40);

    std::shared_ptr<Iterator> it = collection.createIterator();

    while (it->hasNext())
    {
        std::cout << it->next() << " ";
    }
    std::cout << std::endl; // Output: 10 20 30 40

    return 0;
}
