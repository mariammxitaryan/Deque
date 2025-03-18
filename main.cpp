#include "dequeHeader.hpp"

int main() {
    Deque<int> dq;
    
    // Test push_front and push_back
    dq.push_back(10);
    dq.push_back(20);
    dq.push_front(5);
    dq.push_front(1);
    
    // Test size and empty
    std::cout << "Deque size: " << dq.size() << std::endl;
    std::cout << "Deque empty: " << std::boolalpha << dq.empty() << std::endl;

    // Test operator[] and at()
    std::cout << "Element at index 0 (operator[]): " << dq[0] << std::endl;
    std::cout << "Element at index 1 (at()): " << dq.at(1) << std::endl;
    
    // Test iterators
    std::cout << "Deque elements using iterator: ";
    for (auto it = dq.begin(); it != dq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test const iterators
    std::cout << "Deque elements using const_iterator: ";
    for (auto it = dq.cbegin(); it != dq.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    
    // Test iterator arithmetic
    auto it1 = dq.begin();
    auto it2 = dq.end();
    std::cout << "Distance between begin and end: " << (it2 - it1) << std::endl;
    
    // Test iterator comparison
    if (it1 < it2) {
        std::cout << "Begin iterator is less than end iterator." << std::endl;
    }
    if (it2 > it1) {
        std::cout << "End iterator is greater than begin iterator." << std::endl;
    }
    if (it1 <= it2) {
        std::cout << "Begin iterator is less than or equal to end iterator." << std::endl;
    }
    if (it2 >= it1) {
        std::cout << "End iterator is greater than or equal to begin iterator." << std::endl;
    }
    
    // Test iterator increment and decrement
    std::cout << "Iterator increment and decrement: ";
    auto it3 = dq.begin();
    ++it3;
    std::cout << *it3 << " ";
    --it3;
    std::cout << *it3 << std::endl;
    
    // Test iterator addition and subtraction
    it3 += 2;
    std::cout << "Iterator after += 2: " << *it3 << std::endl;
    it3 -= 1;
    std::cout << "Iterator after -= 1: " << *it3 << std::endl;
    
    return 0;
}