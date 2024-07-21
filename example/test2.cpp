// example/test2.cpp

#include <iostream>
#include "inplace_vector.h"

int main() {
    inplace_vector<int, 5> vec;

    vec.emplace_back(1);
    vec.emplace_back(2);
    vec.emplace_back(3);
    std::cout << "Elements after emplace_back: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    vec.insert(vec.begin() + 1, 4);
    std::cout << "Elements after insert: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    vec.erase(vec.begin() + 1);
    std::cout << "Elements after erase: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    vec.clear();
    std::cout << "Size after clear: " << vec.size() << std::endl;

    return 0;
}
