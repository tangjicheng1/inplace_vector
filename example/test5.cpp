#include <iostream>
#include "inplace_vector.h"

int main()
{
    inplace_vector<int, 10> vec;

    for (int i = 0; i < 10; ++i)
    {
        vec.push_back(i);
    }

    std::cout << "Elements in normal order:" << std::endl;
    for (const auto& elem : vec)
    {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    std::cout << "Elements in reverse order:" << std::endl;
    for (auto it = vec.rbegin(); it != vec.rend(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
