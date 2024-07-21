# inplace_vector

A dynamically-resizable vector with fixed capacity and embedded storage.

## Introduction

`inplace_vector` is a header-only, dynamically-resizable vector with a fixed capacity and embedded storage. 

Its API closely resembles that of `std::vector`, providing similar performance characteristics with the added benefit of avoiding dynamic memory allocation. 

This makes `inplace_vector` ideal for use in environments where dynamic allocation is not desirable or possible, such as embedded systems.

## Usage

To use `inplace_vector`, simply include the header file in your project. 

No additional libraries or dependencies are required.

```cpp
#include "inplace_vector.hpp"

// Example usage
inplace_vector<int, 10> vec;
vec.push_back(1);
vec.push_back(2);
```

## API

The API is almost identical to `std::vector`.

## Simple Benchmark

`inplace_vector` and `std::vector` have nearly identical performance, when `std::vector` uses `reserve` to preallocate memory.

```text
Push Back
- inplace_vector: 0.00741959 ms, std::vector: 0.00865536 ms

Access
- inplace_vector: 0.00238694 ms, std::vector: 0.00193281 ms

Pop Back
- inplace_vector: 0.00829454 ms, std::vector: 0.0146191 ms

Modify
- inplace_vector: 0.00215841 ms, std::vector: 0.00241993 ms
```

## Reference
[P0843R8](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/p0843r8.html)
