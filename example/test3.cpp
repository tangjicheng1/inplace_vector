#include "inplace_vector.h"
#include <vector>
#include <iostream>

int main()
{
    inplace_vector<int, 100> vec;
    std::cout << "sizeof(vec): " << sizeof(vec) << std::endl;
    std::cout << "inplace vector data addr: " << reinterpret_cast<uintptr_t>(vec.data()) << std::endl;
    std::cout << "inplace vector addr: " << reinterpret_cast<uintptr_t>(&vec) << std::endl;

    std::vector<int> std_vec(100, -1);
    std::cout << "sizeof(std_vec): " << sizeof(std_vec) << std::endl;
    std::cout << "std::vector data addr: " << reinterpret_cast<uintptr_t>(std_vec.data()) << std::endl;
    std::cout << "std::vector vector addr: " << reinterpret_cast<uintptr_t>(&std_vec) << std::endl;

    return 0;
}