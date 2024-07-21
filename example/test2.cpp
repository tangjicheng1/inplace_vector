// example/test2.cpp

#include <iostream>
#include "inplace_vector.h"

int main() {
    inplace_vector<int, 5> vec;

    // 测试 emplace_back 和插入操作
    vec.emplace_back(1);
    vec.emplace_back(2);
    vec.emplace_back(3);
    std::cout << "Elements after emplace_back: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 测试插入操作
    vec.insert(vec.begin() + 1, 4);
    std::cout << "Elements after insert: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 测试删除操作
    vec.erase(vec.begin() + 1);
    std::cout << "Elements after erase: ";
    for (const auto& elem : vec) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // 测试清除操作
    vec.clear();
    std::cout << "Size after clear: " << vec.size() << std::endl;

    return 0;
}
