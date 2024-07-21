#include <iostream>
#include "inplace_vector.h"

struct A
{
    int x;
    double y;

    A(int a, double b) :
        x(a), y(b) {}

    void display() const
    {
        std::cout << "A: { x: " << x << ", y: " << y << " }" << std::endl;
    }
};

int main()
{
    inplace_vector<A, 5> vec;

    vec.emplace_back(1, 1.1);
    vec.emplace_back(2, 2.2);
    vec.emplace_back(3, 3.3);

    std::cout << "Contents of vec:" << std::endl;
    for (const auto& elem : vec)
    {
        elem.display();
    }

    return 0;
}
