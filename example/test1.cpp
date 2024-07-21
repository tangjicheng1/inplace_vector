#include <iostream>
#include "inplace_vector.h"

int main() {
    inplace_vector<int, 5> vec;

    // 测试 push_back 和 size
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "Size after 3 push_back: " << vec.size() << std::endl;

    // 测试元素访问
    std::cout << "Elements: ";
    for (std::size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    // 测试迭代器
    std::cout << "Elements using iterator: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
