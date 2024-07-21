#include "inplace_vector.h"
#include <vector>
#include <iostream>

int main()
{
    inplace_vector<int, 5> vec;
    std::cout << "inplace vector data addr: " << static_cast<uint64_t>(reinterpret_cast<uintptr_t>(vec.data())) << std::endl;
    std::cout << "inplace vector addr: " << static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&vec)) << std::endl;

    std::vector<int> std_vec(5, -1);
    std::cout << "std::vector data addr: " << static_cast<uint64_t>(reinterpret_cast<uintptr_t>(std_vec.data())) << std::endl;
    std::cout << "std::vector vector addr: " << static_cast<uint64_t>(reinterpret_cast<uintptr_t>(&std_vec)) << std::endl;

    return 0;
}