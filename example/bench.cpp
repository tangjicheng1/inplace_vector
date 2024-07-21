#include <iostream>
#include <vector>
#include <chrono>
#include <numeric>
#include "inplace_vector.h"

constexpr int num_elements = 1000;
constexpr int num_iterations = 100;

using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<double, std::micro>;

template<typename Func>
double measure_time(Func func)
{
    std::vector<double> times;
    for (int i = 0; i < num_iterations; ++i)
    {
        auto start = Clock::now();
        func();
        auto end = Clock::now();
        times.push_back(Duration(end - start).count());
    }
    return std::accumulate(times.begin(), times.end(), 0.0) / num_iterations;
}

void benchmark_push_back()
{
    double inplace_time = measure_time([]() {
        inplace_vector<int, num_elements> vec;
        for (int i = 0; i < num_elements; ++i)
        {
            vec.push_back(i);
        }
    });

    double std_time = measure_time([]() {
        std::vector<int> vec;
        vec.reserve(num_elements);
        for (int i = 0; i < num_elements; ++i)
        {
            vec.push_back(i);
        }
    });

    std::cout << "Push Back:\n";
    std::cout << "  - inplace_vector: " << inplace_time << " µs\n";
    std::cout << "  - std::vector:    " << std_time << " µs\n\n";
}

void benchmark_access()
{
    inplace_vector<int, num_elements> inplace_vec;
    std::vector<int> std_vec;
    std_vec.reserve(num_elements);
    for (int i = 0; i < num_elements; ++i)
    {
        inplace_vec.push_back(i);
        std_vec.push_back(i);
    }

    double inplace_time = measure_time([&]() {
        volatile int sum = 0;
        for (int i = 0; i < num_elements; ++i)
        {
            sum += inplace_vec[i];
        }
    });

    double std_time = measure_time([&]() {
        volatile int sum = 0;
        for (int i = 0; i < num_elements; ++i)
        {
            sum += std_vec[i];
        }
    });

    std::cout << "Access:\n";
    std::cout << "  - inplace_vector: " << inplace_time << " µs\n";
    std::cout << "  - std::vector:    " << std_time << " µs\n\n";
}

void benchmark_pop_back()
{
    double inplace_time = measure_time([]() {
        inplace_vector<int, num_elements> vec;
        for (int i = 0; i < num_elements; ++i)
        {
            vec.push_back(i);
        }
        for (int i = 0; i < num_elements; ++i)
        {
            vec.pop_back();
        }
    });

    double std_time = measure_time([]() {
        std::vector<int> vec;
        vec.reserve(num_elements);
        for (int i = 0; i < num_elements; ++i)
        {
            vec.push_back(i);
        }
        for (int i = 0; i < num_elements; ++i)
        {
            vec.pop_back();
        }
    });

    std::cout << "Pop Back:\n";
    std::cout << "  - inplace_vector: " << inplace_time << " µs\n";
    std::cout << "  - std::vector:    " << std_time << " µs\n\n";
}

void benchmark_modify()
{
    inplace_vector<int, num_elements> inplace_vec;
    std::vector<int> std_vec;
    std_vec.reserve(num_elements);
    for (int i = 0; i < num_elements; ++i)
    {
        inplace_vec.push_back(i);
        std_vec.push_back(i);
    }

    double inplace_time = measure_time([&]() {
        for (int i = 0; i < num_elements; ++i)
        {
            inplace_vec[i] = i * 2;
        }
    });

    double std_time = measure_time([&]() {
        for (int i = 0; i < num_elements; ++i)
        {
            std_vec[i] = i * 2;
        }
    });

    std::cout << "Modify:\n";
    std::cout << "  - inplace_vector: " << inplace_time << " µs\n";
    std::cout << "  - std::vector:    " << std_time << " µs\n\n";
}

int main()
{
    benchmark_push_back();
    benchmark_access();
    benchmark_pop_back();
    benchmark_modify();
    return 0;
}
