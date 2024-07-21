#include <iostream>
#include "inplace_vector.h"

int main()
{
    inplace_vector<int, 5> vec;

    std::cout << "Size in the beginning: " << vec.size() << std::endl;

    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << "Size after 3 push_back: " << vec.size() << std::endl;

    std::cout << "Elements: ";
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements using iterator: ";
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements using foreach iterator: ";
    for (auto&& it : vec)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;

    vec.clear();

    std::cout << "Size after clear: " << vec.size() << std::endl;

    return 0;
}
